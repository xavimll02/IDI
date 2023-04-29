#include "MyLabel.h"

// constructor
MyLabel::MyLabel(QWidget *parent):QLabel(parent) {
    
    notaTotal = notaParcial = notaFinal = notaLaboratori = 0;
    apretats = bonus = 0;
}

void MyLabel::tractaNotaParcial(double nota) {
    
    notaTotal = notaFinal*0.5 + notaLaboratori*0.25;
    notaParcial = nota;
    notaTotal += notaParcial*0.25;
    if (notaLaboratori >= 4.5) {
        if (notaTotal + bonus < 5) setStyleSheet("color: red;");
        else setStyleSheet("color: green;");
        setNum(notaTotal + bonus);
    }
    
    else {
        if (notaTotal < 5) setStyleSheet("color: red;");
        else setStyleSheet("color: green;");
        setNum(notaTotal);
    }
    
    setObjectName(QString::number(notaTotal));
}

void MyLabel::tractaNotaFinal(double nota) {
 
    notaTotal = notaParcial*0.25 + notaLaboratori*0.25;
    notaFinal = nota;
    notaTotal += notaFinal*0.5;
    if (notaLaboratori >= 4.5) {
        if (notaTotal + bonus < 5) setStyleSheet("color: red;");
        else setStyleSheet("color: green;");
        setNum(notaTotal + bonus);
    }
    
    else {
        if (notaTotal < 5) setStyleSheet("color: red;");
        else setStyleSheet("color: green;");
        setNum(notaTotal);
    }
    
    setObjectName(QString::number(notaTotal));
}

void MyLabel::tractaNotaLaboratori(double nota) {
 
    notaTotal = notaParcial*0.25 + notaFinal*0.5;
    notaLaboratori = nota;
    notaTotal += notaLaboratori*0.25;
    if (notaLaboratori >= 4.5) {
        if (notaTotal + bonus < 5) setStyleSheet("color: red;");
        else setStyleSheet("color: green;");
        setNum(notaTotal + bonus);
    }
    
    else {
        if (notaTotal < 5) setStyleSheet("color: red;");
        else setStyleSheet("color: green;");
        setNum(notaTotal);
    }
    
    setObjectName(QString::number(notaTotal));
}

void MyLabel::tractaEntregues(bool apretat) {
    
    if (apretat) apretats++;
    else apretats--;
    
    if (apretats == 0) bonus = 0;
    else if (apretats == 1) bonus = 0.05;
    else if (apretats == 2) bonus = 0.22;
    else if (apretats == 3) bonus = 0.53;
    else bonus = 1;
    
    if (notaLaboratori >= 4.5) {
        if (notaTotal + bonus < 5) setStyleSheet("color: red;");
        else setStyleSheet("color: green;");
        setNum(notaTotal + bonus);
    }
    
    else {
        if (notaTotal < 5) setStyleSheet("color: red;");
        else setStyleSheet("color: green;");
        setNum(notaTotal);
    }
    
    setObjectName(QString::number(notaTotal));
}

void MyLabel::calculaNotaNecessaria(QString nota) {
    
    double nNecessaria = (5 - (nota.toDouble() - notaFinal*0.5))/0.5;
    if (nNecessaria >= 0) setNum((5 - (nota.toDouble() - notaFinal*0.5))/0.5);
    else setNum(0);
}

void MyLabel::resetejar() {
 
    notaTotal = notaParcial = notaFinal = notaLaboratori = 0;
    apretats = bonus = 0;
    setNum(0);
    setStyleSheet("color: red;");
}

void MyLabel::resetejar2() {
 
    setNum(10);
}


