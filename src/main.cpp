#include <QQuickView>
#include <QQmlContext>
//#include <QApplication>

#include <QApplication>
#include <QQmlApplicationEngine>

//#include <QSqlTableModel>
//classes
#include "domainmodel.h"//<--- user class included there
#include "networkmodel.h"
#include  "sqlquerymodel.h"
#include <QQmlDebuggingEnabler>




int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);

    //create a sql object
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("local");
    db.setUserName("root");
    db.setPassword("password");
    db.open();

    //create a sqlQueryModel object with 0 as qobject
    SqlQueryModel *someSqlModel = new SqlQueryModel(0);//necessery to give zero

    //set query for the created model
    someSqlModel->setQuery(" SELECT `time`, energy, user_name, address FROM smartgrid.`usage`");//query values for model

    User user;
    //DomainModel domList;
    DomainModel dom_list(&user);

    NetworkModel net_list(&user);
    net_list.refresh();
    //make the created objects available to qml as qml objects
    QQmlApplicationEngine engine;

    QQmlDebuggingEnabler enabler;

    engine.rootContext()->setContextProperty("applicationDirPath", QGuiApplication::applicationDirPath());
    engine.rootContext()->setContextProperty("host",&user);
    engine.rootContext()->setContextProperty("domain_list",QVariant::fromValue(&dom_list));
    engine.rootContext()->setContextProperty("network_list",QVariant::fromValue(&net_list));
    engine.rootContext()->setContextProperty("address_list",QVariant::fromValue(someSqlModel));
    engine.addImportPath("/home/dravigon/qt/Qvirinterface" );

    //create the qml instance
    engine.load(QUrl(QLatin1String("qrc:/qml/main.qml")));

    return app.exec();
}
