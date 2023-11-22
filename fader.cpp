#include "fader.h"

void Fader::crossfade(QWidget *w) {
    if (w->width() * w->height() > 500000) return;
    new Fader(w, w->grab());
}

Fader::Fader(QWidget *widget, QPixmap pixmap) : QWidget(widget), pixmap(pixmap) {
    setAttribute(Qt::WA_StaticContents);
    setAttribute(Qt::WA_DeleteOnClose);
    resize(widget->size());
    timeLine = new QTimeLine(250, this);
    timeLine->setEasingCurve(QEasingCurve::Linear);
    timeLine->setFrameRange(14, 1);
    connect(timeLine, &QTimeLine::frameChanged, this, [this](int) { update(); });
    connect(timeLine, &QTimeLine::finished, this, &QWidget::close);
    connect(timeLine, &QTimeLine::stateChanged, this, &QWidget::show);
    timeLine->start();
}

void Fader::paintEvent(QPaintEvent *) {
    const qreal opacity = timeLine->currentFrame() / 15.;
    // qDebug() << timeLine->currentFrame() << opacity;
    QPainter painter(this);
    painter.setOpacity(opacity);
    painter.drawPixmap(0, 0, pixmap);
}
