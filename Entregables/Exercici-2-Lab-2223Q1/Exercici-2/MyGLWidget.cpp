#include "MyGLWidget.h"
#include <iostream>
#include <stdio.h>
using namespace std;

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

void MyGLWidget::paintGL ()
{
  // descomentar per canviar paràmetres
  // glViewport (0, 0, ample, alt);

  // Esborrem el frame-buffer
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  // Rick
  glBindVertexArray (VAO_models[RICK]);
  RickTransform();
  glDrawArrays(GL_TRIANGLES, 0, models[RICK].faces().size()*3);

  // Morty
  glBindVertexArray (VAO_models[MORTY]);
  MortyTransform();
  glDrawArrays(GL_TRIANGLES, 0, models[MORTY].faces().size()*3);
  
  // If there's a Portal and Morty gets into it we provoke the desaparition of the portal and the painting of the Red Morty
  if (pintaPortal and MortyPortalTest(angle_obertura_portal*(M_PI/180.0), posMorty)) {
      pintaPortal = false;
      pintaMorty2 = true;
      posMortyPortal = posMorty;
      angleMortyPortal = angleMorty;
  }
  if (pintaMorty2) {
      MortyTransform2();
      glDrawArrays(GL_TRIANGLES, 0, models[MORTY].faces().size()*3);
  }
  
  // Portal
  if (pintaPortal) {
    glBindVertexArray (VAO_models[PORTAL]);
    PortalTransform();
    glDrawArrays(GL_TRIANGLES, 0, models[PORTAL].faces().size()*3);
  }
  
  // Terra
  glBindVertexArray (VAO_Terra);
  identTransform();
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

  glBindVertexArray (0);
}

void MyGLWidget::RickTransform() {
        
    glm::mat4 TG(1.0f);  
    TG = glm::translate(TG, posRick);                                       // We give Rick his actual position
    TG = glm::rotate(TG, angleRick*float(M_PI/180.0), glm::vec3(0,1.0,0));  // We give Rick his actual rotation
    TG = glm::scale(TG, glm::vec3(escalaModels[RICK]));
    TG = glm::translate(TG, -centreBaseModels[RICK]);
    glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
    glm::vec3 Color(1.0,1.0,1.0);           // For each model, we send a uniform to vertex shader. The vector that we send is chosen
    glUniform3fv(ColorLoc,1,&Color[0]);     // taking into account whether we want the model in its normal color or not
}

void MyGLWidget::PortalTransform ()
{
  glm::mat4 TG(1.0f);
  TG = glm::translate(TG, pos_portal);                                      // We give the portal its actual position
  TG = glm::rotate(TG, anglePortal*float(M_PI/180.0), glm::vec3(0,1.0,0));  // We give the portal its actual rotation
  TG = glm::scale(TG, glm::vec3(escalaModels[PORTAL]/4.0, escalaModels[PORTAL], escalaModels[PORTAL]));
  TG = glm::translate(TG, -centreBaseModels[PORTAL]);
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
  
  glm::vec3 Color(1.0,1.0,1.0);
  glUniform3fv(ColorLoc,1,&Color[0]);
}

void MyGLWidget::MortyTransform() {
 
    glm::mat4 TG(1.0f);
    TG = glm::translate(TG, posMorty);                                      // We give Morty its actual position
    TG = glm::rotate(TG, angleMorty*float(M_PI/180.0), glm::vec3(0,1.0,0)); // We give Morty its actual rotation
    TG = glm::scale(TG, glm::vec3(escalaModels[MORTY]));
    TG = glm::translate(TG, -centreBaseModels[MORTY]);
    TGMorty = TG;
    glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
    
    glm::vec3 Color(1.0,1.0,1.0);
    glUniform3fv(ColorLoc,1,&Color[0]);
}

