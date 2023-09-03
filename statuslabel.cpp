#include "statuslabel.h"
#include "lambdaeventfilter.h"

#include <QtGui/QResizeEvent>
#include <QtGui/QStatusTipEvent>

StatusLabel::StatusLabel(QWidget *window) : QLabel(window) {
    setTextFormat(Qt::PlainText);
    setBackgroundRole(QPalette::Base);
    setForegroundRole(QPalette::Text);
    setAutoFillBackground(true);
    setWordWrap(false);
    setAlignment(Qt::AlignCenter);
    hide();

    timer = new QTimer(this);
    timer->setInterval(5000);
    timer->setSingleShot(true);
    connect(timer, &QTimer::timeout, this, [this] {
        hide();
        clear();
    });

    new LambdaEventFilter(window, [this, window](auto o, auto e) {
        bool filtered = false;

        if (e->type() == QEvent::StatusTip) {
            auto ste = static_cast<QStatusTipEvent *>(e);
            auto tip = ste->tip();
            setText(tip);
            if (tip.isEmpty()) {
                hide();
            } else {
                QSize size = sizeHint();
                int margin = 15;
                size = size.grownBy({margin, margin, margin, margin});
                /*
                // round width to avoid flicker with fast changing messages (e.g. volume
                // changes)
                int w = width() + 10;
                const int multiple = 15;
                w = w + multiple / 2;
                w -= w % multiple;
                size.setWidth(w);*/
                resize(size);

                timer->start();

                if (isHidden() && window->isVisible()) {
                    move(0, window->height() - height());
                    show();
                }
            }

            // TODO timer
            // QTimer::singleShot(10000, this, &QWidget::hide);
            filtered = true;
        } else if (e->type() == QEvent::Resize) {
            auto re = static_cast<QResizeEvent *>(e);
            this->move(0, re->size().height() - height());
        }
        return filtered;
    });
}
