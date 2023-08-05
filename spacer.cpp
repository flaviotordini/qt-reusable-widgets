#include "spacer.h"

Spacer::Spacer(QWidget *parent, int minWidth) : QWidget(parent), minWidth(minWidth) {
    setAttribute(Qt::WA_TransparentForMouseEvents);
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    setEnabled(false);
}

QSize Spacer::sizeHint() const {
    return QSize(minWidth, 1);
}
