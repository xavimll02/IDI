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

void MyGLWidget::initializeGL ()
{
  // Cal inicialitzar l'ús de les funcions d'OpenGL
  initializeOpenGLFunctions();  

  glClearColor(0.5, 0.7, 1.0, 1.0); // defineix color de fons (d'esborrat)
  glEnable(GL_DEPTH_TEST);
  carregaShaders();
  creaBuffersPatricio();
  creaBuffersTerraIParet();
  
  glUniform3fv(posfocusLoc, 1, &posF[0]);
  glUniform3fv(colorfocusLoc, 1, &colorF[0]);
  iniEscena();
  iniCamera();
}

void MyGLWidget::iniMaterialTerra ()
{
  // Donem valors al material del terra
  amb = glm::vec3(0.2,0,0.2);
  diff = glm::vec3(0.0,0,0.8);
  spec = glm::vec3(1,1,1);
  shin = 100;
}

void MyGLWidget::carregaShaders()
{
  BL3GLWidget::carregaShaders();
  posfocusLoc = glGetUniformLocation(program->programId(), "posFocus");
  colorfocusLoc = glGetUniformLocation(program->programId(), "colorFocus");
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
      
      case Qt::Key_K: // canvia òptica entre perspectiva i axonomètrica
          if (not focusCamera) {
            posF = posF + glm::vec3(-0.1,0,0);
            glUniform3fv(posfocusLoc,1,&posF[0]);
          }
      break; 
      
      case Qt::Key_L: // canvia òptica entre perspectiva i axonomètrica
          if (not focusCamera) {
            posF = posF + glm::vec3(0.1,0,0);
            glUniform3fv(posfocusLoc,1,&posF[0]);
          }
      break;
      
      case Qt::Key_F: // canvia mode focus
          focusCamera = not focusCamera;
          if (focusCamera) {
            posF = glm::vec3(0,0,0);
            glUniform3fv(posfocusLoc,1,&posF[0]);
          }
          
          else {
            posF = View * glm::vec4(glm::vec3(1,1,1),1);
            glUniform3fv(posfocusLoc,1,&posF[0]);
          }
      break;
      
    default: BL3GLWidget::keyPressEvent(event); break;
  }
  update();
}

