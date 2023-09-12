#include "breadcrumb.h"
#include "iconutils.h"

Breadcrumb::Breadcrumb(QWidget *parent) : QToolBar(parent) {
    backAction = new QAction(
            IconUtils::icon("go-previous"),
            tr("&Back"), this);
    backAction->setShortcuts({Qt::Key_Escape, Qt::ALT | Qt::Key_Left, Qt::Key_Backspace});
    backAction->setStatusTip(tr("Go back") + " (" +
                             backAction->shortcut().toString(QKeySequence::NativeText) + ")");
    connect(backAction, SIGNAL(triggered()), SIGNAL(goneBack()));
    addAction(backAction);

    setIconSize(QSize(24, 24));
}

void Breadcrumb::addItem(QString title) {
    QAction *action = addAction(title);

    // all actions enabled but the last one
    for (auto a : actions())
        a->setEnabled(a != action);
}

void Breadcrumb::goBack() {
    if (actions().size() > 1) {
        QAction *action = actions().last();
        if (action) {
            removeAction(action);
            delete action;
        }

        // all actions enabled but the last one
        for (auto a : actions())
            a->setEnabled(a != action);
    }
}

void Breadcrumb::clear() {
    // remove all but the backAction
    for (QAction *action : actions()) {
        if (action != backAction) {
            removeAction(action);
            delete action;
        }
    }
}
