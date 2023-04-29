// MyGLWidget.h
#include "BL2GLWidget.h"
#include "/home/xavi/Escritorio/Model/model.h"

class MyGLWidget : public BL2GLWidget {

    Q_OBJECT

public:
    MyGLWidget(QWidget *parent=0) : BL2GLWidget(parent) {}
    ~MyGLWidget();

public slots:
    void canviaAorto();
    void canviaApers();
    void assigna1();
    void assigna2();
    void assigna3();
    
signals:
    void seleccionaOrto();
    void seleccionaPers();
    void selecciona1();
    void selecciona2();
    void selecciona3();
    
protected:
    
    virtual void carregaShaders();
    virtual void creaBuffers();
    virtual void paintGL();
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void keyPressEvent(QKeyEvent* event); 
    
private:
    int printOglError(const char file[], int line, const char func[]);
    void projectTransform();
    void viewTransform(const glm::vec3& OBS, const glm::vec3& VRP, const glm::vec3& UP);
    QPair<glm::vec3,glm::vec3> calculaCapsaModel();
    void modelTransform1();
    void modelTransform2();
    
    void sphere(const glm::vec3& pmin, const glm::vec3& pmax);
    void ini_camera();
    
    GLuint projLoc, viewLoc, VAO_Patricio, VAO_Terra;
    glm::vec3 centroEscena;
    float radio;
    float FOV, FOVini, ra, znear, zfar;
    
    Model m;
    glm::vec3 centroAbajoModelo;
    QPair<glm::vec3,glm::vec3> pminmax;
    float h;
    
    int option;
};
