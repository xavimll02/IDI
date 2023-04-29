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
  glEnable(GL_CULL_FACE);
  
  carregaShaders();
  
  creaBuffersMorty();
  creaBuffersFantasma();
  creaBuffersTerraIParets();

  iniEscena();
  iniCamera();
  posFE1 = glm::vec3(0,6,0);
  colFE1 = glm::vec3(0.7,0,0.7);
  posFE2 = glm::vec3(0,6,10);
  colFE2 = glm::vec3(0.7,0,0.7);
  posFE3 = glm::vec3(10,6,0);
  colFE3 = glm::vec3(0.7,0,0.7);
  posFE4 = glm::vec3(10,6,10);
  colFE4 = glm::vec3(0.7,0,0.7);
  posFM = glm::vec3(60,-90,-7);
  colFM = glm::vec3(0.9,0.9,0);
}

void MyGLWidget::paintGL ()
{

  TGM = glm::translate(glm::mat4(1.f), glm::vec3(5,0,5));
  TGM = glm::rotate(TGM, float(glm::radians(angleMorty)),glm::vec3(0.f, 1.f, 0.f));
  TGM = glm::rotate(TGM, float(glm::radians(90.0)),glm::vec3(0.f, 1.f, 0.f));
  TGM = glm::scale(TGM, glm::vec3(escalaMorty, escalaMorty, escalaMorty));
  TGM = glm::translate(TGM, -centreBaseMorty);
  glUniformMatrix4fv(transMLoc, 1, GL_FALSE, &TGM[0][0]);
  glUniform3fv(posFE1Loc, 1, &posFE1[0]);
  glUniform3fv(colFE1Loc, 1, &colFE1[0]);
  glUniform3fv(posFE2Loc, 1, &posFE2[0]);
  glUniform3fv(colFE2Loc, 1, &colFE2[0]);
  glUniform3fv(posFE3Loc, 1, &posFE3[0]);
  glUniform3fv(colFE3Loc, 1, &colFE3[0]);
  glUniform3fv(posFE4Loc, 1, &posFE4[0]);
  glUniform3fv(colFE4Loc, 1, &colFE4[0]);
  glUniform3fv(posFMLoc, 1, &posFM[0]);
  glUniform3fv(colFMLoc, 1, &colFM[0]);
  
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // TERRA
  glBindVertexArray (VAO_Terra);
  modelTransformTerra ();
  glDrawArrays(GL_TRIANGLES, 0, 30);
  
  // MORTY
  glBindVertexArray (VAO_Morty);
  modelTransformMorty ();
  glDrawArrays(GL_TRIANGLES, 0, morty.faces().size()*3);
  
  // FANTASMA
  if (apagatE and not mira) {
    glBindVertexArray (VAO_Fantasma);
    modelTransformFantasma ();
    glDrawArrays(GL_TRIANGLES, 0, fantasma.faces().size()*3);
  }
  glBindVertexArray(0);
}

void MyGLWidget::modelTransformMorty()
{
  TG_morty = glm::translate(glm::mat4(1.f), glm::vec3(5,0,5));
  TG_morty = glm::rotate(TG_morty, float(glm::radians(angleMorty)),glm::vec3(0.f, 1.f, 0.f));
  TG_morty = glm::rotate(TG_morty, float(glm::radians(90.0)),glm::vec3(0.f, 1.f, 0.f));
  TG_morty = glm::scale(TG_morty, glm::vec3(escalaMorty, escalaMorty, escalaMorty));
  TG_morty = glm::translate(TG_morty, -centreBaseMorty);
  
  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG_morty[0][0]);
}

void MyGLWidget::modelTransformFantasma ()
{
  glm::mat4 TG;
  TG = glm::translate(glm::mat4(1.f), glm::vec3(1 + desplacament_boo,0.5,5));
  TG = glm::rotate(TG, float(glm::radians(90.0)),glm::vec3(0.f, 1.f, 0.f));
  TG = glm::scale(TG, glm::vec3(escalaFantasma, escalaFantasma, escalaFantasma));
  TG = glm::translate(TG, -centreBaseFantasma);
  
  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::carregaShaders()
{
  LL4GLWidget::carregaShaders();
  posFE1Loc = glGetUniformLocation(program->programId(), "posFocusE1");
  colFE1Loc = glGetUniformLocation(program->programId(), "colorFocusE1");
  posFE2Loc = glGetUniformLocation(program->programId(), "posFocusE2");
  colFE2Loc = glGetUniformLocation(program->programId(), "colorFocusE2");
  posFE3Loc = glGetUniformLocation(program->programId(), "posFocusE3");
  colFE3Loc = glGetUniformLocation(program->programId(), "colorFocusE3");
  posFE4Loc = glGetUniformLocation(program->programId(), "posFocusE4");
  colFE4Loc = glGetUniformLocation(program->programId(), "colorFocusE4");
  posFMLoc = glGetUniformLocation(program->programId(), "posFocusM");
  colFMLoc = glGetUniformLocation(program->programId(), "colorFocusM");
  transMLoc = glGetUniformLocation(program->programId(), "TGM");
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

void MyGLWidget::reinicia() {
 
    angleMorty = 0;
    apagatM = false;
    apagatE = false;
    mira = false;
    desplacament_boo = 0;
    colFE1 = glm::vec3(0.7,0.0,0.7);
    colFE2 = glm::vec3(0.7,0.0,0.7);
    colFE3 = glm::vec3(0.7,0.0,0.7);
    colFE4 = glm::vec3(0.7,0.0,0.7);
    colFM = glm::vec3(0.9,0.9,0.0);
}

void MyGLWidget::keyPressEvent(QKeyEvent* event) {
  makeCurrent();
  switch (event->key()) {
  case Qt::Key_A: {
      
      angleMorty = float((int(angleMorty) + 45) % 360);
      mira = abs(180.0 - angleMorty) < 90.0;
      if (not mira) desplacament_boo += 0.5;
      if (5.0 - (desplacament_boo + 1.0) <= 0.5) reinicia();
      
    break;
	}
  case Qt::Key_D: {
      
      if (angleMorty == 0.0) angleMorty = 360.0;
      angleMorty = float(int(angleMorty) - 45);
      mira = abs(180.0 - angleMorty) < 90.0;
      if (not mira) desplacament_boo += 0.5;
      if (5.0 - (desplacament_boo + 1.0) <= 0.5) reinicia();
      
    break;
	}
  case Qt::Key_M: {
      
      apagatM = not apagatM;
      if (apagatM) colFM = glm::vec3(0.0,0.0,0.0);
      else colFM = glm::vec3(0.9,0.9,0.0);
      
    break;
	}
  case Qt::Key_E: {
      
      apagatE = not apagatE;
      if (apagatE) {
          colFE1 = glm::vec3(0.0,0.0,0.0);
          colFE2 = glm::vec3(0.0,0.0,0.0);
          colFE3 = glm::vec3(0.0,0.0,0.0);
          colFE4 = glm::vec3(0.0,0.0,0.0);
      }
      else {
          colFE1 = glm::vec3(0.7,0.0,0.7);
          colFE2 = glm::vec3(0.7,0.0,0.7);
          colFE3 = glm::vec3(0.7,0.0,0.7);
          colFE4 = glm::vec3(0.7,0.0,0.7);
      }
      
    break;
	}	
  default: LL4GLWidget::keyPressEvent(event); break;
  }
  update();
}
