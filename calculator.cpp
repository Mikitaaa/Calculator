#include "calculator.h"
#include "./ui_calculator.h"

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::Calculator) {

    setupPalette();

    setupDisplay();

    setupButtons();

    QGridLayout *Layout = setupLayout();

    QWidget* centralWidget = new QWidget;
    centralWidget->setLayout(Layout);
    setCentralWidget(centralWidget);
}

Calculator::~Calculator()
{
    delete ui;
}

QPushButton* Calculator::createButton (const QString& str, const char *member) {
 QPushButton* tempDigitButton = new QPushButton(str);
 tempDigitButton->setMinimumSize(60, 50);
 QFont font("Helvetica [Cronyx]", 20);
 tempDigitButton->setFont(font);
 tempDigitButton->setStyleSheet("QPushButton {"
                                "background-color: rgb(95, 94, 99);"
                                "border: 0px solid rgb(43, 41, 48);"
                                "padding: 10px;"
                                "}"
                                "QPushButton:pressed {"
                                "background-color: rgb(161, 160, 161);"
                                "}");
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

void Calculator::setupPalette() {
    QPalette palette;
    QBrush brush(QColor(48, 45, 50));
    palette.setBrush(QPalette::Background, brush);
    this->setPalette(palette);
}

void Calculator::setupDisplay() {
    display = new QLabel("0");
    display->setMinimumSize (150, 55);
    display->setAlignment(Qt::AlignRight | Qt::AlignBottom);
    QFont font("Helvetica [Cronyx]", 44, QFont::Cursive);
    display->setFont(font);
}

void Calculator::setupButtons() {
    for (int i = 0; i < NumDigitButtons; ++i) {
      digitButtons[i] = createButton(QString::number(i), SLOT(DigitClicked()));
     }
    pointButton = createButton(tr("."), SLOT(pointClicked()));
    clearButton = createButton(tr("AC"), SLOT(clear()));
    divideButton = createButton(tr("÷"), SLOT(devideOperatorClicked()));
    multiplyButton = createButton(tr("*"), SLOT(multiplyOperatorClicked()));
    minusButton = createButton(tr("-"), SLOT(minusOperatorClicked()));
    plusButton = createButton(tr("+"), SLOT(plusOperatorClicked()));
    percentButton = createButton(tr("%"), SLOT(percentOperatorClicked()));
    equalButton = createButton(tr("="), SLOT(equalClicked()));
    openBracketButton = createButton(tr("("), SLOT(openBracketClicked()));
    closeBracketButton = createButton(tr(")"), SLOT(closeBracketClicked()));
}

QGridLayout* Calculator::setupLayout()
{
    QGridLayout *tempLayout = new QGridLayout;
    tempLayout->setContentsMargins(0, 0, 0, 0);
    tempLayout->setSizeConstraint(QLayout::SetFixedSize);
    tempLayout->setSpacing(1);

    tempLayout->addWidget(display, 0, 0, 1, 6);
    tempLayout->addWidget(clearButton, 1, 1, 1, 1);

    for (int i = 1; i < NumDigitButtons; ++i) {
      int row = ((9 - i) / 3) + 2;
      int column = ((i - 1) % 3) + 1;
      tempLayout->addWidget(digitButtons[i], row, column);
     }

    tempLayout->addWidget(digitButtons[0], 5, 1);
    tempLayout->addWidget(pointButton, 5, 2);
    tempLayout->addWidget(divideButton, 2, 4);
    tempLayout->addWidget(multiplyButton, 3, 4);
    tempLayout->addWidget(minusButton, 4, 4);
    tempLayout->addWidget(plusButton, 5, 4);
    tempLayout->addWidget(percentButton, 1, 2);
    tempLayout->addWidget(equalButton, 5, 3);
    tempLayout->addWidget(openBracketButton, 1, 3);
    tempLayout->addWidget(closeBracketButton, 1, 4);

    return tempLayout;
}
