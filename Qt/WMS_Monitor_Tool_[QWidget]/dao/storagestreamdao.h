#ifndef STORAGESTREAMDAO_H
#define STORAGESTREAMDAO_H

#include <QObject>
#include <QtSql/QtSql>
#include <dao/basedao.h>

class storagestreamdao : public basedao
{
public:
    storagestreamdao():basedao(){
        rtmodel = new QSqlRelationalTableModel(this, this->getdatabase());
    }
    ~storagestreamdao(){}

    bool showstoragein();

    bool showstorageout();

    bool showstorageinventory();

    bool showstoragelog(int);

    void clearstoragelog(int);

    QStringList streamlocation(QStringList &);

    QStringList streammodel(QStringList &);

    QStringList streamchargeman(QStringList &);

    int storageinrecord(QString,QString,int,QString,QString);

    int storageoutrecord(QString,int,QString);

    int stocktakerecord(QString,QString,int,QString,QString);

    bool exportstoragelogtotxt(const QString &,int);

    QSqlRelationalTableModel* getrtmodel(){
        return rtmodel;
    }

private:
    QSqlRelationalTableModel *rtmodel;
    QSqlQuery query;
};

#endif // STORAGESTREAMDAO_H
