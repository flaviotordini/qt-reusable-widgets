#include "actionbutton.h"

ActionButton::ActionButton(QWidget *parent) : QPushButton(parent), action(0) {}

void ActionButton::setAction(QAction *newAction) {
    if (action && action != newAction) {
        disconnect(action, &QAction::changed, this, &ActionButton::updateButtonStatusFromAction);
        disconnect(this, &QAbstractButton::clicked, action, &QAction::trigger);
    }
    action = newAction;
    if (action) {
        updateButtonStatusFromAction();
        connect(action, &QAction::changed, this, &ActionButton::updateButtonStatusFromAction);
        connect(this, &QAbstractButton::clicked, action, &QAction::trigger);
    }
}

void ActionButton::setToolButtonStyle(Qt::ToolButtonStyle value) {
    style = value;
    updateButtonStatusFromAction();
}

void ActionButton::updateButtonStatusFromAction() {
    if (!action) return;
    if (style == Qt::ToolButtonTextBesideIcon || style == Qt::ToolButtonTextOnly)
        setText(action->text());
    if (style == Qt::ToolButtonTextBesideIcon || style == Qt::ToolButtonIconOnly)
        setIcon(action->icon());
    setStatusTip(action->statusTip());
    setToolTip(action->toolTip());
    setEnabled(action->isEnabled());
    setCheckable(action->isCheckable());
    setChecked(action->isChecked());
}
