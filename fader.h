#ifndef FADER_H
#define FADER_H

#include <QtWidgets>

class Fader : public QWidget {
    Q_OBJECT

public:
    Fader(QWidget *widget, QPixmap pixmap);
    static void crossfade(QWidget *w);

protected:
    void paintEvent(QPaintEvent *event);

private:
    QTimeLine *timeLine;
    const QPixmap pixmap;
};

#endif
