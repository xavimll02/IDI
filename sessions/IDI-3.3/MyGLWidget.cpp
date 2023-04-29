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

void MyGLWidget::iniMaterialTerra()
{
  // Donem valors al material del terra
  amb = glm::vec3(0.2,0,0.2);
  diff = glm::vec3(0.0,0,0.8);
  spec = glm::vec3(1,1,1);
  shin = 100;
}

void MyGLWidget::modelTransformPatricio()
{
    TG = glm::translate(glm::mat4(1.f), desplacament);
    TG = glm::scale(TG, glm::vec3(esc, esc, esc));
    TG = glm::translate(TG, -centrePatr);
    glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::carregaShaders()
{
  BL3GLWidget::carregaShaders();
  posfocusCLoc = glGetUniformLocation(program->programId(), "posFocusC");
  colorfocusCLoc = glGetUniformLocation(program->programId(), "colorFocusC");
  posfocusELoc = glGetUniformLocation(program->programId(), "posFocusE");
  colorfocusELoc = glGetUniformLocation(program->programId(), "colorFocusE");
}

void MyGLWidget::initializeGL()
{
  // Cal inicialitzar l'ús de les funcions d'OpenGL
  initializeOpenGLFunctions();  

  glClearColor(0.5, 0.7, 1.0, 1.0); // defineix color de fons (d'esborrat)
  glEnable(GL_DEPTH_TEST);
  carregaShaders();
  creaBuffersPatricio();
  creaBuffersTerraIParet();
  
  glUniform3fv(posfocusCLoc, 1, &posFC[0]);
  glUniform3fv(colorfocusCLoc, 1, &colorFC[0]);
  iniEscena();
  iniCamera();
  glUniform3fv(colorfocusELoc, 1, &colorFE[0]);
  esc = ((escala*0.3)/2.0);
}

void MyGLWidget::paintGL () 
{
  glm::vec4 aux = View * glm::vec4(glm::vec3(desplacament.x, -0.5, desplacament.z), 1.0);
  posFE = glm::vec3(aux.x, aux.y, aux.z);
  glUniform3fv(posfocusELoc, 1, &posFE[0]);
  BL3GLWidget::paintGL();
}

MyGLWidget::~MyGLWidget() {
}

void MyGLWidget::mouseMoveEvent(QMouseEvent *e)
{
  makeCurrent();
  // Aqui cal que es calculi i s'apliqui la rotacio o el zoom com s'escaigui...
  if (DoingInteractive == ROTATE)
  {
    // Fem la rotació
    angleY += (e->x() - xClick) * M_PI / ample;
    viewTransform ();
  }

  xClick = e->x();
  yClick = e->y();

  update ();
}

void MyGLWidget::keyPressEvent(QKeyEvent* event) {
  
  makeCurrent();
  switch (event->key()) {
      
      case Qt::Key_Left: // canvia òptica entre perspectiva i axonomètrica
        
        desplacament = desplacament + glm::vec3(-0.1,0,0);
    
      break;
      
      case Qt::Key_Right: // canvia òptica entre perspectiva i axonomètrica
        
        desplacament = desplacament + glm::vec3(0.1,0,0);
          
      break;
      
      case Qt::Key_Up: // canvia òptica entre perspectiva i axonomètrica
        
        desplacament = desplacament + glm::vec3(0,0,-0.1);
        
      break;
      
      case Qt::Key_Down: // canvia òptica entre perspectiva i axonomètrica
          
        desplacament = desplacament + glm::vec3(0,0,0.1);
          
      break;
      
      case Qt::Key_1: // canvia òptica entre perspectiva i axonomètrica
        
        apagatE = not apagatE;
        if (apagatE) colorFE = glm::vec3(0,0,0);
        else colorFE = glm::vec3(0.8,0.8,0.0);
        glUniform3fv(colorfocusELoc, 1, &colorFE[0]);
          
      break;
      
      case Qt::Key_2: // canvia òptica entre perspectiva i axonomètrica
          
        apagatC = not apagatC;
        if (apagatC) colorFC = glm::vec3(0,0,0);
        else colorFC = glm::vec3(0.8,0.8,0.8);
        glUniform3fv(colorfocusCLoc, 1, &colorFC[0]);
        
      break;
      
      case Qt::Key_B: // canvia òptica entre perspectiva i axonomètrica
          
        faceCulling = not faceCulling;
        if (faceCulling) glEnable(GL_CULL_FACE);
        else glDisable(GL_CULL_FACE);
        
      break;
      
    default: BL3GLWidget::keyPressEvent(event); break;
  }
  update();
}