void MyGLWidget::MortyTransform2() {
 
    glm::mat4 TG(1.0f);
    TG = glm::translate(TG, posMortyPortal);
    TG = glm::rotate(TG, angleMortyPortal*float(M_PI/180.0), glm::vec3(0,1.0,0));
    TG = glm::scale(TG, glm::vec3(escalaModels[MORTY]));
    TG = glm::translate(TG, -centreBaseModels[MORTY]);
    TGMorty = TG;
    glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
    
    glm::vec3 Red(1.0,0.0,0.0);                                             // For this Morty we multiply the model's color
    glUniform3fv(ColorLoc,1, &Red[0]);                                      // by red
}

void MyGLWidget::identTransform ()
{
  LL2GLWidget::identTransform();
  glm::vec3 Color(1.0,1.0,1.0);
  glUniform3fv(ColorLoc,1,&Color[0]);
}

void MyGLWidget::iniEscena()
{
  centreEscena = glm::vec3(0,1.5,0);                            // The center of the scene is (0,1.5,0) as it is centered at origen and its h is 3
  radiEscena = distance(centreEscena, glm::vec3(7.5,3.0,5.0));  // The radius of the scene is the distance from the center of the scene to one of
}                                                               // the corners that contains it

void MyGLWidget::iniCamera() {
  
  up = glm::vec3(0.0,1.0,0.0);
  vrp = centreEscena;
  obs = centreEscena + glm::vec3(0.0,0.0,1.0)*float(radiEscena*2.0);    // We locate the observer in a distance equal to two times the radius of the scene
  fov = 2 * asin(radiEscena / distance(obs,vrp));
  znear =  distance(obs,vrp) - radiEscena;
  zfar  = distance(obs,vrp) + radiEscena;
  ra = 1.0;
  
  factorAngleX = 0;
  factorAngleY = 0;
  
  viewTransform();
  projectTransform();
}

void MyGLWidget::viewTransform ()
{
  // Matriu de posició i orientació de l'observador
  glm::mat4 View(1.0f);
  
  // If we are in third person view we define a camera using Euler angles, initially setting it with a rotation of 45º in x axis. 
  if (tpv) {
    View = glm::translate(View, glm::vec3(0,0,-distance(obs,vrp)));
    View = glm::rotate(View, float(M_PI/4) + factorAngleX, glm::vec3(1.0,0.0,0.0));
    View = glm::rotate(View, -factorAngleY, glm::vec3(0.0,1.0,0.0));
    View = glm::translate(View, -vrp);
  }
  
  // If we are not in third person we define a less sofisticated perspective camera which points to where Rick is watching, with a height of 0.8 and Rick's position.
  // To know the position of the vrp we use trigonometry, supposing that Rick has a rotation of 90º and "he is already at the start of the second quadrant".
  // This technique is also used more below.
  else View = glm::lookAt(glm::vec3(-2.5,0.8,0.0), glm::vec3(-2.5,0.8,0.0)+glm::vec3(cos((angleRick-90.0)*M_PI/180.0)*3.0,0.0,-sin((angleRick-90.0)*M_PI/180.0)*3.0), up);
    
  glUniformMatrix4fv (viewLoc, 1, GL_FALSE, &View[0][0]);
}

void MyGLWidget::projectTransform () {
 
    glm::mat4 Proj(1.0f);
    Proj = glm::perspective (fov, ra, znear, zfar);
    glUniformMatrix4fv (projLoc, 1, GL_FALSE, &Proj[0][0]);
}

