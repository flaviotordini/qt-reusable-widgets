#ifndef VIEWS_H
#define VIEWS_H

#include "view.h"

#include <QtWidgets>

class View;

class Views : public QStackedWidget {
    Q_OBJECT

public:
    Views(QWidget *parent = nullptr);
    void addView(View *view);
    void showView(View *view);

    QStack<View *> getHistory() const { return history; }
    bool goBack();
    bool canGoBack();

    void setHomeView(View *view);
    void goHome();

signals:
    void currentViewChanged(View *view);

private:
    QStack<View *> history;
    View *home = nullptr;
};

#endif // VIEWS_H
