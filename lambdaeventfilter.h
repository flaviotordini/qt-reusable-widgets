#ifndef LAMBDAEVENTFILTER_H
#define LAMBDAEVENTFILTER_H

#include <QtCore/QObject>

/***
 * This class enables the use of lambdas with QObject::installEventFilter
 */
template <class Function> class LambdaEventFilter : public QObject {
public:
    explicit LambdaEventFilter(QObject *obj, Function func) : func(func), QObject{obj} {
        obj->installEventFilter(this);
    }

protected:
    bool eventFilter(QObject *obj, QEvent *e) override { return func(obj, e); }

private:
    const Function func;
};
#endif // LAMBDAEVENTFILTER_H
