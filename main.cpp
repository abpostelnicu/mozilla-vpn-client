#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "mozillavpn.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QScopedPointer<MozillaVPN> mozillaVPN(new MozillaVPN());
    mozillaVPN->initialize();

    QQmlApplicationEngine engine;
    qmlRegisterSingletonInstance("Mozilla.VPN", 1, 0, "VPN", mozillaVPN.get());

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl) {
                QCoreApplication::exit(-1);
            }
        },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
