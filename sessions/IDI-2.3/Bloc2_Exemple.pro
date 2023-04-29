TEMPLATE    = app
QT         += opengl 

INCLUDEPATH +=  /usr/include/glm /home/xavi/Escritorio/Model

FORMS += MyForm.ui

HEADERS += MyForm.h BL2GLWidget.h MyGLWidget.h /home/xavi/Escritorio/Model/model.h

SOURCES += main.cpp MyForm.cpp \
        BL2GLWidget.cpp MyGLWidget.cpp /home/xavi/Escritorio/Model/model.cpp
