#include "calculator.h"
#include "display.h"
#include "./ui_calculator.h"
#include <QDialog>

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::Calculator) {
    setStyleSheet("background-color: rgb(42, 40, 49);");

    setupDisplay();

    setupButtons();

    setFixedSize(sizeHint());

    formula = "";

    QGridLayout *Layout = setupLayout();

    QWidget* centralWidget = new QWidget;
    centralWidget->setLayout(Layout);
    setCentralWidget(centralWidget);
}

Calculator::~Calculator() { delete ui; }

QPushButton* Calculator::createButton (const QString& str, const QString &color, const char *member) {
 QPushButton* tempDigitButton = new QPushButton(str);
 tempDigitButton->setMinimumSize(60, 50);

 QFont font("Helvetica [Cronyx]", 23);
 tempDigitButton->setFont(font);

 QString styleSheet = QString("QPushButton {"
                              "%1"
                              "border: none;"
                              "text-align: center;"
                              "}"
                              "QPushButton:pressed {"
                              "background-color: rgb(161, 160, 161);"
                              "}").arg(color);

 tempDigitButton->setStyleSheet(styleSheet);
 connect(tempDigitButton, SIGNAL(clicked()), this, member);

 return tempDigitButton;
}

void Calculator::DigitOrOperatorClicked() {
    QString str = ((QPushButton*)sender())->text();
    if(str == "÷") formula += "/";
    else if (str == "×") formula += "*";
    else formula += str;

    display->setText(formula);
}

void Calculator::clear() {
    display->setText("0");

    numbers.clear();
    operators.clear();

    formula = "";

}

void Calculator::backspaseClicked() {
    formula.chop(1);
    display->setText(formula);
}

void Calculator::equalClicked(){

    QString result = calculate();
    display->setText(result);

    numbers.clear();
    operators.clear();
    if(result == "nan" || result == "0")formula = "";
   else formula = result;
}


void Calculator::setupDisplay() {
    display = new Display(this);
    display->setMaximumSize (311, 65);
    QFont font("Helvetica [Cronyx]", 44, QFont::Cursive);
    display->setFont(font);
}

void Calculator::setupButtons() {
    for (int i = 0; i < NumDigitButtons; ++i) {
      digitButtons[i] = createButton(QString::number(i), digitColor, SLOT(DigitOrOperatorClicked()));
     }

    equalButton = createButton(tr("="), operatorColor, SLOT(equalClicked()));
    clearButton = createButton(tr("AC"), serviceColor, SLOT(clear()));

    backspaseButton = createButton(tr("⌫"), serviceColor, SLOT(backspaseClicked()));

    pointButton = createButton(tr("."), digitColor, SLOT(DigitOrOperatorClicked()));

    powerButton = createButton(tr("^"), operatorColor, SLOT(DigitOrOperatorClicked()));
    divideButton = createButton(tr("÷"), operatorColor, SLOT(DigitOrOperatorClicked()));
    multiplyButton = createButton(tr("×"), operatorColor, SLOT(DigitOrOperatorClicked()));
    minusButton = createButton(tr("-"), operatorColor, SLOT(DigitOrOperatorClicked()));
    plusButton = createButton(tr("+"), operatorColor, SLOT(DigitOrOperatorClicked()));

    openBracketButton = createButton(tr("("), serviceColor, SLOT(DigitOrOperatorClicked()));
    closeBracketButton = createButton(tr(")"), serviceColor, SLOT(DigitOrOperatorClicked()));
}

QGridLayout* Calculator::setupLayout()
{
    QGridLayout *tempLayout = new QGridLayout;
    tempLayout->setContentsMargins(0, 0, 0, 0);
    tempLayout->setSizeConstraint(QLayout::SetFixedSize);
    tempLayout->setSpacing(1);

    tempLayout->addWidget(display, 0, 0, 1, 6);

    for (int i = 1; i < NumDigitButtons; ++i) {
      int row = ((9 - i) / 3) + 2;
      int column = ((i - 1) % 3) + 1;
      tempLayout->addWidget(digitButtons[i], row, column);
     }

    tempLayout->addWidget(equalButton, 5, 4, 1, 2);
    tempLayout->addWidget(clearButton, 1, 1, 1, 2);

    tempLayout->addWidget(backspaseButton, 1, 5);

    tempLayout->addWidget(pointButton, 5, 3);

    tempLayout->addWidget(digitButtons[0], 5, 1, 1, 2);

    tempLayout->addWidget(multiplyButton, 4, 5);
    tempLayout->addWidget(plusButton, 3, 5);
    tempLayout->addWidget(powerButton, 2, 4, 1, 2);
    tempLayout->addWidget(minusButton, 3, 4);
    tempLayout->addWidget(divideButton, 4, 4);

    tempLayout->addWidget(openBracketButton, 1, 3);
    tempLayout->addWidget(closeBracketButton, 1, 4);



    return tempLayout;
}

