#ifndef LOCATIONDAO_H
#define LOCATIONDAO_H

#include <QObject>
#include <QtSql/QtSql>
#include <dao/basedao.h>

class locationdao : public basedao
{
public:
    locationdao():basedao(){
        rtmodel = new QSqlRelationalTableModel(this, this->getdatabase());
    }

    ~locationdao(){}

    bool showstoragelocation();

    QSqlRelationalTableModel* getrtmodel(){
        return rtmodel;
    }

private:
    QSqlRelationalTableModel *rtmodel;
};

#endif // LOCATIONDAO_H
