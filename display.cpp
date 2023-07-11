#include "display.h"

Display::Display(QWidget* parent) : QTextEdit(parent) {
    setReadOnly(true);
    setAlignment(Qt::AlignRight | Qt::AlignBottom);
    setReadOnly(true);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setLineWrapMode(QTextEdit::NoWrap);

    setText("0");
}

void Display::setText(const QString& text) {
    QTextEdit::setText(text);
    setAlignment(Qt::AlignRight | Qt::AlignBottom);
    QTextCursor cursor = textCursor();
    cursor.movePosition(QTextCursor::End);
    setTextCursor(cursor);
}
