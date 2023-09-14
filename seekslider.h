#ifndef SEEKSLIDER_H
#define SEEKSLIDER_H

#include <QSlider>

class SeekSlider : public QSlider {
    Q_OBJECT

public:
    SeekSlider(QWidget *parent = nullptr);
};

#endif // SEEKSLIDER_H
