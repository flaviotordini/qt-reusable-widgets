#ifndef STATUSLABEL_H
#define STATUSLABEL_H

#include <QtWidgets/QLabel>

class StatusLabel : public QLabel {
    Q_OBJECT

public:
    StatusLabel(QMainWindow *window);

private:
    QTimer *timer;
};

#endif // STATUSLABEL_H
