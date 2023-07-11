#ifndef DISPLAY_H
#define DISPLAY_H

#include <QTextEdit>

class Display: public QTextEdit {
public:
    Display();
    Display(QWidget* parent = nullptr);

    void setText(const QString& text);
};

#endif // DISPLAY_H
