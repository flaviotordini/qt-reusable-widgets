#include "messagebar.h"
#include "iconutils.h"

MessageBar::MessageBar(QWidget *parent) : QWidget(parent) {
    setStyleSheet("border-radius: 5px;"
                  "background: palette(highlight);"
                  "color: palette(highlighted-text);");
    setCursor(Qt::PointingHandCursor);

    const int padding = 10;

    auto layout = new QHBoxLayout(this);
    layout->setContentsMargins(padding, 0, padding, 0);
    layout->setSpacing(padding);

    label = new QLabel();
    label->setContentsMargins(0, padding, 0, padding);
    label->setAlignment(Qt::AlignCenter);
    layout->addWidget(label);

    auto closeButton = new QToolButton();
    closeButton->setStyleSheet("border:0");
    closeButton->setIconSize({24, 24});
    closeButton->setAutoRaise(true);
    closeButton->setIcon(IconUtils::icon("close"));
    closeButton->setCursor(Qt::ArrowCursor);
    connect(closeButton, &QToolButton::clicked, this, [this] {
        emit closed();
        hide();
    });
    layout->addWidget(closeButton);
}

void MessageBar::setMessage(const QString &message) {
    label->setText(message);
}

void MessageBar::paintEvent(QPaintEvent *e) {
    Q_UNUSED(e);
    QStyleOption o;
    o.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &o, &p, this);
}

void MessageBar::mouseReleaseEvent(QMouseEvent *e) {
    emit clicked();
}
