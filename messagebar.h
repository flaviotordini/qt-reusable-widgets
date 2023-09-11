#ifndef MESSAGEBAR_H
#define MESSAGEBAR_H

#include <QLabel>
#include <QWidget>

class MessageBar : public QWidget {
    Q_OBJECT

public:
    MessageBar(QWidget *parent = 0);
    void setMessage(const QString &message);

signals:
    void clicked();
    void closed();

protected:
    void paintEvent(QPaintEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

private:
    QLabel *label;
};

#endif // MESSAGEBAR_H
