#include "fontutils.h"

#ifdef APP_MAC
#include "macutils.h"
#endif

namespace {

QFont createFont(bool isBold, double sizeScale) {
    QFont font;
    font.setPointSize(font.pointSize() * sizeScale);
    font.setBold(isBold);
    return font;
}

QFont createFontWithMinSize(bool isBold, double sizeScale) {
    const int minPixels = 11;
    QFont font = createFont(isBold, sizeScale);
    if (font.pixelSize() < minPixels) font.setPixelSize(minPixels);
    return font;
}

} // namespace

const QFont &FontUtils::small() {
    static const QFont font = createFontWithMinSize(false, .9);
    return font;
}

const QFont &FontUtils::smallBold() {
    static const QFont font = createFontWithMinSize(true, .9);
    return font;
}

const QFont &FontUtils::medium() {
    static const QFont font = createFont(false, 1.25);
    return font;
}

const QFont &FontUtils::mediumBold() {
    static const QFont font = createFont(true, 1.25);
    return font;
}

const QFont &FontUtils::big() {
    static const QFont font = createFont(false, 1.5);
    return font;
}

const QFont &FontUtils::bigBold() {
    static const QFont font = createFont(true, 1.5);
    return font;
}

QFont FontUtils::light(int pointSize) {
#ifdef APP_MAC
    QVariant v = mac::lightFont(pointSize);
    if (!v.isNull()) return qvariant_cast<QFont>(v);
#endif
    QFont f;
#ifdef APP_WIN
    f.setFamily(QStringLiteral("Segoe UI Light"));
#endif
    f.setPointSize(pointSize);
    f.setStyleName(QStringLiteral("Light"));
    f.setWeight(QFont::Light);
    return f;
}