bool Calculator::checkParentheses() {
    int openCount = 0, closeCount = 0;

    for (QChar c : formula) {
       if (c == '(') { openCount++; }
       else if (c == ')') {  closeCount++; }
    }

    return openCount == closeCount;
}

bool Calculator::isOperation(QChar c) {return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';}

int Calculator::setPriority(char op) {
    if (op < 0) { return 3; }
    else {
       if (op == '+' || op == '-') return 1;
       else if (op == '*' || op == '/') return 2;
       else if (op == '^') return 4;
       else return -1;
    }
}

void Calculator::action(char op) {
    if (numbers.size() == 0) { return; }
    else if (op < 0) {
        double unaryNum = numbers.pop();
        if (-op == '-') { numbers.push(-unaryNum); }
        else { numbers.push(unaryNum); }
    } else {
        if (numbers.size() < 2) { return; }
        double right = numbers.pop();
        double left = numbers.pop();
        if (op == '/' && right == 0) {
            numbers.push(std::numeric_limits<double>::quiet_NaN());
        } else {
            switch (op) {
                case '+': numbers.push(left + right); break;
                case '-': numbers.push(left - right); break;
                case '*': numbers.push(left * right); break;
                case '/': numbers.push(left / right); break;
                case '^': numbers.push(std::pow(left, right)); break;
            }
        }
    }
}


QString Calculator::calculate() {
    if (!checkParentheses()){
      errorMessage("Несовпадение скобок!");
      return "";
    }

    bool unary = true;
    numbers.clear();
    operators.clear();

for (int i = 0; i < formula.size(); i++) {
    QChar currentChar = formula[i];

    if (currentChar == '(') {
        operators.push('(');
        unary = true;
    } else if (currentChar == ')') {
        while (operators.top() != '(') {
            action(operators.pop());
        }
        operators.pop();
        unary = false;

    } else if (isOperation(currentChar)) {
        char operation = currentChar.toLatin1();

        if (unary) { operation = -operation; }

        while (!operators.empty() && setPriority(operators.top()) >= setPriority(operation)) {
            action(operators.pop());
        }
        operators.push(operation);
        unary = true;

    } else if (currentChar.isDigit() || currentChar == '.') {
        QString number;
        while (i < formula.size() && (formula[i].isDigit() || formula[i] == '.')) {
            number += formula[i];
            i++;
        }
        i--;
        numbers.push(number.toDouble());
        unary = false;
    }
}

while (!operators.empty()) { action(operators.pop()); }


    double result = numbers.pop();

    if (std::isnan(result)) { return "nan"; }
    else { return QString::number(result); }
}

void Calculator::errorMessage(const QString& message) {
    QDialog dialog;
    dialog.setWindowTitle("Ошибка");

    QFont font("Helvetica [Cronyx]", 24);

    QLabel label(message);
    label.setFont(font);

    QVBoxLayout layout(&dialog);
    layout.addWidget(&label);

    dialog.exec();
}

void Calculator::keyPressEvent(QKeyEvent* event) {
    switch (event->key()) {
        case Qt::Key_Left:
            scrollTextLeft();
            break;
        case Qt::Key_Right:
            scrollTextRight();
            break;
        default:
        QString inputText = event->text();
        if (!inputText.isEmpty()) {
            QChar inputChar = inputText.at(0);
            if (isInputCharacterAllowed(inputChar)) {
                formula += inputChar;
                display->setText(formula);
            }
        }
            break;
    }
    QMainWindow::keyPressEvent(event);
}

bool Calculator::isInputCharacterAllowed(QChar inputChar) {
    QString allowedCharacters = "0123456789+-*/().^";

    return allowedCharacters.contains(inputChar);
}

void Calculator::scrollTextLeft() {
    QTextCursor cursor = display->textCursor();
    cursor.movePosition(QTextCursor::Left, QTextCursor::MoveAnchor);
    display->setTextCursor(cursor);
}

void Calculator::scrollTextRight() {
    QTextCursor cursor = display->textCursor();
    cursor.movePosition(QTextCursor::Right, QTextCursor::MoveAnchor);
    display->setTextCursor(cursor);
}
