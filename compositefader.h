#ifndef COMPOSITEFADER_H
#define COMPOSITEFADER_H

#include <QtWidgets>

class CompositeFader : public QWidget {
    Q_OBJECT

public:
    static void go(QWidget *newWidget, QPixmap oldWidgetPixmap);
    CompositeFader();

protected:
    void paintEvent(QPaintEvent *event);

private:
    void start(QWidget *newWidget, QPixmap oldWidgetPixmap);

    QTimeLine *timeLine;
    QPixmap frozenView;
};

#endif // COMPOSITEFADER_H
