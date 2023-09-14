#include "seekslider.h"

#include <QProxyStyle>

class MyProxyStyle : public QProxyStyle {
public:
    int styleHint(StyleHint hint,
                  const QStyleOption *option = nullptr,
                  const QWidget *widget = nullptr,
                  QStyleHintReturn *returnData = nullptr) const {
        if (hint == SH_Slider_AbsoluteSetButtons) return Qt::LeftButton;
        return QProxyStyle::styleHint(hint, option, widget, returnData);
    }
};

SeekSlider::SeekSlider(QWidget *parent) : QSlider(parent) {
    setStyle(new MyProxyStyle());
}
