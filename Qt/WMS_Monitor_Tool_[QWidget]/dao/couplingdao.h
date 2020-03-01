#ifndef COUPLINGDAO_H
#define COUPLINGDAO_H

#include <QObject>
#include <QtSql/QtSql>
#include <dao/basedao.h>

class couplingdao : public basedao
{
public:
    couplingdao():basedao(){
        rtmodel = new QSqlRelationalTableModel(this, this->getdatabase());
    }

    ~couplingdao(){}

    bool showcoupling();

    QSqlRelationalTableModel* getrtmodel(){
        return rtmodel;
    }

private:
    QSqlRelationalTableModel *rtmodel;
};

#endif // COUPLINGDAO_H
