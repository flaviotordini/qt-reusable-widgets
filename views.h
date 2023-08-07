#ifndef VIEWS_H
#define VIEWS_H

#include <QtWidgets>

class View;

class Views : public QStackedWidget {
    Q_OBJECT

public:
    Views(QWidget *parent = nullptr);

    void setCurrentWidget(QWidget *widget);

    QStack<QWidget *> getHistory() const { return history; }
    Q_SLOT bool goBack();
    bool canGoBack();

    void setHome(QWidget *widget);
    void goHome();

private:
    QStack<QWidget *> history;
    QWidget *home = nullptr;
};

#endif // VIEWS_H
