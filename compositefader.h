#ifndef COMPOSITEFADER_H
#define COMPOSITEFADER_H

#include <QtWidgets>

class CompositeFader : public QWidget {
    Q_OBJECT

public:
    static void go(QWidget *widget, QPixmap pixmap);
    CompositeFader();

protected:
    void paintEvent(QPaintEvent *event);

private:
    void start(QWidget *newWidget, QPixmap pixmap);

    QTimeLine *timeLine;
    QPixmap pixmap;
};

#endif // COMPOSITEFADER_H
