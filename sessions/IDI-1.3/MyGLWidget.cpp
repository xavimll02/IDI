#include "MyGLWidget.h"

#include <iostream>

MyGLWidget::MyGLWidget (QWidget* parent) : QOpenGLWidget(parent), program(NULL)
{
  setFocusPolicy(Qt::StrongFocus);  // per rebre events de teclat
}

MyGLWidget::~MyGLWidget ()
{
  if (program != NULL)
    delete program;
}

void MyGLWidget::initializeGL ()
{
  // Cal inicialitzar l'ús de les funcions d'OpenGL
  initializeOpenGLFunctions();

  glClearColor (0.5, 0.7, 1.0, 1.0); // defineix color de fons (d'esborrat)
  carregaShaders();
  createBuffers1();
  createBuffers2();
}

void MyGLWidget::paintGL ()
{
  glClear (GL_COLOR_BUFFER_BIT);  // Esborrem el frame-buffer

  glViewport (0, 0, width(), height()); // Aquesta crida no cal, Qt la fa de forma automàtica amb aquests paràmetres

  modelTransform1();
  // Activem l'Array a pintar VAO1
  glBindVertexArray(VAO1);
  // Pintem l'escena VAO1
  glDrawArrays(GL_TRIANGLES, 0, 3);

  //glBindVertexArray(0);

  modelTransform2();
  // Activem l'Array a pintar VAO2
  glBindVertexArray(VAO2);
  // Pintem l'escena VAO2
  glDrawArrays(GL_TRIANGLES, 0, 3);

  // Desactivem els VAOs
  glBindVertexArray(0);
}

void MyGLWidget::resizeGL (int w, int h)
{
  // Aquí anirà el codi que cal fer quan es redimensiona la finestra
}

void MyGLWidget::createBuffers1 ()
{
  glm::vec3 Vertices[3];  // Tres vèrtexs amb X, Y i Z
  Vertices[0] = glm::vec3(-0.5, 0.0, 0.0);
  Vertices[1] = glm::vec3(-0.5, -0.5, 0.0);
  Vertices[2] = glm::vec3(0.0, -0.5, 0.0);

  // Creació del Vertex Array Object (VAO) que usarem per pintar
  glGenVertexArrays(1, &VAO1);
  glBindVertexArray(VAO1);

  // Creació del buffer amb les dades dels vèrtexs
  GLuint VBO1;
  glGenBuffers(1, &VBO1);
  glBindBuffer(GL_ARRAY_BUFFER, VBO1);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
  // Activem l'atribut que farem servir per vèrtex
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);

  // Desactivem el VAO
  glBindVertexArray(0);
}

void MyGLWidget::createBuffers2 ()
{
  glm::vec3 Vertices[3];  // Tres vèrtexs amb X, Y i Z
  Vertices[0] = glm::vec3(0.25, 0.0, 0.0);
  Vertices[1] = glm::vec3(0.0, -0.25, 0.0);
  Vertices[2] = glm::vec3(0.5, -0.25, 0.0);


  // Creació del Vertex Array Object (VAO) que usarem per pintar
  glGenVertexArrays(1, &VAO2);
  glBindVertexArray(VAO2);

  // Creació del buffer amb les dades dels vèrtexs
  GLuint VBO1;
  glGenBuffers(1, &VBO1);
  glBindBuffer(GL_ARRAY_BUFFER, VBO1);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
  // Activem l'atribut que farem servir per vèrtex
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);

  // Desactivem el VAO
  glBindVertexArray(0);
}

void MyGLWidget::carregaShaders()
{
  // Creem els shaders per al fragment shader i el vertex shader
  QOpenGLShader fs (QOpenGLShader::Fragment, this);
  QOpenGLShader vs (QOpenGLShader::Vertex, this);
  // Carreguem el codi dels fitxers i els compilem
  fs.compileSourceFile("shaders/basicShader.frag");
  vs.compileSourceFile("shaders/basicShader.vert");
  // Creem el program
  program = new QOpenGLShaderProgram(this);
  // Li afegim els shaders corresponents
  program->addShader(&fs);
  program->addShader(&vs);
  // Linkem el program
  program->link();
  // Indiquem que aquest és el program que volem usar
  program->bind();

  // Obtenim identificador per a l'atribut “vertex” del vertex shader
  vertexLoc = glGetAttribLocation (program->programId(), "vertex");
  transLoc = glGetUniformLocation(program->programId(), "TG");
}

void MyGLWidget::modelTransform1 () {
	glm::mat4 TG(1.0);
	TG = glm::rotate(TG, rotate1, glm::vec3(0.0, 0.0, 1.0));
	glUniformMatrix4fv(transLoc, 1,GL_FALSE, &TG[0][0]);
}

void MyGLWidget::modelTransform2 () {
	glm::mat4 TG(1.0);
	TG = glm::rotate(TG, rotate2, glm::vec3(0.0, 0.0, 1.0));
	glUniformMatrix4fv(transLoc, 1,GL_FALSE, &TG[0][0]);
}

void MyGLWidget::keyPressEvent(QKeyEvent *e) {
	makeCurrent();
	switch (e->key()) {
		case Qt::Key_P:
			rotate1 += float(M_PI/6.0);
			rotate2 -= float(M_PI/6.0);
			break;
		default: e->ignore();
	}
	update();
}
