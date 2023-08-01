#ifndef ICONUTILS_H
#define ICONUTILS_H

#include <QtWidgets>

class IconUtils {
public:
    static void setSizes(const QList<int> &value);

    static QIcon fromTheme(const QString &name);
    static QIcon fromResources(const char *name, const QColor &background);

    template <class T> static void setWidgetIcon(T *obj, const char *name) {
        auto setObjIcon = [obj, name] {
            obj->setIcon(icon(name, obj->palette().color(obj->backgroundRole())));
        };
        obj->connect(qApp, &QGuiApplication::paletteChanged, obj, setObjIcon);
        setObjIcon();
    }
    template <class T> static void setIcon(T *obj, const char *name) {
        auto setObjIcon = [obj, name] { obj->setIcon(icon(name)); };
        setObjIcon();
        obj->connect(qApp, &QGuiApplication::paletteChanged, obj, setObjIcon);
    }
    static QIcon icon(const char *name,
                      const QColor &background = qApp->palette().window().color());
    static QIcon icon(const QList<const char *> &names,
                      const QColor &background = qApp->palette().window().color());

    static QIcon tintedIcon(const char *name, const QColor &color, const QList<QSize> &sizes);
    static QIcon tintedIcon(const char *name, const QColor &color, const QSize &size);
    static void tint(QPixmap &pixmap,
                     const QColor &color,
                     QPainter::CompositionMode mode = QPainter::CompositionMode_SourceIn);

    // HiDPI stuff
    static QPixmap pixmap(const char *name, const qreal pixelRatio);
    static QPixmap pixmap(const QString &filename, const qreal pixelRatio);
    static QPixmap
    iconPixmap(const char *name, int size, const QColor &background, const qreal pixelRatio);

private:
    IconUtils() {}
    static QImage grayscaled(const QImage &image);
};

#endif // ICONUTILS_H
