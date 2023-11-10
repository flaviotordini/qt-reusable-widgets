#ifndef PAINTERUTILS_H
#define PAINTERUTILS_H

#include <QtWidgets>

class PainterUtils {

public:
    static void centeredMessage(QString message, QWidget *widget);
    static void centeredPixmap(QPixmap pixmap, QWidget *widget);
    static QPixmap roundCorners(QPixmap pixmap, int radius = 5);

private:
    PainterUtils();
};

#endif // PAINTERUTILS_H
