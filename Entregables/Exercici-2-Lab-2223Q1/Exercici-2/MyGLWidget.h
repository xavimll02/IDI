#include "LL2GLWidget.h"

#include "model.h"

class MyGLWidget : public LL2GLWidget {
    
    Q_OBJECT

public:
    
    MyGLWidget(QWidget *parent=0) : LL2GLWidget(parent) {}
    ~MyGLWidget();
    
protected:
    
    virtual void RickTransform();
    virtual void PortalTransform();
    virtual void MortyTransform();
    virtual void iniCamera();
    virtual void iniEscena();
    virtual void viewTransform();
    virtual void projectTransform();
    virtual void mouseMoveEvent(QMouseEvent *e);
    virtual void mousePressEvent(QMouseEvent *e);
    virtual void keyPressEvent(QKeyEvent* event); 
    virtual void paintGL();
    virtual void carregaShaders();
    virtual void identTransform();
    
private:

    int printOglError(const char file[], int line, const char func[]);
    void MortyTransform2();     // MortyTransform2 paints the red Morty when Morty gets into the portal
    
    float y_ant, x_ant;                             // Previous pixel coordinates
    
    // Rick
    float angleRick = 180.0;                        // Rick angle
    glm::vec3 posRick = glm::vec3(-2.5,0.0,0.0);    // Rick position
    float angle_obertura_portal = 180.0;            // Angle that Rick has when he opens a portal
    
    // Morty
    glm::vec3 posMortyPortal;                       // Position that Morty has when he gets into the portal               
    float angleMortyPortal;                         // Angle that Morty has when he gets into the portal
    
    // Portal
    glm::vec3 pos_portal = glm::vec3(-2.5,0.0,-3.0);    // Portal position
    float anglePortal = 0.0;                            // Portal angle
    
    bool pintaPortal = true;                        // Bool indicating whether we paint the portal or not
    bool pintaMorty2 = false;                       // Bool indicating whether we paint the red Morty or not
    bool tpv = true;                                // Bool indicating whether we are in third person view or not
    
    GLuint ColorLoc;
};
