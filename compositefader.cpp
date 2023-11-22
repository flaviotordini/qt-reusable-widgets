#include "compositefader.h"

void CompositeFader::go(QWidget *newWidget, QPixmap oldWidgetPixmap) {
    static CompositeFader i;
    i.start(newWidget, oldWidgetPixmap);
}

CompositeFader::CompositeFader() : QWidget(nullptr) {
    setWindowFlags(Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint | Qt::CustomizeWindowHint |
                   Qt::WindowStaysOnTopHint | Qt::WindowTransparentForInput);
    setAttribute(Qt::WA_StaticContents);

    timeLine = new QTimeLine(250, this);
    timeLine->setEasingCurve(QEasingCurve::Linear);
    timeLine->setFrameRange(14, 1);

    connect(timeLine, &QTimeLine::frameChanged, this, [this](int frame) {
        const qreal opacity = frame / 15.;
        setWindowOpacity(opacity);
    });
    connect(timeLine, &QTimeLine::finished, this, &QWidget::close);
}

void CompositeFader::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.drawPixmap(0, 0, frozenView);
}

void CompositeFader::start(QWidget *newWidget, QPixmap oldWidgetPixmap) {
    frozenView = oldWidgetPixmap;
    update();
    move(newWidget->mapToGlobal(QPoint(0, 0)));
    resize(newWidget->size());
    show();
    timeLine->start();
}
