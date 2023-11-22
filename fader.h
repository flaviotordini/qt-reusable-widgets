#ifndef FADER_H
#define FADER_H

#include <QtWidgets>

class Fader : public QWidget {
    Q_OBJECT

public:
    Fader(QWidget *newWidget, QPixmap oldWidgetPixmap);
    static void crossfade(QWidget *w);

protected:
    void paintEvent(QPaintEvent *event);

private:
    QTimeLine *timeLine;
    QPixmap frozenView;
};

#endif
