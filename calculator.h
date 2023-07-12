#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "display.h"

#include <QMainWindow>
#include <QPushButton>
#include <QTextEdit>
#include <QLabel>
#include <QStack>
#include <QString>
#include <QGridLayout>
#include <QFont>
#include <QDebug>
#include <QKeyEvent>


QT_BEGIN_NAMESPACE
namespace Ui { class Calculator; }
QT_END_NAMESPACE

class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();
    QString calculate ();

    bool checkParentheses();
    bool isOperation(QChar c);
    int setPriority(char op);
    void action(char op);
    QString formula;

private:
    Ui::Calculator *ui;
    Display *display;
    QStack<double> numbers;
    QStack<char> operators;

     QPushButton* createButton (const QString& str, const QString &color, const char *member);
     const QString digitColor = "background-color: rgb(95, 93, 99);";
     const QString operatorColor = "background-color: rgb(215, 51, 154);";
     const QString serviceColor = "background-color: rgb(62, 61, 68);";

     enum { NumDigitButtons = 10 };
     QPushButton *digitButtons[NumDigitButtons];

     QPushButton *pointButton;
     QPushButton *clearButton;
     QPushButton *backspaseButton;

     QPushButton *divideButton;
     QPushButton *multiplyButton;
     QPushButton *minusButton;
     QPushButton *plusButton;
     QPushButton *powerButton;
     QPushButton *equalButton;

     QPushButton *openBracketButton;
     QPushButton *closeBracketButton;

     void setupPalette();
     void setupDisplay();
     void setupButtons();
     QGridLayout* setupLayout();

     void errorMessage(const QString& message);

     void keyPressEvent(QKeyEvent* event);
     bool isInputCharacterAllowed(QChar inputChar);
     void scrollTextLeft();
     void scrollTextRight();

private slots:

     void DigitOrOperatorClicked();
     void clear();
     void backspaseClicked();

     void equalClicked();
};
#endif // CALCULATOR_H
