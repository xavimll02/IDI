// MyGLWidget.cpp
#include "MyGLWidget.h"
#include <iostream>
#include <stdio.h>

#define printOpenGLError() printOglError(__FILE__, __LINE__)
#define CHECK() printOglError(__FILE__, __LINE__,__FUNCTION__)
#define DEBUG() std::cout << __FILE__ << " " << __LINE__ << " " << __FUNCTION__ << std::endl;

int MyGLWidget::printOglError(const char file[], int line, const char func[]) 
{
    GLenum glErr;
    int    retCode = 0;

    glErr = glGetError();
    const char * error = 0;
    switch (glErr)
    {
        case 0x0500:
            error = "GL_INVALID_ENUM";
            break;
        case 0x501:
            error = "GL_INVALID_VALUE";
            break;
        case 0x502: 
            error = "GL_INVALID_OPERATION";
            break;
        case 0x503:
            error = "GL_STACK_OVERFLOW";
            break;
        case 0x504:
            error = "GL_STACK_UNDERFLOW";
            break;
        case 0x505:
            error = "GL_OUT_OF_MEMORY";
            break;
        default:
            error = "unknown error!";
    }
    if (glErr != GL_NO_ERROR)
    {
        printf("glError in file %s @ line %d: %s function: %s\n",
                             file, line, error, func);
        retCode = 1;
    }
    return retCode;
}

void MyGLWidget::keyPressEvent(QKeyEvent* event) 
{
  makeCurrent();
  switch (event->key()) {
    case Qt::Key_O: { // escalar a més gran
      option = (option + 1) % 2;
      projectTransform();
      break;
    }

    default: event->ignore(); break;
  }
  update();
}

void MyGLWidget::initializeGL (){
  // Cal inicialitzar l'ús de les funcions d'OpenGL
    initializeOpenGLFunctions();  
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.5, 0.7, 1.0, 1.0); // defineix color de fons (d'esborrat)
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    carregaShaders();
    creaBuffers();
    pminmax = calculaCapsaModel();
    centroAbajoModelo = glm::vec3((pminmax.first[0]+pminmax.second[0])/2,pminmax.first[1],(pminmax.first[2]+pminmax.second[2])/2);
    h = pminmax.second[1]-pminmax.first[1];
    sphere(glm::vec3(-2.5,0,-2.5),glm::vec3(2.5,4,2.5));
    option = 0;
    ini_camera();
}

