#ifndef STAFFDAO_H
#define STAFFDAO_H

#include <QObject>
#include <QtSql/QtSql>
#include "basedao.h"
#include "entity/staff.h"

class staffdao : public basedao
{
public:
    staffdao():basedao(){
        rtmodel = new QSqlRelationalTableModel(this, this->getdatabase());
    }
    ~staffdao(){}

    bool login(QString number, QString password);

    bool staffregister(QString, QString, QString, QString,
                       QString, QString, QString);
    bool showstaff();

    staff getstaff(){   //void setstaff(){}
        return astaff;
    }

    QSqlRelationalTableModel* getrtmodel(){
        return rtmodel;
    }

private:
    staff astaff;
    QSqlRelationalTableModel *rtmodel;
};

#endif // STAFFDAO_H
