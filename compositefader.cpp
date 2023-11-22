#include "compositefader.h"

void CompositeFader::go(QWidget *widget, QPixmap pixmap) {
    static CompositeFader i;
    i.start(widget, pixmap);
}

CompositeFader::CompositeFader() : QWidget(nullptr) {
    setWindowFlags(Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint | Qt::CustomizeWindowHint |
                   Qt::WindowStaysOnTopHint | Qt::WindowTransparentForInput);
    setAttribute(Qt::WA_StaticContents);
    setAttribute(Qt::WA_Disabled);

    timeLine = new QTimeLine(250, this);
    timeLine->setFrameRange(14, 1);

    connect(timeLine, &QTimeLine::frameChanged, this, [this](int frame) {
        const qreal opacity = frame / 15.;
        setWindowOpacity(opacity);
    });
    connect(timeLine, &QTimeLine::finished, this, &QWidget::close);
}

void CompositeFader::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.drawPixmap(0, 0, pixmap);
}

void CompositeFader::start(QWidget *widget, QPixmap pixmap) {
    hide();
    this->pixmap = pixmap;
    update();
    move(widget->mapToGlobal(QPoint(0, 0)));
    resize(widget->size());
    show();
    timeLine->start();
}
