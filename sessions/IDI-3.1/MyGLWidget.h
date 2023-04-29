// MyGLWidget.h
#include "BL3GLWidget.h"
#include "glm/gtc/matrix_inverse.hpp"

class MyGLWidget : public BL3GLWidget {
  Q_OBJECT

  public:
    MyGLWidget(QWidget *parent=0) : BL3GLWidget(parent) {}
    ~MyGLWidget();

  protected:
    virtual void initializeGL();
    virtual void mouseMoveEvent(QMouseEvent *e);
    virtual void keyPressEvent(QKeyEvent* event);
    virtual void iniMaterialTerra();
    virtual void carregaShaders();

  private:
    int printOglError(const char file[], int line, const char func[]);
    GLuint posfocusLoc, colorfocusLoc;
    glm::vec3 colorF = glm::vec3(0.8, 0.8, 0.8);
    glm::vec3 posF = glm::vec3(1, 1, 1); 
};
