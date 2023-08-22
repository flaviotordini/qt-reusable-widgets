#include "zoomableui.h"

ZoomableUI::ZoomableUI(QMainWindow &window) : QObject(&window) {
    // Enable font propagation for widgets that have stylesheets
    QCoreApplication::setAttribute(Qt::AA_UseStyleSheetPropagationInWidgetStyles);

    static int defaultZoom = 0;
#ifdef Q_OS_MAC
    defaultZoom = 2;
#endif

    auto applyZoom = [](int zoom, bool saveSetting = true) {
        QSettings settings;
        const int currentZoom = settings.value("zoom", defaultZoom).toInt();

        // reset
        int increment = zoom;
        if (zoom == 0) {
            increment = -currentZoom;
        }

#ifdef Q_OS_MAC
        static auto defaultAppFont = QApplication::font();
#endif

        auto appFont = QApplication::font();
        appFont.setPointSize(appFont.pointSize() + increment);
        QApplication::setFont(appFont);

        // fix font for widgets that have a custom font
        // either by CSS or by QWidget::setFont
        for (auto w : QApplication::allWidgets()) {
            if (w->testAttribute(Qt::WA_SetFont)) {
                // has custom font
                auto font = w->font();
                font.setPointSize(font.pointSize() + increment);
                w->setFont(font);
            }
        }

#ifdef Q_OS_MAC
        // Mac style does not support bigger sizes for buttons
        // https://bugreports.qt.io/browse/QTBUG-116337
        if (QApplication::style()->name() != "Fusion")
            QApplication::setFont(defaultAppFont, "QAbstractButton");
#endif

        if (saveSetting) settings.setValue("zoom", currentZoom + increment);
    };

    QSettings settings;
    int zoom = settings.value("zoom", defaultZoom).toInt();
    if (zoom) applyZoom(zoom, false);

    auto createAction = [this, applyZoom, &window](QString text, QKeySequence keySeq, int zoom) {
        auto action = new QAction(text, &window);
        action->setShortcut(keySeq);
        window.addAction(action);
        actions.append(action);
        connect(action, &QAction::triggered, this, [applyZoom, zoom] { applyZoom(zoom); });
    };

    createAction(tr("Zoom In"), QKeySequence(Qt::CTRL | Qt::Key_Plus), 1);
    createAction(tr("Zoom Out"), QKeySequence(Qt::CTRL | Qt::Key_Minus), -1);
    createAction(tr("Reset Zoom"), QKeySequence(Qt::CTRL | Qt::Key_0), 0);
}
