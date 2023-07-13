// Realise custom class for display with overloaded setText function
#include "display.h"

// Custom options of display
Display::Display(QWidget* parent) : QTextEdit(parent) {
    setAlignment(Qt::AlignRight | Qt::AlignBottom);
    setReadOnly(true);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setLineWrapMode(QTextEdit::NoWrap);
    setStyleSheet("QTextEdit { background-color: rgb(42, 40, 49);"
                              "border: none;"
                              "padding-top: 10px; }");

    setText("0");
}

// Overloaded function
void Display::setText(const QString& text) {
    QTextEdit::setText(text);
    setAlignment(Qt::AlignRight | Qt::AlignBottom);

    QTextCursor cursor = textCursor();
    cursor.movePosition(QTextCursor::End);

    setTextCursor(cursor);
}
