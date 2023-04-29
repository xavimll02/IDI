#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLWidget>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include "glm/glm.hpp"

#include <QKeyEvent>
#include "glm/gtc/matrix_transform.hpp"

class MyGLWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
{
  Q_OBJECT

  public:
    MyGLWidget (QWidget *parent=0);
    ~MyGLWidget ();

  protected:
    // initializeGL - Aqui incluim les inicialitzacions del contexte grafic.
    virtual void initializeGL ();

    // paintGL - Mètode cridat cada cop que cal refrescar la finestra.
    // Tot el que es dibuixa es dibuixa aqui.
    virtual void paintGL ();

    // resize - Es cridat quan canvia la mida del widget
    virtual void resizeGL (int width, int height);

    virtual void keyPressEvent (QKeyEvent *e);

  private:
    void createBuffers1 ();
    void createBuffers2 ();
    void carregaShaders ();
    void modelTransform1 ();
    void modelTransform2 ();

    // attribute locations
    GLuint vertexLoc, transLoc;

    // Program
    QOpenGLShaderProgram *program;

    GLuint VAO1, VAO2;

    float rotate1, rotate2;
};
