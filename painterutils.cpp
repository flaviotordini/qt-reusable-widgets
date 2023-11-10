#include "painterutils.h"
#include "fontutils.h"

PainterUtils::PainterUtils() { }

void PainterUtils::centeredMessage(QString message, QWidget* widget) {
    QPainter painter(widget);
    painter.setPen(widget->palette().text().color());
    painter.setOpacity(.5);
    painter.setFont(FontUtils::big());
    QSize textSize(QFontMetrics(painter.font()).size(Qt::TextSingleLine, message));
    QPoint topLeft(
                (widget->width()-textSize.width())/2,
                ((widget->height()-textSize.height())/2)
                );
    QRect rect(topLeft, textSize);
    painter.drawText(rect, Qt::AlignCenter, message);
}

void PainterUtils::centeredPixmap(QPixmap pixmap, QWidget *widget) {
    QRect pixmapRect = pixmap.rect();
    pixmapRect.moveCenter(widget->rect().center());
    QPainter painter(widget);
    painter.drawPixmap(pixmapRect, pixmap);
}

QPixmap PainterUtils::roundCorners(QPixmap pixmap, int radius) {
    QPixmap p(pixmap.size());
    p.fill(Qt::transparent);
    QPainter painter(&p);
    painter.setRenderHint(QPainter::Antialiasing);
    QBrush brush(pixmap);
    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);
    painter.drawRoundedRect(pixmap.rect(), radius, radius);
    return p;
}
