#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QLineEdit>
#include <QBoxLayout>
#include <QShortcut>

#include "keyprocessor.h"

class Window : public QWidget
{
    Q_OBJECT

public:
    Window();
    ~Window();

public slots:
    void onEscape();
    void onTextChanged();

private:
    // LineEdit control
    QLineEdit *lineEdit;

    // Shortcut to handle Enter key
    QShortcut *shortcut;

    // Convert to Vietnamese
    KeyProcessor *keyProcessor;
};

#endif