void MyGLWidget::paintGL() {
 
    glClear (GL_COLOR_BUFFER_BIT);

  // Carreguem la transformació de model
    modelTransform1();
  // Activem el VAO per a pintar la caseta 
    glBindVertexArray (VAO_Patricio);

  // pintem
    glDrawArrays(GL_TRIANGLES, 0, m.faces().size()*3);
    modelTransform2();
    glBindVertexArray(VAO_Terra);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void MyGLWidget::resizeGL (int w, int h) 
{

    ra = float(w)/float(h);
    if (ra < 1.0) FOV = 2.0*atan(tan(FOVini/2.0)/ra);
    projectTransform();    
}

QPair<glm::vec3,glm::vec3> MyGLWidget::calculaCapsaModel() {
 
    float minx, maxx, miny, maxy, minz, maxz;
    minx = maxx = m.vertices()[0];
    miny = maxy = m.vertices()[1];
    minz = maxz = m.vertices()[2];
    for (double i = 3; i < m.vertices().size(); i+= 3) {
        
        if (m.vertices()[i] < minx) minx = m.vertices()[i];
        if (m.vertices()[i] > maxx) maxx = m.vertices()[i];
        if (m.vertices()[i+1] < miny) miny = m.vertices()[i+1];
        if (m.vertices()[i+1] > maxy) maxy = m.vertices()[i+1];
        if (m.vertices()[i+2] < minz) minz = m.vertices()[i+2];
        if (m.vertices()[i+2] > maxz) maxz = m.vertices()[i+2];
    }
    
    return {glm::vec3(minx,miny,minz), glm::vec3(maxx,maxy,maxz)};
}

void MyGLWidget::modelTransform1() {
 
    glm::mat4 transform (1.0f);
    transform = glm::scale(transform,glm::vec3(4/h,4/h,4/h));
    transform = glm::translate(transform,-centroAbajoModelo);
    glUniformMatrix4fv(transLoc, 1, GL_FALSE, &transform[0][0]);
}

void MyGLWidget::modelTransform2() {
 
    glm::mat4 transform (1.0f);
    glUniformMatrix4fv(transLoc, 1, GL_FALSE, &transform[0][0]);
}

void MyGLWidget::projectTransform() {
 
    glm::mat4 Proj;
    
    if (option == 0) {
        Proj = glm::perspective(FOV, ra, znear, zfar);
        glUniformMatrix4fv(projLoc,1,GL_FALSE,&Proj[0][0]);
    }
    
    else {
        if (ra >= 1) Proj = glm::ortho(double(-radio*ra),double(radio*ra),double(-radio),double(radio),double(znear), double(zfar));
        else Proj = glm::ortho(double(-radio),double(radio),double(-radio*pow(ra,-1)),double(radio*pow(ra,-1)),double(znear), double(zfar));
        glUniformMatrix4fv(projLoc,1,GL_FALSE,&Proj[0][0]);
    }
}

void MyGLWidget::viewTransform(const glm::vec3& OBS, const glm::vec3& VRP, const glm::vec3& UP) {
 
    glm::mat4 View = glm::lookAt(OBS, VRP, UP);
    glUniformMatrix4fv(viewLoc,1,GL_FALSE,&View[0][0]);
}

void MyGLWidget::sphere(const glm::vec3& pmin, const glm::vec3& pmax) {
 
    centroEscena = (pmin+pmax)/2.0f;
    radio = glm::distance(centroEscena,pmax);
}

void MyGLWidget::ini_camera() {
 
    float d = 2 * radio;
    FOVini = glm::asin(radio/d)*2;
    FOV = FOVini;
    ra = 1.0;
    znear = d - radio;
    zfar = d + radio;
    
    glm::vec3 VRP = centroEscena;
    glm::vec3 OBS = VRP+(d*(glm::vec3(0,0,1)));
    glm::vec3 UP = glm::vec3(0,1,0);
    
    projectTransform();
    viewTransform(OBS, VRP, UP);
}

void MyGLWidget::carregaShaders() {
    
    BL2GLWidget::carregaShaders();
    projLoc = glGetUniformLocation(program->programId(), "proj");
    viewLoc = glGetUniformLocation(program->programId(), "view");
}

void MyGLWidget::creaBuffers() 
{
    // Dades del homer
    m.load("/home/xavi/Escritorio/models/Patricio.obj");

    // Creació del Vertex Array Object per pintar
    glGenVertexArrays(1, &VAO_Patricio);
    glBindVertexArray(VAO_Patricio);

    GLuint VBO_Patricio[2];
    glGenBuffers(2, VBO_Patricio);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Patricio[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*m.faces().size()*3*3, m.VBO_vertices(), GL_STATIC_DRAW);

    // Activem l'atribut vertexLoc
    glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(vertexLoc);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_Patricio[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*m.faces().size()*3*3, m.VBO_matdiff(), GL_STATIC_DRAW);

    // Activem l'atribut colorLoc
    glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(colorLoc);
    
    glm::vec3 posicio[6] = {
        
        glm::vec3(-2.5, 0.0, -2.5),
        glm::vec3( 2.5, 0.0, -2.5),
        glm::vec3(-2.5,  0.0, 2.5),
        glm::vec3(-2.5,  0.0, 2.5),
        glm::vec3( 2.5, 0.0, -2.5),
        glm::vec3( 2.5,  0.0, 2.5)
    }; 
    
    glm::vec3 color[6] = {
        
        glm::vec3(0.0,0.0,1.0),
        glm::vec3(0.0,0.0,1.0),
        glm::vec3(0.0,0.0,1.0),
        glm::vec3(0.0,0.0,1.0),
        glm::vec3(0.0,0.0,1.0),
        glm::vec3(0.0,0.0,1.0)
    };
    
    glGenVertexArrays(1, &VAO_Terra);
    
    glBindVertexArray(VAO_Terra);
    GLuint VBO_Terra[2];
    glGenBuffers(2,VBO_Terra);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Terra[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(posicio), posicio, GL_STATIC_DRAW);
    glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(vertexLoc);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Terra[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);
    glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(colorLoc);
    
    glBindVertexArray(0);
}

MyGLWidget::~MyGLWidget() {
}


