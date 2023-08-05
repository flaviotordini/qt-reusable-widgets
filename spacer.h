#ifndef SPACER_H
#define SPACER_H

#include <QtWidgets>

class Spacer : public QWidget {
public:
    Spacer(QWidget *parent = nullptr, int minWidth = 100);

protected:
    QSize sizeHint() const;

private:
    int minWidth;
};

#endif // SPACER_H
