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
    virtual void modelTransformPatricio();
    virtual void paintGL();
    
  private:
    int printOglError(const char file[], int line, const char func[]);
    GLuint posfocusCLoc, colorfocusCLoc, posfocusELoc, colorfocusELoc;
    glm::vec3 colorFC = glm::vec3(0.8, 0.8, 0.8);
    glm::vec3 posFC = glm::vec3(0, 0, 0);
    glm::vec3 colorFE = glm::vec3(0.8, 0.8, 0.0);
    glm::vec3 posFE;
    glm::vec3 desplacament = glm::vec3(0,-0.85,0);
    float esc;
    bool apagatE = false;
    bool apagatC = false;
    bool faceCulling = false;
};
