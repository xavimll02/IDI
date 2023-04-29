// MyGLWidget.h
#include "LL4GLWidget.h"

class MyGLWidget : public LL4GLWidget {
  Q_OBJECT
  public:
    MyGLWidget(QWidget *parent=0) : LL4GLWidget(parent) {}
    ~MyGLWidget();
  protected:
    virtual void mouseMoveEvent(QMouseEvent *e);
    virtual void keyPressEvent(QKeyEvent* event);
    virtual void paintGL();
    virtual void initializeGL();
    virtual void modelTransformMorty ();
    virtual void modelTransformFantasma ();
    
  private:
    int printOglError(const char file[], int line, const char func[]);
    void carregaShaders();
    void reinicia();
    GLuint posFE1Loc, colFE1Loc, posFE2Loc, colFE2Loc, posFE3Loc, colFE3Loc, posFE4Loc, colFE4Loc, posFMLoc, colFMLoc, transMLoc;
    glm::vec3 posFE1, colFE1, posFE2, colFE2, posFE3, colFE3, posFE4, colFE4, posFM, colFM;
    glm::mat4 TGM;
    float angleMorty = 0;
    bool apagatM = false;
    bool apagatE = false;
    bool mira = false;
    float desplacament_boo = 0;
};
