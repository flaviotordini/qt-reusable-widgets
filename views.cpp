#include "views.h"

Views::Views(QWidget *parent) : QStackedWidget(parent) {}

void Views::setHome(QWidget *widget) {
    home = widget;
}

void Views::goHome() {
    if (home) setCurrentWidget(home);
}

void Views::setCurrentWidget(QWidget *widget) {
    auto previous = history.isEmpty() ? nullptr : history.top();
    if (previous == widget) return;
    if (previous) previous->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    QStackedWidget::setCurrentWidget(widget);
    widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    history.push(widget);
}

bool Views::goBack() {
    if (canGoBack()) {
        history.pop();
        setCurrentWidget(history.pop());
        return true;
    }
    return false;
}

bool Views::canGoBack() {
    return history.size() > 1;
}
