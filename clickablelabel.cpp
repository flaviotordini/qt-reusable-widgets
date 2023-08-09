#include "clickablelabel.h"

ClickableLabel::ClickableLabel(QWidget *parent) : QLabel(parent) {
    setCursor(Qt::PointingHandCursor);
    setFocusPolicy(Qt::TabFocus);
}

ClickableLabel::ClickableLabel(const QString &text, QWidget *parent) : QLabel(text, parent) {
    setCursor(Qt::PointingHandCursor);
    setFocusPolicy(Qt::TabFocus);
}

void ClickableLabel::mouseReleaseEvent(QMouseEvent *e) {
    if (e->button() == Qt::LeftButton && rect().contains(e->pos())) emit clicked();
    QLabel::mouseReleaseEvent(e);
}

void ClickableLabel::leaveEvent(QEvent *e) {
    setForegroundRole(QPalette::WindowText);
    emit hovered(false);
    QLabel::leaveEvent(e);
}

void ClickableLabel::focusInEvent(QFocusEvent *e) {
    setForegroundRole(QPalette::Highlight);
    QLabel::focusInEvent(e);
}

void ClickableLabel::focusOutEvent(QFocusEvent *e) {
    setForegroundRole(QPalette::WindowText);
    QLabel::focusOutEvent(e);
}

void ClickableLabel::enterEvent(CompatibleEnterEvent *e) {
    setForegroundRole(QPalette::Highlight);
    emit hovered(true);
    QLabel::enterEvent(e);
}
