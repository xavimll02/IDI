#include <QLabel>
class MyLabel: public QLabel
{
    Q_OBJECT
public:
    MyLabel(QWidget *parent);
    double notaTotal, notaParcial, notaFinal, notaLaboratori;
    double apretats, bonus;
public slots:

    void tractaNotaParcial(double nota);
    void tractaNotaFinal(double nota);
    void tractaNotaLaboratori(double nota);
    void tractaEntregues(bool apretat);
    void calculaNotaNecessaria(QString nota);
    void resetejar();
    void resetejar2();
};

