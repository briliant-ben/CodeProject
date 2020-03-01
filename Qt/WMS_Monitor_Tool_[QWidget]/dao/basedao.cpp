#include "basedao.h"
#include <QDebug>

basedao::basedao(){
    DataBaseConn = QSqlDatabase();

    //    QString DataBase = "QMYSQL";
    //    QString HostName= "127.0.0.1";
    //    QString DataBaseName= "wms";
    //    qint32 Port= 3306;
    //    QString UserName= "root";
    //    QString Password= "mysql-2007112";

    if(QSqlDatabase::contains("qt_sql_default_connection")){
        DataBaseConn = QSqlDatabase::database("qt_sql_default_connection");
    }
    else{
        DataBaseConn = QSqlDatabase::addDatabase("QMYSQL");
    }
    DataBaseConn.setHostName("127.0.0.1");
    DataBaseConn.setDatabaseName("wms");
    DataBaseConn.setPort(3306);
    DataBaseConn.setUserName("root");
    DataBaseConn.setPassword("mysql-2007112");
}

bool basedao::connection(){
    if(DataBaseConn.open()){
        qDebug()<<"databese opened!";
        return true;
    }
    return false;
}

void basedao::closedatabse(){
    DataBaseConn.close();
    //    return (!DataBaseConn.isOpen());
}
