#include "minisplitter.h"

class MiniSplitterHandle : public QSplitterHandle {
public:
    MiniSplitterHandle(Qt::Orientation orientation, QSplitter *parent)
        : QSplitterHandle(orientation, parent) {
        setMask(QRegion(contentsRect()));
        setAttribute(Qt::WA_MouseNoMask, true);
    }

protected:
    void resizeEvent(QResizeEvent *event) {
        if (orientation() == Qt::Horizontal)
            setContentsMargins(2, 0, 2, 0);
        else
            setContentsMargins(0, 2, 0, 2);
        setMask(QRegion(contentsRect()));
        QSplitterHandle::resizeEvent(event);
    }

    void paintEvent(QPaintEvent *event) {
        if (splitter()->lineWidth() > 0) {
            QPainter painter(this);
            QPen pen(palette().color(QPalette::Mid));
            // cosmetic pen, always 1px
            pen.setWidth(0);
            painter.setPen(pen);
            painter.drawLine(event->rect().topLeft(), event->rect().bottomLeft());
        }
    }
};

MiniSplitter::MiniSplitter(Qt::Orientation orientation, QWidget *parent)
    : QSplitter(orientation, parent) {
    setHandleWidth(1);
    setChildrenCollapsible(false);
    setLineWidth(0); // default to invisible
}

QSplitterHandle *MiniSplitter::createHandle() {
    return new MiniSplitterHandle(orientation(), this);
}
