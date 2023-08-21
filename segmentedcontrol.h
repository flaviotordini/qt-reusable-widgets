#ifndef SEGMENTEDCONTROL_H
#define SEGMENTEDCONTROL_H

#include <QtWidgets>

class SegmentedControl : public QWidget {
    Q_OBJECT

public:
    SegmentedControl(QWidget *parent = nullptr);
    QAction *addAction(QAction *action);
    bool setCheckedAction(int index);
    bool setCheckedAction(QAction *action);
    QSize minimumSizeHint(void) const;

signals:
    void checkedActionChanged(QAction &action);

protected:
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void leaveEvent(QEvent *event);
    bool event(QEvent *event);

private slots:
    void setupColors();

private:
    void paintButton(QPainter *painter, const QRect &rect, const QAction *action);
    QAction *findHoveredAction(const QPoint &pos) const;
    int calculateButtonWidth() const;

    QVector<QAction *> actionList;
    QAction *checkedAction;
    QAction *hoveredAction;
    QAction *pressedAction;

    QColor backgroundColor;
    QColor selectedColor;
    QColor hoveredColor;
};

#endif /* !SEGMENTEDCONTROL_H */
