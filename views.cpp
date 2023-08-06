#include "views.h"

Views::Views(QWidget *parent) : QStackedWidget(parent) {}

void Views::addView(View *view) {
    view->setEnabled(false);
    addWidget(view);
}

void Views::setHomeView(View *view) {
    home = view;
}

void Views::goHome() {
    if (home) showView(home);
}

void Views::showView(View *view) {
    if (!history.isEmpty() && view == history.top()) {
        qDebug() << "Attempting to show same view" << view;
        return;
    }

    // call hide method on the current view
    View *oldView = history.isEmpty() ? nullptr : history.top();
    if (oldView) {
        oldView->willDisappear();
        oldView->disappear();
        oldView->setEnabled(false);
        oldView->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    } else
        qDebug() << "Cannot cast old view";

    view->willAppear();
    view->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    view->setEnabled(true);
    setCurrentWidget(view);
    view->appear();
    view->didAppear();
    if (oldView) oldView->didDisappear();

    history.push(view);
}

bool Views::goBack() {
    if (canGoBack()) {
        history.pop();
        showView(history.pop());
        return true;
    }
    return false;
}

bool Views::canGoBack() {
    return history.size() > 1;
}
