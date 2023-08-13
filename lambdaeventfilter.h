#ifndef LAMBDAEVENTFILTER_H
#define LAMBDAEVENTFILTER_H

#include <QtCore/QObject>

/***
 * QObject event filtering using lambdas
 */
template <class Function> class LambdaEventFilter : public QObject {
public:
    explicit LambdaEventFilter(QObject *obj, Function func) : QObject(obj), func(func) {
        obj->installEventFilter(this);
    }

protected:
    bool eventFilter(QObject *obj, QEvent *e) override { return func(obj, e); }

private:
    const Function func;
};
#endif // LAMBDAEVENTFILTER_H
