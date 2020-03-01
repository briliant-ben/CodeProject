#include "window/loginwindow.h"
#include <QApplication>
#include <QpropertyAnimation>
//#include <QSplashScreen>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF8"));
//    QSplashScreen *splash = new QSplashScreen;
//    splash->setPixmap(QPixmap(":/image/nightsky.jpg"));
//    splash->show();
//    // Loading some items
//    splash->showMessage("Loaded modules",Qt::AlignRight | Qt::AlignTop);
//    qApp->processEvents();

    loginwindow w;
    w.setWindowFlags(Qt::FramelessWindowHint);// | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint
//    w.setWindowTitle("Login Window");
    w.show();

//    splash->finish(&w);

    //Login Window animation
    QPropertyAnimation *animation = new QPropertyAnimation(&w,"windowOpacity");
    animation->setDuration(222);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->start();

    return a.exec();
}
