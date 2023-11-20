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
    p.setDevicePixelRatio(pixmap.devicePixelRatio());
    p.fill(Qt::transparent);
    QPainter painter(&p);
    painter.setRenderHint(QPainter::Antialiasing);
    QBrush brush(pixmap);
    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);
    QRect rect(0, 0, pixmap.width() / pixmap.devicePixelRatio(),
               pixmap.height() / pixmap.devicePixelRatio());
    painter.drawRoundedRect(rect, radius, radius);
    return p;
}

QPixmap PainterUtils::scaleAndCrop(QPixmap pixmap, QSize size, qreal pixelRatio) {
    if (pixmap.size().width() < size.width() || pixmap.size().height() < size.height())
        return pixmap;

    const int pixelWidth = size.width() * pixelRatio;
    const int pixelHeight = size.height() * pixelRatio;

    int wDiff = pixmap.width() - pixelWidth;
    int hDiff = pixmap.height() - pixelHeight;
    if (wDiff > 0 || hDiff > 0) {
        if (wDiff > hDiff) {
            pixmap = pixmap.scaledToHeight(pixelHeight, Qt::SmoothTransformation);
        } else {
            pixmap = pixmap.scaledToWidth(pixelWidth, Qt::SmoothTransformation);
        }
        wDiff = pixmap.width() - pixelWidth;
        hDiff = pixmap.height() - pixelHeight;
        int xOffset = 0;
        int yOffset = 0;
        if (hDiff > 0) yOffset = hDiff / 4;
        if (wDiff > 0) xOffset = wDiff / 2;
        pixmap = pixmap.copy(xOffset, yOffset, pixelWidth, pixelHeight);
    }
    pixmap.setDevicePixelRatio(pixelRatio);
    return pixmap;
}

QPixmap PainterUtils::collage(QList<QPixmap> fourPics, int width, int height, qreal pixelRatio) {
    QPixmap pixmap = QPixmap(width * pixelRatio, height * pixelRatio);
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing);

    int cols = fourPics.size() >= 4 ? 2 : 1;
    const int w = pixmap.width() / cols;
    int rows = cols;
    const int h = pixmap.height() / rows;

    int i = 0;
    int row = -1;
    for (auto p : fourPics) {
        if (p.isNull()) continue;

        int col = i % cols;
        if (col == 0) row++;
        QRect rect(w * col, h * row, w, h);
        p = scaleAndCrop(p, rect.size(), p.devicePixelRatio());
        painter.drawPixmap(rect.topLeft(), p);

        i++;
    }
    pixmap.setDevicePixelRatio(pixelRatio);
    return pixmap;
}
