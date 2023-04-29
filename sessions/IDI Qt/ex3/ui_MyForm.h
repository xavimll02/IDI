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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_4;
    QHBoxLayout *horizontalLayout;
    QRadioButton *radioButton;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_5;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *radioButton_2;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_6;
    QHBoxLayout *horizontalLayout_3;
    QRadioButton *radioButton_3;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *pushButton;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QString::fromUtf8("Form"));
        Form->resize(411, 300);
        verticalLayout = new QVBoxLayout(Form);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        radioButton = new QRadioButton(Form);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));
        radioButton->setMinimumSize(QSize(100, 0));

        horizontalLayout->addWidget(radioButton);

        label = new QLabel(Form);
        label->setObjectName(QString::fromUtf8("label"));
        label->setStyleSheet(QString::fromUtf8("background-color: rgb(239, 41, 41);"));

        horizontalLayout->addWidget(label);

        horizontalSpacer = new QSpacerItem(390, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        horizontalLayout_4->addLayout(horizontalLayout);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        radioButton_2 = new QRadioButton(Form);
        radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));
        radioButton_2->setMinimumSize(QSize(100, 0));

        horizontalLayout_2->addWidget(radioButton_2);

        label_2 = new QLabel(Form);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(0, 0));
        label_2->setStyleSheet(QString::fromUtf8("background-color: rgb(138, 226, 52);"));

        horizontalLayout_2->addWidget(label_2);

        horizontalSpacer_2 = new QSpacerItem(390, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        horizontalLayout_5->addLayout(horizontalLayout_2);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        radioButton_3 = new QRadioButton(Form);
        radioButton_3->setObjectName(QString::fromUtf8("radioButton_3"));
        radioButton_3->setMinimumSize(QSize(100, 0));

        horizontalLayout_3->addWidget(radioButton_3);

        label_3 = new QLabel(Form);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setAutoFillBackground(false);
        label_3->setStyleSheet(QString::fromUtf8("background-color: rgb(114, 159, 207);"));

        horizontalLayout_3->addWidget(label_3);


        horizontalLayout_6->addLayout(horizontalLayout_3);

        horizontalSpacer_3 = new QSpacerItem(390, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout_6);

        verticalSpacer = new QSpacerItem(20, 147, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_4);

        pushButton = new QPushButton(Form);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout_7->addWidget(pushButton);


        verticalLayout->addLayout(horizontalLayout_7);


        retranslateUi(Form);
        QObject::connect(pushButton, SIGNAL(clicked()), Form, SLOT(close()));
        QObject::connect(radioButton_3, SIGNAL(clicked(bool)), label_3, SLOT(setEnabled(bool)));
        QObject::connect(radioButton_3, SIGNAL(clicked(bool)), label_2, SLOT(setDisabled(bool)));
        QObject::connect(radioButton_3, SIGNAL(clicked(bool)), label, SLOT(setDisabled(bool)));
        QObject::connect(radioButton_2, SIGNAL(clicked(bool)), label_2, SLOT(setEnabled(bool)));
        QObject::connect(radioButton_2, SIGNAL(clicked(bool)), label_3, SLOT(setDisabled(bool)));
        QObject::connect(radioButton_2, SIGNAL(clicked(bool)), label, SLOT(setDisabled(bool)));
        QObject::connect(radioButton, SIGNAL(clicked(bool)), label, SLOT(setEnabled(bool)));
        QObject::connect(radioButton, SIGNAL(clicked(bool)), label_2, SLOT(setDisabled(bool)));
        QObject::connect(radioButton, SIGNAL(clicked(bool)), label_3, SLOT(setDisabled(bool)));

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QApplication::translate("Form", "Form", nullptr));
        radioButton->setText(QApplication::translate("Form", "Vermell", nullptr));
        label->setText(QApplication::translate("Form", "VERMELL", nullptr));
        radioButton_2->setText(QApplication::translate("Form", "Verd", nullptr));
        label_2->setText(QApplication::translate("Form", "VERD", nullptr));
        radioButton_3->setText(QApplication::translate("Form", "Blau", nullptr));
        label_3->setText(QApplication::translate("Form", "BLAU", nullptr));
        pushButton->setText(QApplication::translate("Form", "Exit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYFORM_H
