#ifndef PAINTERUTILS_H
#define PAINTERUTILS_H

#include <QtWidgets>

class PainterUtils {

public:
    static void centeredMessage(QString message, QWidget *widget);
    static void centeredPixmap(QPixmap pixmap, QWidget *widget);
    static QPixmap roundCorners(QPixmap pixmap, int radius = 5);
    static QPixmap scaleAndCrop(QPixmap pixmap, QSize size, qreal pixelRatio);
    static QPixmap collage(QList<QPixmap> fourOrLessPics, int width, int height, qreal pixelRatio);

private:
    PainterUtils();
};

#endif // PAINTERUTILS_H
