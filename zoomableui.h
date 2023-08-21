#ifndef ZOOMABLEUI_H
#define ZOOMABLEUI_H

#include <QtWidgets>

class ZoomableUI : public QObject {
    Q_OBJECT

public:
    ZoomableUI(QMainWindow &window);
    QList<QAction *> getActions() { return actions; }

private:
    QList<QAction *> actions;
};

#endif // ZOOMABLEUI_H
