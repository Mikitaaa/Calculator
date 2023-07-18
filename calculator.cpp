#include "calculator.h"
#include "display.h"
#include "./ui_calculator.h"
#include <QDialog>

// Setup main window
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

// Create a QPushButton with the specified text, size, and font
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
     // Get the text of the clicked button
    QString str = ((QPushButton*)sender())->text();

    // Append the corresponding character to the formula string based on the clicked button
    if(str == "÷") formula += "/";
    else if (str == "×") formula += "*";
    else formula += str;

    display->setText(formula);
}

// Clear the display text, stack of numbers and operators and formula string
void Calculator::clearClicked() {
    display->setText("0");

    numbers.clear();
    operators.clear();

    formula = "";
}

// Remove the last character from the formula string and update display with the modified formula
void Calculator::backspaseClicked() {
    formula.chop(1);
    display->setText(formula);
}

void Calculator::equalClicked(){
    QString result = calculate();

    display->setText(result);

    numbers.clear();
    operators.clear();

    // Clear the result if it is "nan" or "0"
    // This is necessary to preven errors
    // like: 02 + 2
    if(result == "nan" || result == "0") { result = ""; }
    // We can use the result for the following solution
    formula = result;
}

// Create a new display widget with specified options
void Calculator::setupDisplay() {
    display = new Display(this);

    display->setMaximumSize (311, 65);

    QFont font("Helvetica [Cronyx]", 44, QFont::Cursive);
    display->setFont(font);
}

