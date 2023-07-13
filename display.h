#ifndef DISPLAY_H
#define DISPLAY_H

#include <QTextEdit>

// Custom class for display with overloaded setText function
class Display: public QTextEdit {
public:
    Display();
    Display(QWidget* parent = nullptr);

    void setText(const QString& text); // Overload function
};

#endif // DISPLAY_H
