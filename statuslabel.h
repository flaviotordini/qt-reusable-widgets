#ifndef STATUSLABEL_H
#define STATUSLABEL_H

#include <QtCore/QTimer>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>

class StatusLabel : public QLabel {
    Q_OBJECT

public:
    StatusLabel(QMainWindow *window);

private:
    QTimer *timer;
};

#endif // STATUSLABEL_H
