#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>

QT_BEGIN_NAMESPACE
namespace Ui { class Calculator; }
QT_END_NAMESPACE

class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();
    QPushButton* createButton (const QString& str, const char *member);
    void calculate ();

public slots:
    void DigitClicked ();

    void pointClicked();
    void clear();

    void devideOperatorClicked();
    void multiplyOperatorClicked();
    void percentOperatorClicked();
    void minusOperatorClicked();
    void plusOperatorClicked();
    void equalClicked();

    void openBracketClicked();
    void closeBracketClicked();

private:
    Ui::Calculator *ui;
    QLabel *display;

     enum { NumDigitButtons = 10 };
     QPushButton *digitButtons[NumDigitButtons];

     QPushButton *pointButton;
     QPushButton *clearButton;

     QPushButton *divideButton;
     QPushButton *multiplyButton;
     QPushButton *percentButton;
     QPushButton *minusButton;
     QPushButton *plusButton;
     QPushButton *equalButton;

     QPushButton *openBracketButton;
     QPushButton *closeBracketButton;

private slots:
    void digit_numbers();
};
#endif // CALCULATOR_H
