
#include <Qt3DQuickExtras/qt3dquickwindow.h>
#include <Qt3DQuick/QQmlAspectEngine>
#include <QGuiApplication>
#include <QApplication>
#include <QQmlEngine>
#include <QQmlContext>
#include <QOpenGLContext>

#include <QQuickView>

//classes
#include "Domain/domainmodel.h"//<--- user class included there
#include "Network/networkmodel.h"

#include "contoller.h"

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

    Contoller contoller;
    //make the created objects available to qml as qml objects
     Qt3DExtras::Quick::Qt3DQuickWindow  view;

            qRegisterMetaType<HostModel*>("HostModel*" );
    view.engine()->qmlEngine()->rootContext()->setContextProperty("applicationDirPath", QGuiApplication::applicationDirPath());
    view.engine()->qmlEngine()->rootContext()->setContextProperty("host",&user);
    view.engine()->qmlEngine()->rootContext()->setContextProperty("contoller",QVariant::fromValue(&contoller));
    view.engine()->qmlEngine()->rootContext()->setContextProperty("domain_list",QVariant::fromValue(&dom_list));
    view.engine()->qmlEngine()->rootContext()->setContextProperty("network_list",QVariant::fromValue(&net_list));
    view.engine()->qmlEngine()->rootContext()->setContextProperty("address_list",QVariant::fromValue(someSqlModel));
    view.engine()->qmlEngine()->addImportPath("/home/dravigon/qt/Qvirinterface" );

    //create the qml instance
    view.setSource(QUrl(QLatin1String("qrc:/qml/main.qml")));
    view.show();


    return app.exec();

}
