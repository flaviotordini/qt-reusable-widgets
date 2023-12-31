#include "iconutils.h"

namespace {

QList<int> sizes;

} // namespace

void IconUtils::setSizes(const QList<int> &value) {
    sizes = value;
}

QIcon IconUtils::fromTheme(const QString &name) {
    static const QLatin1String symbolic("-symbolic");
    if (name.endsWith(symbolic)) return QIcon::fromTheme(name);
    QIcon icon = QIcon::fromTheme(name + symbolic);
    if (icon.isNull()) return QIcon::fromTheme(name);
    return icon;
}

QIcon IconUtils::fromResources(const char *name, const QColor &background) {
    qDebug() << "Creating icon" << name;
    static const QLatin1String active("_active");
    static const QLatin1String selected("_selected");
    static const QLatin1String disabled("_disabled");
    static const QLatin1String checked("_checked");
    static const QLatin1String ext(".png");
    static const QLatin1String darkPath(":/icons/dark/");
    static const QLatin1String lightPath(":/icons/light/");

    const QLatin1String path = background.value() > 128 ? lightPath : darkPath;

    QIcon icon;

    auto addIconFile = [](QIcon &icon, const QString &filename, int size,
                          QIcon::Mode mode = QIcon::Normal, QIcon::State state = QIcon::Off) {
        if (QFile::exists(filename)) {
            icon.addFile(filename, QSize(size, size), mode, state);
        }
    };

    for (int size : qAsConst(sizes)) {
        const QString pathAndName = path + QString::number(size) + '/' + name;
        QString iconFilename = pathAndName + ext;
        if (QFile::exists(iconFilename)) {
            addIconFile(icon, iconFilename, size);
            addIconFile(icon, pathAndName + active + ext, size, QIcon::Active);
            addIconFile(icon, pathAndName + selected + ext, size, QIcon::Selected);
            addIconFile(icon, pathAndName + disabled + ext, size, QIcon::Disabled);
            addIconFile(icon, pathAndName + checked + ext, size, QIcon::Normal, QIcon::On);
        }
    }
    return icon;
}

QIcon IconUtils::icon(const char *name, const QColor &background) {
    static QMap<QByteArray, QIcon> cache = [] {
        qDebug() << "Init icon cache";
        QMap<QByteArray, QIcon> c;
        QObject::connect(qApp, &QApplication::paletteChanged, qApp, [&c]() {
            qDebug() << "Clearing icon cache";
            c.clear();
        });
        return c;
    }();

    QByteArray key = QByteArray::fromRawData(name, strlen(name)).append(background.value());
    auto i = cache.constFind(key);
    if (i != cache.constEnd()) return i.value();

    QIcon icon;
#ifdef APP_UBUNTU_NO
    icon = fromTheme(name);
    if (icon.isNull()) icon = fromResources(name, background);
#else
    icon = fromResources(name, background);
#endif

    cache.insert(key, icon);
    return icon;
}

QIcon IconUtils::icon(const QList<const char *> &names, const QColor &background) {
    QIcon icon;
    for (auto name : names) {
        icon = IconUtils::icon(name, background);
        if (!icon.availableSizes().isEmpty()) break;
    }
    return icon;
}

QIcon IconUtils::tintedIcon(const char *name, const QColor &color, const QList<QSize> &sizes) {
    QIcon i = IconUtils::icon(name);
    QIcon t;
    // if (sizes.isEmpty()) sizes = i.availableSizes();
    for (const QSize &size : sizes) {
        QPixmap pixmap = i.pixmap(size);
        tint(pixmap, color);
        t.addPixmap(pixmap);
    }
    return t;
}

QIcon IconUtils::tintedIcon(const char *name, const QColor &color, const QSize &size) {
    return IconUtils::tintedIcon(name, color, QList<QSize>() << size);
}

QImage IconUtils::grayscaled(const QImage &image) {
    QImage img = image;
    int pixels = img.width() * img.height();
    unsigned int *data = (unsigned int *)img.bits();
    for (int i = 0; i < pixels; ++i) {
        int val = qGray(data[i]);
        data[i] = qRgba(val, val, val, qAlpha(data[i]));
    }
    return img;
}

void IconUtils::tint(QPixmap &pixmap, const QColor &color, QPainter::CompositionMode mode) {
    QPainter painter(&pixmap);
    painter.setCompositionMode(mode);
    painter.fillRect(pixmap.rect(), color);
}

QPixmap IconUtils::pixmap(const QString &filename, const qreal pixelRatio) {
    // Check if a "@2x" file exists
    if (pixelRatio > 1.0) {
        int dotIndex = filename.lastIndexOf('.');
        if (dotIndex != -1) {
            QString at2xfileName = filename;
            at2xfileName.insert(dotIndex, "@2x");
            if (QFile::exists(at2xfileName)) {
                QPixmap pixmap(at2xfileName);
                pixmap.setDevicePixelRatio(pixelRatio);
                return pixmap;
            }
        }
    }
    return QPixmap(filename);
}
