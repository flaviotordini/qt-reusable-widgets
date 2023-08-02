#include "segmentedcontrol.h"

SegmentedControl::SegmentedControl(QWidget *parent) : QWidget(parent) {
    setAttribute(Qt::WA_OpaquePaintEvent);

    setMouseTracking(true);

    hoveredAction = nullptr;
    checkedAction = nullptr;
    pressedAction = nullptr;

    setupColors();
    connect(qApp, &QGuiApplication::paletteChanged, this, [this] {
        setupColors();
        update();
    });
}

QAction *SegmentedControl::addAction(QAction *action) {
    QWidget::addAction(action);
    action->setCheckable(true);
    actionList.append(action);
    return action;
}

bool SegmentedControl::setCheckedAction(int index) {
    if (index < 0) {
        checkedAction = nullptr;
        return true;
    }
    QAction *newCheckedAction = actionList.at(index);
    return setCheckedAction(newCheckedAction);
}

bool SegmentedControl::setCheckedAction(QAction *action) {
    if (checkedAction == action) {
        return false;
    }
    if (checkedAction) checkedAction->setChecked(false);
    checkedAction = action;
    checkedAction->setChecked(true);
    update();
    return true;
}

QSize SegmentedControl::minimumSizeHint() const {
    int itemsWidth = calculateButtonWidth() * actionList.size() * 1.2;
    return (QSize(itemsWidth, QFontMetrics(font()).height() * 3));
}

void SegmentedControl::paintEvent(QPaintEvent * /*event*/) {
    const int height = rect().height();
    const int width = rect().width();

    QPainter p(this);
    p.fillRect(rect(), backgroundColor);

    // Calculate Buttons Size & Location
    const int buttonWidth = width / actionList.size();

    // Draw Buttons
    QRect rect(0, 0, buttonWidth, height);
    const int actionCount = actionList.size();
    for (int i = 0; i < actionCount; i++) {
        QAction *action = actionList.at(i);
        if (i + 1 == actionCount) {
            // last button
            rect.setWidth(width - buttonWidth * (actionCount - 1));
            paintButton(&p, rect, action);
        } else {
            paintButton(&p, rect, action);
            rect.moveLeft(rect.x() + rect.width());
        }
    }
}

void SegmentedControl::mouseMoveEvent(QMouseEvent *event) {
    QAction *action = findHoveredAction(event->pos());

    if (!action && hoveredAction) {
        hoveredAction = nullptr;
        update();
    } else if (action && action != hoveredAction) {
        hoveredAction = action;
        action->hover();
        update();

        setStatusTip(action->statusTip());
    }
}

void SegmentedControl::mousePressEvent(QMouseEvent *event) {
    QWidget::mousePressEvent(event);
    if (hoveredAction) {
        pressedAction = hoveredAction;
        update();
    }
}

void SegmentedControl::mouseReleaseEvent(QMouseEvent *event) {
    QWidget::mouseReleaseEvent(event);
    pressedAction = nullptr;
    if (hoveredAction) {
        bool changed = setCheckedAction(hoveredAction);
        if (changed) hoveredAction->trigger();
    }
}

void SegmentedControl::leaveEvent(QEvent *event) {
    QWidget::leaveEvent(event);
    setStatusTip(QString());
    hoveredAction = nullptr;
    pressedAction = nullptr;
    update();
}

bool SegmentedControl::event(QEvent *event) {
    if (event->type() == QEvent::ApplicationPaletteChange) {
        setupColors();
        update();
    }
    return QWidget::event(event);
}

void SegmentedControl::setupColors() {
#ifdef Q_OS_WIN
    backgroundColor = qApp->palette().color(QPalette::Base);
#else
    backgroundColor = qApp->palette().color(QPalette::Window);
#endif
    int factor = backgroundColor.lightness() > 128 ? 115 : 80;
    selectedColor = backgroundColor.darker(factor);
    hoveredColor = selectedColor;
    pressedColor = hoveredColor.darker(factor);
}

QAction *SegmentedControl::findHoveredAction(const QPoint &pos) const {
    const int w = width();
    if (pos.y() <= 0 || pos.x() >= w || pos.y() >= height()) return nullptr;

    int buttonWidth = w / actionList.size();

    int buttonIndex = pos.x() / buttonWidth;

    if (buttonIndex >= actionList.size()) return nullptr;
    return actionList[buttonIndex];
}

int SegmentedControl::calculateButtonWidth() const {
    QFontMetrics fontMetrics(font());
    int tmpItemWidth, itemWidth = 0;
    for (QAction *action : actionList) {
        tmpItemWidth = fontMetrics.boundingRect(action->text()).width();
        if (itemWidth < tmpItemWidth) itemWidth = tmpItemWidth;
    }
    return itemWidth;
}

void SegmentedControl::paintButton(QPainter *painter, const QRect &rect, const QAction *action) {
    QColor c;
    if (action == checkedAction) {
        c = selectedColor;
    } else if (action == pressedAction) {
        c = pressedColor;
    } else if (action == hoveredAction) {
        c = hoveredColor;
    }

    painter->save();

    if (c.isValid()) {
        const int margin = rect.height() * .2;
        QRect bgRect = rect.marginsRemoved(QMargins(margin, margin, margin, margin));
        bgRect.moveCenter(rect.center());
        painter->setBrush(c);
        painter->setPen(Qt::NoPen);
        painter->setRenderHint(QPainter::Antialiasing);
        painter->drawRoundedRect(bgRect, margin, margin);
    }

    painter->setPen(qApp->palette().windowText().color());
    painter->drawText(rect, Qt::AlignCenter, action->text());
    painter->restore();
}
