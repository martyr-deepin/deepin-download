#include "mainwindow.h"
//#include <qtsingleapplication/qtsingleapplication.h>

#include <DApplication>
#include <DMainWindow>
#include <DWidgetUtil>
#include <QApplication>
#include <QDesktopWidget>
#include <QMessageBox>
#include <QtDBus/QDBusConnection>
#include <QDBusInterface>
#include <QDBusReply>
#include <QGuiApplication>
#include <QScreen>
#include <QRect>
#include <QSize>

#include <QApplication>

#include <iostream>
#include "utils.h"
#include "DLog"


//#include <jcon/json_rpc_client.h>
DWIDGET_USE_NAMESPACE

#define  chromeEXid  "chrome-extension://gopcfccgjpkkpabnbfflbchgaodjbdik/"

int main(int argc, char *argv[])
{


    QString fileURL = "";
    /**
     * 命令行参数
     **/
    if( argc >= 2 ){

        /** 由chrome 扩展发起的应用程序启动 */
        //"chrome-extension://gopcfccgjpkkpabnbfflbchgaodjbdik/"
        if(  strcmp( chromeEXid , argv[1] )  == 0 ){

            unsigned int length = 0;
            for ( int i = 0; i < 4; i++ ){
                length += getwchar();
            }

            /** getwchar() 标准输入流中取出 chrome-extension 传递的参数 */
            for (int i = 0; i < length; i++){
                fileURL += getwchar();
            }


            fileURL = fileURL.mid(1,fileURL.length()-2);
        }
    }

    /** =========================================================================== */

    DApplication::loadDXcbPlugin();
    DApplication app(argc, argv);
    app.loadTranslator();
    app.setOrganizationName("deepin");
    app.setApplicationName("deepin-download");
    app.setApplicationDisplayName(QObject::tr("Deepin Downloader"));
    app.setApplicationVersion("1.0");
    //app.loadTranslator();

    /**
     * 日志
     */
    //Dtk::Core::DLogManager::registerFileAppender();
    //Dtk::Core::DLogManager::registerConsoleAppender();

    /**
    * 单例测试
    **/

    if (!app.setSingleInstance("deepin-download")) {

         qDebug() << "there's an deepin-download instance running.";

         QDBusInterface *iface = new QDBusInterface( "com.deepin.Download",
                                 "/com/deepin/Download",
                                 "com.deepin.Download", QDBusConnection::sessionBus());

         auto reply =  iface->call("ShowDownWindow", fileURL );
         return 0;
    }

    /**
     * 版权信息
     */
    const char *descriptionText = QT_TRANSLATE_NOOP("MainWindow",
                                                    "Deepin Downloader is a built-in downloading tool of "
                                                    "deepin operating system, supporting single and batch download."
                                                    );

    const QString acknowledgementLink = "https://www.deepin.org/acknowledgments/deepin-download";
    app.setProductIcon(QPixmap::fromImage(QImage(Utils::getQrcPath("logo_24.svg"))));
    app.setProductName(DApplication::translate("MainWindow", "Deepin Downloader"));
    app.setApplicationDescription(DApplication::translate("MainWindow", descriptionText) + "\n");
    app.setApplicationAcknowledgementPage(acknowledgementLink);
    app.setWindowIcon(QIcon(Utils::getQrcPath("logo_24.svg")));

    /**
     */
    MainWindow window;

    Utils::applyQss(&window, "main.qss");

    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();
    window.setMinimumSize(QSize(screenGeometry.width() * 1 / 2, screenGeometry.height() * 1 / 2));
    Dtk::Widget::moveToCenter(&window);

    window.show();

    /**
     * 注册DBUS 服务&对象，
    */
    QDBusConnection dbus = QDBusConnection::sessionBus();
    if ( dbus.registerService("com.deepin.Download") ) {

        dbus.registerObject("/com/deepin/Download", &window );
    }

    return app.exec();
    //return 0;
}
