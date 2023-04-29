/********************************************************************************
** Form generated from reading UI file 'MyForm.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYFORM_H
#define UI_MYFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDial>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLabel *label_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLCDNumber *lcdNumber;
    QLCDNumber *lcdNumber_2;
    QHBoxLayout *horizontalLayout_3;
    QDial *dial_2;
    QDial *dial;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QString::fromUtf8("Form"));
        Form->resize(437, 551);
        verticalLayout_3 = new QVBoxLayout(Form);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(Form);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(200, 100));
        label->setMaximumSize(QSize(200, 100));
        QFont font;
        font.setPointSize(24);
        label->setFont(font);

        horizontalLayout->addWidget(label);

        label_2 = new QLabel(Form);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(200, 100));
        label_2->setMaximumSize(QSize(200, 100));
        label_2->setFont(font);

        horizontalLayout->addWidget(label_2);


        verticalLayout_2->addLayout(horizontalLayout);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        lcdNumber = new QLCDNumber(Form);
        lcdNumber->setObjectName(QString::fromUtf8("lcdNumber"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lcdNumber->sizePolicy().hasHeightForWidth());
        lcdNumber->setSizePolicy(sizePolicy);
        lcdNumber->setMinimumSize(QSize(200, 100));
        lcdNumber->setMaximumSize(QSize(200, 100));
        lcdNumber->setSizeIncrement(QSize(0, 0));
        lcdNumber->setFont(font);
        lcdNumber->setDigitCount(3);

        horizontalLayout_2->addWidget(lcdNumber);

        lcdNumber_2 = new QLCDNumber(Form);
        lcdNumber_2->setObjectName(QString::fromUtf8("lcdNumber_2"));
        lcdNumber_2->setMinimumSize(QSize(200, 100));
        lcdNumber_2->setMaximumSize(QSize(200, 100));
        lcdNumber_2->setDigitCount(3);

        horizontalLayout_2->addWidget(lcdNumber_2);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        dial_2 = new QDial(Form);
        dial_2->setObjectName(QString::fromUtf8("dial_2"));
        dial_2->setMinimumSize(QSize(200, 100));
        dial_2->setMaximumSize(QSize(200, 100));
        dial_2->setMaximum(23);
        dial_2->setInvertedAppearance(false);
        dial_2->setInvertedControls(false);
        dial_2->setWrapping(false);
        dial_2->setNotchesVisible(false);

        horizontalLayout_3->addWidget(dial_2);

        dial = new QDial(Form);
        dial->setObjectName(QString::fromUtf8("dial"));
        dial->setMinimumSize(QSize(200, 100));
        dial->setMaximumSize(QSize(200, 100));
        dial->setMaximum(59);

        horizontalLayout_3->addWidget(dial);


        verticalLayout->addLayout(horizontalLayout_3);


        verticalLayout_2->addLayout(verticalLayout);


        verticalLayout_3->addLayout(verticalLayout_2);

        verticalSpacer = new QSpacerItem(20, 169, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        pushButton = new QPushButton(Form);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout_4->addWidget(pushButton);


        verticalLayout_3->addLayout(horizontalLayout_4);


        retranslateUi(Form);
        QObject::connect(dial_2, SIGNAL(sliderMoved(int)), lcdNumber, SLOT(display(int)));
        QObject::connect(dial, SIGNAL(sliderMoved(int)), lcdNumber_2, SLOT(display(int)));
        QObject::connect(pushButton, SIGNAL(clicked()), Form, SLOT(close()));

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QApplication::translate("Form", "Form", nullptr));
        label->setText(QApplication::translate("Form", "Hours", nullptr));
        label_2->setText(QApplication::translate("Form", "Minutes", nullptr));
        pushButton->setText(QApplication::translate("Form", "E&xit", nullptr));
#ifndef QT_NO_SHORTCUT
        pushButton->setShortcut(QApplication::translate("Form", "Alt+X", nullptr));
#endif // QT_NO_SHORTCUT
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYFORM_H
