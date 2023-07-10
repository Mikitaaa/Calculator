#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QFont>
#include <QtGui/QPalette>
#include <QtGui/QBrush>
#include <QtGui/QColor>

QT_BEGIN_NAMESPACE
namespace Ui { class Calculator; }
QT_END_NAMESPACE

class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();
    void calculate ();

private:
    Ui::Calculator *ui;
    QLabel *display;

     QPushButton* createButton (const QString& str, const QString &color, const char *member);
     const QString digitColor = "background-color: rgb(100, 100, 102);";
     const QString operatorColor = "background-color: rgb(215, 51, 154);";
     const QString serviceColor = "background-color: rgb(70, 70, 71);";

     enum { NumDigitButtons = 10 };
     QPushButton *digitButtons[NumDigitButtons];

     QPushButton *pointButton;
     QPushButton *clearButton;

     QPushButton *divideButton;
     QPushButton *multiplyButton;
     QPushButton *minusButton;
     QPushButton *plusButton;
     QPushButton *equalButton;

     QPushButton *openBracketButton;
     QPushButton *closeBracketButton;

     void setupPalette();
     void setupDisplay();
     void setupButtons();
     QGridLayout* setupLayout();

private slots:
     void DigitClicked ();

     void pointClicked();
     void clear();

     void devideOperatorClicked();
     void multiplyOperatorClicked();
     void minusOperatorClicked();
     void plusOperatorClicked();
     void equalClicked();

     void openBracketClicked();
     void closeBracketClicked();

};
#endif // CALCULATOR_H
