#ifndef BREADCRUMB_H
#define BREADCRUMB_H

#include <QtWidgets>

class Breadcrumb : public QToolBar {
    Q_OBJECT

public:
    Breadcrumb(QWidget *parent);
    void addItem(QString title);
    void clear();
    void goBack();

signals:
    void goneBack();

private:
    QAction *backAction;
};

#endif // BREADCRUMB_H
