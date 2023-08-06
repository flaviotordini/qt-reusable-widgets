#ifndef VIEW_H
#define VIEW_H

#include <QtWidgets>

class View : public QWidget {
    Q_OBJECT

public:
    View(QWidget *parent = 0) : QWidget(parent) {}
    virtual QString getTitle() { return QString(); }
    virtual QString getDescription() { return QString(); }
    virtual void appear() {}
    virtual void disappear() {}

signals:
    void willAppear();
    void didAppear();
    void willDisappear();
    void didDisappear();
};

#endif // VIEW_H
