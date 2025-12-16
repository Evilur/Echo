#include "util/path.h"
#include "config/settings.h"
#include "type/string.h"
#include "util/logger.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QTranslator>

int main(int argc, char* argv[]) {
    /* Init static classes */
    Path::Init();
    Settings::Init();

    /* Create a GUI application object */
    INFO_LOG("Creating the Qt application");
    QGuiApplication app(argc, argv);

    /* Load translation */
    QTranslator translator;
    if(translator.load((const char*)String::Format(
            ":/i18n/%s.qm",
            (const char*)Settings::UI::language
        ))) {
        app.installTranslator(&translator);
        INFO_LOG("Translation '%s' has been loaded",
                 (const char*)Settings::UI::language);
    } else WARN_LOG("Failed to load the '%s' translation",
                    (const char*)Settings::UI::language);

    /* Create a QML engine */
    QQmlApplicationEngine engine;

    /* Load the main window url */
    const QUrl url(QStringLiteral("qrc:/app/MainWindow.qml"));
    engine.load(url);

    /* Run the application */
    INFO_LOG("Starting the application");
    return app.exec();
}