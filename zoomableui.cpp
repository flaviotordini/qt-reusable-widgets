#include "zoomableui.h"

ZoomableUI::ZoomableUI(QMainWindow &window) : QObject(&window) {
    // May be useful for font sizes set in stylesheets
    // QCoreApplication::setAttribute(Qt::AA_UseStyleSheetPropagationInWidgetStyles, true);

    auto applyZoom = [](int zoom, bool saveSetting = true) {
        // https://doc.qt.io/qt-6/qwidget.html#font-prop

        QSettings settings;
        const int currentZoom = settings.value("zoom").toInt();

        // reset
        int increment = zoom;
        if (zoom == 0) {
            increment = -currentZoom;
        }

        auto font = QApplication::font();
        font.setPointSize(font.pointSize() + increment);
        QApplication::setFont(font);

        for (auto w : QApplication::allWidgets()) {
            auto font = w->font();
            font.setPointSize(font.pointSize() + increment);
            w->setFont(font);
        }

        if (saveSetting) settings.setValue("zoom", currentZoom + increment);
    };

    QSettings settings;
    int zoom = settings.value("zoom").toInt();
    if (zoom) applyZoom(zoom, false);

    auto createAction = [this, applyZoom, &window](QString text, QKeySequence keySeq, int zoom) {
        auto action = new QAction(text, &window);
        action->setShortcut(keySeq);
        window.addAction(action);
        actions.append(action);
        connect(action, &QAction::triggered, &window,
                [&window, applyZoom, zoom] { applyZoom(zoom); });
    };

    createAction(tr("Zoom In"), QKeySequence(Qt::CTRL | Qt::Key_Plus), 1);
    createAction(tr("Zoom Out"), QKeySequence(Qt::CTRL | Qt::Key_Minus), -1);
    createAction(tr("Reset Zoom"), QKeySequence(Qt::CTRL | Qt::Key_0), 0);
}
