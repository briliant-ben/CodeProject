#ifndef BASEDAO_H
#define BASEDAO_H

#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QtSql/QtSql>

class basedao:public QObject
{
public:
    basedao();
    ~basedao(){}
    bool connection();
    void closedatabse();
    QSqlDatabase getdatabase(){
        return DataBaseConn;
    }
private:
    QSqlDatabase DataBaseConn;
};

#endif // BASEDAO_H