// Create digit buttons and operator buttons with their respective colors and slots
void Calculator::setupButtons() {
    for (int i = 0; i < NumDigitButtons; ++i) {
      digitButtons[i] = createButton(QString::number(i), digitColor, SLOT(DigitOrOperatorClicked()));
     }

    equalButton = createButton(tr("="), operatorColor, SLOT(equalClicked()));
    clearButton = createButton(tr("AC"), serviceColor, SLOT(clearClicked()));

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

QGridLayout* Calculator::setupLayout() {
    // Create new layout
    QGridLayout *tempLayout = new QGridLayout;
    tempLayout->setContentsMargins(0, 0, 0, 0);
    tempLayout->setSizeConstraint(QLayout::SetFixedSize);
    tempLayout->setSpacing(1);

    // Add the display widget to the layout
    tempLayout->addWidget(display, 0, 0, 1, 6);

    // Add digit buttons to the layout
    // by calculating the desired position
    for (int i = 1; i < NumDigitButtons; ++i) {
      int row = ((9 - i) / 3) + 2;
      int column = ((i - 1) % 3) + 1;
      tempLayout->addWidget(digitButtons[i], row, column);
     }

    // Add other buttons to the layout
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

// This function checks if the parentheses in the formula are balanced.
bool Calculator::checkParentheses() {
    int count = 0;  // Counter for open parentheses

    for (int i = 0; i < formula.size(); ++i) {
        const QChar& c = formula.at(i);
        if (c == '(') {
            count++;    // Increment count for each open parenthesis
        } else if (c == ')') {
        // If a closing parenthesis is encountered without a matching open parenthesis, return false
            if (count == 0) { return false; }

            count--;    // Decrement count for each closing parenthesis that matches an open parenthesis
        }
    }

    return count == 0;  // Return true if count is zero, indicating balanced parentheses
}

// Checks if a character is an arithmetic operation
bool Calculator::isOperation(QChar c) {return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';}

// This function assigns priority levels to arithmetic operations.
int Calculator::setPriority(char op) {
    if (op < 0) { return 4; } // Unary operations have the highest priority
    else {
       // Increase priority
       if (op == '+' || op == '-') return 1;
       else if (op == '*' || op == '/') return 2;
       else if (op == '^') return 3;
       // -1 if invalid operation
       else return -1;
    }
}

// This function performs the arithmetic action based on the given operation.
void Calculator::action(char op) {

    if (numbers.size() == 0) {
        return; // If there are not enough operands, return without performing any action
    } else if (op < 0) {

        double unaryNum = numbers.pop();
        if (-op == '-') {
            numbers.push(-unaryNum); // For unary minus, negate the operand and push back to the stack
        } else {
            numbers.push(unaryNum); // For other unary operations, push back the operand as is
        }

    } else {
        if (numbers.size() < 2) {
            return; // If there are not enough operands, return without performing any action
        }
        double right = numbers.pop();
        double left = numbers.pop();
        if (op == '/' && right == 0) {
            numbers.push(std::numeric_limits<double>::quiet_NaN()); // Division by zero results in NaN
        } else {
            switch (op) { // If all ok, perform the action
                case '+': numbers.push(left + right); break;
                case '-': numbers.push(left - right); break;
                case '*': numbers.push(left * right); break;
                case '/': numbers.push(left / right); break;
                case '^': numbers.push(std::pow(left, right)); break;
            }
        }
    }
}

// This function evaluates the formula and returns the calculated result as a string.
QString Calculator::calculate() {

    // Display error message if parentheses are not balanced and return 0
    if (!checkParentheses()){
      display->setText("˙◠˙");
      errorMessage("Parentheses mismatch!");
      return "0";
    }

    bool unary = true;  // Flag to track if the current operation is unary

    // Clear the stack of numbers and operations
    numbers.clear();
    operators.clear();

    // Formula pass cycle
for (int i = 0; i < formula.size(); i++) {
    QChar currentChar = formula[i];

    if (currentChar == '(') {
        operators.push('(');    // Push open parenthesis to the operator stack
        unary = true;
    } else if (currentChar == ')') {

        while (operators.top() != '(') {
            action(operators.pop());    // Perform actions on operators until an open parenthesis is encountered
        }

        operators.pop();
        unary = false;

    } else if (isOperation(currentChar)) { // Process the operation
        char operation = currentChar.toLatin1();

        if (unary) { operation = -operation; }  // Negate the operation if it is unary

        while (!operators.empty() && setPriority(operators.top()) >= setPriority(operation)) {
            action(operators.pop());    // Perform actions on operators with higher or equal priority
        }
        operators.push(operation);  // Push the current operation to the stack
        unary = true;

    } else if (currentChar.isDigit() || currentChar == '.') {   // Process the digits
        QString number; // From digits create the number

        while (i < formula.size() && (formula[i].isDigit() || formula[i] == '.')) {
            number += formula[i];   // Accumulate digits and decimal point to form a number
            i++;
        }
        i--;
        numbers.push(number.toDouble());  // Convert the accumulated number to double and push to the number stack
        unary = false;
    }
}

while (!operators.empty()) { action(operators.pop()); } // Perform remaining actions on the remaining operators


    double result = numbers.pop(); // Pop the final result from the number stack

    // Return "nan" if the result is NaN
    // and convert the result to a string and return if not NaN
    if (std::isnan(result)) { return "nan"; }
    else { return QString::number(result); }
}

// This function displays an error message dialog with the given message string.
void Calculator::errorMessage(const QString& message) {
    QDialog dialog;
    dialog.setWindowTitle("Error");

    QFont font("Helvetica [Cronyx]", 24);

    QLabel label(message);
    label.setFont(font);

    QVBoxLayout layout(&dialog);
    layout.addWidget(&label);

    dialog.exec();
}

// This function handles the key press event.
// Key_Right scroll display to right
// Key_Left scroll display to left
// Key_Backspace delete last character in formula
// Key_Return the same with pushing "="
// Add others allowed to the end of formula
//  "0 1 2 3 4 5 6 7 8 9 + - * / ( ) . ^" //
void Calculator::keyPressEvent(QKeyEvent* event) {
    switch (event->key()) {
        case Qt::Key_Left:
            scrollTextLeft();
            break;
        case Qt::Key_Right:
            scrollTextRight();
            break;
        case Qt::Key_Backspace:
            backspaseClicked();
            break;
        case Qt::Key_Return:
            equalClicked();
            break;
        default: // Check for allowed character and push it to formula and display

        QString inputText = event->text();

        if(InputCharacterISValid(inputText)){
            addCharacterToSolution(inputText.at(0));
        }

            break;
    }
    QMainWindow::keyPressEvent(event);
}

bool Calculator::InputCharacterISValid(QString inputText) {
    if (!inputText.isEmpty()) {
        QChar inputChar = inputText.at(0);
        if (isInputCharacterAllowed(inputChar)) { return 1; }
    }
    return 0;
}

bool Calculator::isInputCharacterAllowed(QChar inputChar) {
    QString allowedCharacters = "0123456789+-*/().^";
    return allowedCharacters.contains(inputChar);
}

void Calculator::addCharacterToSolution(QChar inputSimbol){
    formula += inputSimbol;
    display->setText(formula);
}

// This function scrolls the text display to the left.
void Calculator::scrollTextLeft() {
    QTextCursor cursor = display->textCursor();
    cursor.movePosition(QTextCursor::Left, QTextCursor::MoveAnchor);
    display->setTextCursor(cursor);
}

// This function scrolls the text display to the right.
void Calculator::scrollTextRight() {
    QTextCursor cursor = display->textCursor();
    cursor.movePosition(QTextCursor::Right, QTextCursor::MoveAnchor);
    display->setTextCursor(cursor);
}
