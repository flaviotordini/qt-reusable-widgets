#ifndef ACTIONBUTTON_H
#define ACTIONBUTTON_H

#include <QAction>
#include <QPushButton>

class ActionButton : public QPushButton {
    Q_OBJECT

public:
    explicit ActionButton(QWidget *parent = 0);
    void setAction(QAction *newAction);
    void setToolButtonStyle(Qt::ToolButtonStyle value);

private:
    void updateButtonStatusFromAction();

    QAction *action;
    Qt::ToolButtonStyle style = Qt::ToolButtonIconOnly;
};

#endif // ACTIONBUTTON_H
