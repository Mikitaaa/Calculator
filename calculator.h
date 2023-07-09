#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class Calculator; }
QT_END_NAMESPACE

class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();
    QPushButton* createButton (const QString& str);
    void calculate ();

public slots:
    void ButtonClicked ();

private:
    Ui::Calculator *ui;
    QLabel *displaystr;

     enum { NumDigitButtons = 10 };
     QPushButton *digitButtons[NumDigitButtons];

     QPushButton *pointButton;
     QPushButton *clearButton;

     QPushButton *divideButton;
     QPushButton *minusButton;
     QPushButton *plusButton;
     QPushButton *multiplyButton;
     QPushButton *equalButton;
     QPushButton *percentButton;

     QPushButton *openBracketButton;
     QPushButton *closeBracketButton;

private slots:
    void digit_numbers();
};
#endif // CALCULATOR_H
