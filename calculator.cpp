#include "calculator.h"
#include "./ui_calculator.h"

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    display = new QLabel("0");
    display->setMinimumSize (150, 50);
    QGridLayout *myLayout = new QGridLayout;
    myLayout->addWidget(display, 0, 0, 1, 4);


    for (int i = 0; i < NumDigitButtons; ++i) {
      digitButtons[i] = createButton(QString::number(i), SLOT(DigitButtonClicked()));
     }

    ui->setupUi(this);
}

Calculator::~Calculator()
{
    delete ui;
}

QPushButton* Calculator::createButton (const QString& str, const char *member) {
 QPushButton* tempDigitButton = new QPushButton(str);
 tempDigitButton->setMinimumSize(60, 60);
 connect(tempDigitButton, SIGNAL(clicked()), this, member);
 return tempDigitButton;
}

void Calculator::DigitClicked()
{

}

void Calculator::pointClicked()
{

}

void Calculator::clear()
{

}

void Calculator::devideOperatorClicked()
{

}

void Calculator::multiplyOperatorClicked()
{

}

void Calculator::percentOperatorClicked()
{

}

void Calculator::minusOperatorClicked()
{

}

void Calculator::plusOperatorClicked()
{

}

void Calculator::equalClicked()
{

}

void Calculator::openBracketClicked()
{

}

void Calculator::closeBracketClicked()
{

}

