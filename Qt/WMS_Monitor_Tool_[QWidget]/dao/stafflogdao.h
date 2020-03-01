#ifndef STAFFLOGDAO_H
#define STAFFLOGDAO_H

#include <QObject>
#include <QtSql/QtSql>
#include "basedao.h"

class stafflogdao : public basedao
{
public:
    stafflogdao():basedao(){
        rtmodel = new QSqlRelationalTableModel(this, this->getdatabase());
        query = new QSqlQuery(this->getdatabase());
    }
    ~stafflogdao(){}

    bool showstafflog();

    bool clearstafflog(int);

    bool insertstafflog(int);

    bool exportstafflogtotxt(QString filename);

    bool exportstafflogtoexcel(QString filename);

    QSqlRelationalTableModel* getrtmodel(){
        return rtmodel;
    }

private:
    QSqlRelationalTableModel *rtmodel;
    QSqlQuery *query;
};

#endif // STAFFLOGDAO_H