void MyGLWidget::keyPressEvent(QKeyEvent* event) 
{
    makeCurrent();
    switch (event->key()) {
        
        // For Up and Down, we compute the position where Morty has to go in function of his angle
        case Qt::Key_Up: { 
            posMorty = posMorty + glm::vec3(cos((angleMorty+270.0)*M_PI/180.0)*0.1,0.0,-sin((angleMorty+270.0)*M_PI/180.0)*0.1);    	
            break;
        }
        case Qt::Key_Down: {
            posMorty = posMorty - glm::vec3(cos((angleMorty+270.0)*M_PI/180.0)*0.1,0.0,-sin((angleMorty+270.0)*M_PI/180.0)*0.1);
            break;
        }
        // For left and Right, we rotate Morty 45 or -45 degrees
        case Qt::Key_Left: { 
            angleMorty = float(int(angleMorty + 45) % 360);    	
            break;
        }
        case Qt::Key_Right: {
            angleMorty = float(int(angleMorty - 45) % 360);
            break;
        }
        // For Q and E we rotate Rick and if we are in first person view we also change the orientation of the camera
        case Qt::Key_Q: {
            angleRick = float(int(angleRick + 45) % 360);
            if (not tpv) viewTransform();
            break;
        }
        case Qt::Key_E: {
            angleRick = float(int(angleRick - 45) % 360);
            if (not tpv) viewTransform();
            break;
        }
        // For P we open a portal in front of Rick and if it is already painted, we close it
        case Qt::Key_P: {
            if (abs(angleRick - anglePortal) == 180.0) pintaPortal = (not pintaPortal);
            else {
                pintaPortal = true;
                anglePortal = float(int(angleRick + 180) % 360);
                angle_obertura_portal = angleRick;
                pos_portal = posRick + glm::vec3(cos((angleRick-90.0)*M_PI/180.0)*3.0,0.0,-sin((angleRick-90.0)*M_PI/180.0)*3.0); 
            }
            break;
        }
        // For R we restablish all the variables that may have changed with the aim to return to the initial scene
        case Qt::Key_R: {
            
            tpv = true;
            pintaPortal = true;
            pintaMorty2 = false;
            anglePortal = 0.0;
            angle_obertura_portal = 180.0;
            pos_portal = glm::vec3(-2.5,0.0,-3.0);
            angleRick = 180.0;
            angleMorty = 0.0;
            posMorty = glm::vec3(1,0,0);
            factorAngleX = 0;
            factorAngleY = 0;
            fov = 2 * asin(radiEscena / distance(obs,vrp));
            znear =  distance(obs,vrp) - radiEscena;
            zfar  = distance(obs,vrp) + radiEscena;
            viewTransform();
            projectTransform();
            break;
        }
        // For C we define the projection parameters that we want for third person or first person view and then we update view transform and
        // project transform matrixes
        case Qt::Key_C: {
            
            tpv = not tpv;
            if (not tpv) {
                
                fov = float(M_PI/2.0);
                znear = 0.25;
                zfar = distance(glm::vec3(-2.5,0.8,0.0),glm::vec3(7.5,0.0,-7.5));
                viewTransform();
                projectTransform();
            }
            else {
                fov = 2 * asin(radiEscena / distance(obs,vrp));
                znear =  distance(obs,vrp) - radiEscena;
                zfar  = distance(obs,vrp) + radiEscena;
                viewTransform();
                projectTransform();
            }
            break;
        }
    default: event->ignore(); break;
    }
    update();
}

void MyGLWidget::mousePressEvent (QMouseEvent *e)
{
  xClick = e->x();
  yClick = e->y();

  if (e->button() & Qt::LeftButton &&
      ! (e->modifiers() & (Qt::ShiftModifier|Qt::AltModifier|Qt::ControlModifier)))
  {
      x_ant = xClick;   // This takes the coordinates of the mouse when we click its left button
      y_ant = yClick;
  }
}

void MyGLWidget::mouseMoveEvent(QMouseEvent *e)
{
  makeCurrent();
  
  // We only want this to have effect if we are in third person view
  if (tpv) {
    xClick = e->x();
    yClick = e->y();
    
    if (xClick != x_ant) factorAngleY -= (xClick - x_ant)*float(M_PI/180.0);    // We suppose that 1 pixel is 1º 
    if (yClick != y_ant) factorAngleX += (yClick - y_ant)*float(M_PI/180.0);    // and we make the transformation to radians
    
    x_ant = e->x();
    y_ant = e->y();
    
    viewTransform();
    update();
  }
}

void MyGLWidget::carregaShaders()
{
  LL2GLWidget::carregaShaders();
  ColorLoc = glGetUniformLocation (program->programId(), "Color");
}

MyGLWidget::~MyGLWidget()
{

}

