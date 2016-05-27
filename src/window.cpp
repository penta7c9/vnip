#include <Qt>
#include <QtGui>
#include <QClipboard>

#include "window.h"

Window::Window()
{
    // Init lineEdit
    lineEdit = new QLineEdit;
    lineEdit->setFixedWidth(300);
    lineEdit->setFocus();
    connect(lineEdit, SIGNAL(textChanged(const QString &)), this, SLOT(onTextChanged()));
    connect(lineEdit, SIGNAL(returnPressed()), this, SLOT(onEscape()));

    // Add lineEdit to a layout
    QBoxLayout *layout = new QBoxLayout(QBoxLayout::LeftToRight);
    layout->addWidget(lineEdit);
    setLayout(layout);

    // Init shortcut processer
    shortcut = new QShortcut(QKeySequence(Qt::Key_Escape), this);
    shortcut->setContext(Qt::ApplicationShortcut);
    connect(shortcut, SIGNAL(activated()), this, SLOT(onEscape()));

    // Set title of the window
    setWindowTitle(tr("Vietnamese Input Panel"));

    // Init key processor
    keyProcessor = new KeyProcessor;
}

// Handler on ESC pressed
void Window::onEscape()
{
    QClipboard *clipboard = qApp->clipboard();
    clipboard->setText(lineEdit->text());

    qApp->quit();
}

// Handle text changed event of line edit
void Window::onTextChanged()
{
    QString res = keyProcessor->process(lineEdit->text());
    if (res != lineEdit->text()) lineEdit->setText(res);
}

// Tidy up
Window::~Window()
{
    delete lineEdit;
    delete layout();
    delete shortcut;
    delete keyProcessor;
}
