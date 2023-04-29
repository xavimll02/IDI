// MyGLWidget.h
#include "BL2GLWidget.h"
#include "/home/xavi/Escritorio/Model/model.h"

class MyGLWidget : public BL2GLWidget {

    Q_OBJECT

public:
    MyGLWidget(QWidget *parent=0) : BL2GLWidget(parent) {}
    ~MyGLWidget();

protected:
    
    virtual void carregaShaders();
    virtual void modelTransform(int option);
    virtual void creaBuffers();
    virtual void paintGL();
    virtual void initializeGL();
    virtual void keyPressEvent(QKeyEvent* event);
    
private:
    int printOglError(const char file[], int line, const char func[]);
    void projectTransform(float& FOV, float& ra, float& znear, float& zfar);
    void viewTransform(const glm::vec3& OBS, const glm::vec3& VRP, const glm::vec3& UP);
    void ini_camera();
    GLuint projLoc, viewLoc, VAO_Homer, VAO_Terra;
    Model m;
    float rota;
};
