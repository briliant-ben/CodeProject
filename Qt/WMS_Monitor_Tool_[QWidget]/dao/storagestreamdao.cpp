#pragma execution_character_set("utf-8")
#include <QDebug>
#include "storagestreamdao.h"

bool storagestreamdao::showstoragein()
{
    if(this->connection()){
        rtmodel->setTable("storagein");
        rtmodel->setRelation(2,QSqlRelation("storagelocation","idstoragelocation","location"));
        rtmodel->setRelation(3,QSqlRelation("coupling","idcoupling","model"));
        if(rtmodel->select()){
            rtmodel->setHeaderData(0, Qt::Horizontal, "编号");
            rtmodel->setHeaderData(1, Qt::Horizontal, "时间");
            rtmodel->setHeaderData(2, Qt::Horizontal, "位置");
            rtmodel->setHeaderData(3, Qt::Horizontal, "管料");
            rtmodel->setHeaderData(4, Qt::Horizontal, "数量");
            rtmodel->setHeaderData(5, Qt::Horizontal, "单位");
            rtmodel->setHeaderData(6, Qt::Horizontal, "状态");
            rtmodel->setHeaderData(7, Qt::Horizontal, "负责人");
            rtmodel->setEditStrategy(QSqlTableModel::OnManualSubmit);
            return true;
        }
        else{
            qDebug()<<"showstoragein query failed!";
            return false;
        }
    }
    else{
        qDebug()<<"showstoragein connection failed!";
        return false;
    }
}

bool storagestreamdao::showstorageout()
{
    if(this->connection()){
        rtmodel->setTable("storageout");
        rtmodel->setRelation(2,QSqlRelation("storagelocation","idstoragelocation","location"));
        rtmodel->setRelation(3,QSqlRelation("coupling","idcoupling","model"));
        if(rtmodel->select()){
            rtmodel->setHeaderData(0, Qt::Horizontal, "编号");
            rtmodel->setHeaderData(1, Qt::Horizontal, "时间");
            rtmodel->setHeaderData(2, Qt::Horizontal, "位置");
            rtmodel->setHeaderData(3, Qt::Horizontal, "管料");
            rtmodel->setHeaderData(4, Qt::Horizontal, "数量");
            rtmodel->setHeaderData(5, Qt::Horizontal, "单位");
            rtmodel->setHeaderData(6, Qt::Horizontal, "状态");
            rtmodel->setHeaderData(7, Qt::Horizontal, "负责人");
            rtmodel->setEditStrategy(QSqlTableModel::OnManualSubmit);
            return true;
        }
        else{
            qDebug()<<"showstorageout query failed!";
            return false;
        }
    }
    else{
        qDebug()<<"showstorageout connection failed!";
        return false;
    }
}

bool storagestreamdao::showstorageinventory()
{
    if(this->connection()){
        rtmodel->setTable("stocktake");
        rtmodel->setRelation(2,QSqlRelation("storagelocation","idstoragelocation","location"));
        rtmodel->setRelation(3,QSqlRelation("coupling","idcoupling","model"));
        if(rtmodel->select()){
            rtmodel->setHeaderData(0, Qt::Horizontal, "编号");
            rtmodel->setHeaderData(1, Qt::Horizontal, "时间");
            rtmodel->setHeaderData(2, Qt::Horizontal, "位置");
            rtmodel->setHeaderData(3, Qt::Horizontal, "管料");
            rtmodel->setHeaderData(4, Qt::Horizontal, "数量");
            rtmodel->setHeaderData(5, Qt::Horizontal, "单位");
            rtmodel->setHeaderData(6, Qt::Horizontal, "状态");
            rtmodel->setHeaderData(7, Qt::Horizontal, "负责人");
            rtmodel->setEditStrategy(QSqlTableModel::OnManualSubmit);
            return true;
        }
        else{
            qDebug()<<"showstorageinventory query failed!";
            return false;
        }
    }
    else{
        qDebug()<<"showstorageinventory connection failed!";
        return false;
    }
}

bool storagestreamdao::showstoragelog(int which)
{
    if(this->connection()){
        switch (which) {
        case 0:
            rtmodel->setTable("storageinview");
            break;
        case 1:
            rtmodel->setTable("storageoutview");
            break;
        case 2:
            rtmodel->setTable("stocktakeview");
            break;
        default:
            break;
        }
        if(rtmodel->select()){
            rtmodel->setHeaderData(0, Qt::Horizontal, "时间");
            rtmodel->setHeaderData(1, Qt::Horizontal, "批次数");
            rtmodel->setHeaderData(2, Qt::Horizontal, "总个数");
            rtmodel->setHeaderData(3, Qt::Horizontal, "负责人");
            rtmodel->setEditStrategy(QSqlTableModel::OnManualSubmit);
            return true;
        }else{
            qDebug()<<"showstoragelog query failed!";
            return false;
        }
    }
    else{
        qDebug()<<"showstoragelog connection failed!";
        return false;
    }
}

void storagestreamdao::clearstoragelog(int arg)
{
    if(this->connection()){
        switch (arg) {
        case 00:
            query.prepare("delete from storagein");
            break;
        case 01:
            query.prepare("truncate table storagein");
            break;
        case 10:
            query.prepare("delete from storageout");
            break;
        case 11:
            query.prepare("truncate table storageout");
            break;
        case 20:
            query.prepare("delete from stocktake");
            break;
        case 21:
            query.prepare("truncate table stocktake");
            break;
        default:
            break;
        }
        if(!query.exec()){
            qDebug()<<"clearstoragelog query exec failed!";
            return;
        }
        this->closedatabse();
        return;
    }
    else{
        qDebug()<<"clearstoragelog connection failed!";
        return;
    }
}

QStringList storagestreamdao::streamlocation(QStringList &text)
{
    if(this->connection()){
        if(query.exec("select storagelocation.location from wms.storagelocation")){
            while (query.next()) {
                text<<query.value(0).toString();
            }
            return text;
        }
        else{
            qDebug()<<"streamlocation query failed!";
            return text;
        }
    }
    else{
        qDebug()<<"streamlocation connection failed!";
        return text;
    }
}

QStringList storagestreamdao::streammodel(QStringList &text)
{
    if(this->connection()){
        if(query.exec("select coupling.model from wms.coupling")){
            while (query.next()) {
                text<<query.value(0).toString();
            }
            return text;
        }
        else{
            qDebug()<<"streammodel query failed!";
            return text;
        }
    }
    else{
        qDebug()<<"streammodel connection failed!";
        return text;
    }
}

QStringList storagestreamdao::streamchargeman(QStringList &text)
{
    if(this->connection()){
        if(query.exec("select staff.name from wms.staff")){
            while (query.next()) {
                text<<query.value(0).toString();
            }
            return text;
        }
        else{
            qDebug()<<"streamchargeman query failed!";
            return text;
        }
    }
    else{
        qDebug()<<"streamchargeman connection failed!";
        return text;
    }
}

/*
 *error number:
 * 0   ---success!
 * 1   ---coupling not same
 * 2   ---
 * 3   ---
 * 100+---databse error
*/
int storagestreamdao::storageinrecord(QString location,QString model,int quantity,
                                      QString state,QString dutypeople)
{
    int idlocation;
    int idcoupling;
    if(this->connection()){
        query.prepare("select storagelocation.idstoragelocation from wms.storagelocation where location=?");
        query.bindValue(0,location);
        if(query.exec()){
            if(query.first()){
                idlocation = query.value(0).toInt();
            }else{
                return 101;
            }
        }else{
            return 102;
        }

        query.prepare("select coupling.idcoupling from wms.coupling where model=?");
        query.bindValue(0,model);
        if(query.exec()){
            if(query.first()){
                idcoupling = query.value(0).toInt();
            }else{
                return 103;
            }
        }else{
            return 104;
        }

        query.prepare("select * from wms.storagelocation where idstoragelocation=?");
        query.bindValue(0,idlocation);
        if(query.exec()){
            if(query.first()){
                int total = query.value(3).toInt() + quantity;
                if(query.value(3).toInt() == 0){
                    query.prepare("update storagelocation set storagelocation.coupling=?,"
                                  "storagelocation.quantity=?,storagelocation.state=? "
                                  "where storagelocation.idstoragelocation=?");
                    query.bindValue(0,idcoupling);
                    query.bindValue(1,total);
                    query.bindValue(2,state);
                    query.bindValue(3,idlocation);
                    //------------------------------------------------------
                    if(query.exec()){
                        query.prepare("insert into storagein(location,coupling,quantity,state,dutypeople) "
                                      "values(?,?,?,?,?)");
                        query.bindValue(0,idlocation);
                        query.bindValue(1,idcoupling);
                        query.bindValue(2,quantity);
                        query.bindValue(3,state);
                        query.bindValue(4,dutypeople);
                        if(query.exec()){
                            return 0;//success
                        }else{
                            return 105;
                        }
                    }else{
                        return 106;
                    }
                    //-----------------------------------------------------
                }else{//query.value(3).toInt() > 0
                    if(idcoupling == query.value(2).toInt() || query.value(2).toInt() == 9999){
                        query.prepare("update storagelocation set storagelocation.quantity=? "
                                      "where storagelocation.idstoragelocation=?");
                        query.bindValue(0,total);
                        query.bindValue(1,idlocation);
                        //------------------------------------------------------
                        if(query.exec()){
                            query.prepare("insert into storagein(location,coupling,quantity,state,dutypeople) "
                                          "values(?,?,?,?,?)");
                            query.bindValue(0,idlocation);
                            query.bindValue(1,idcoupling);
                            query.bindValue(2,quantity);
                            query.bindValue(3,state);
                            query.bindValue(4,dutypeople);
                            if(query.exec()){
                                return 0;//success
                            }else{
                                return 107;
                            }
                        }else{
                            return 108;
                        }
                        //-----------------------------------------------------
                    }else{
                        return 1;//coupling not same
                    }
                }
            }else{
                return 109;
            }
        }else{
            return 110;
        }
    }else{
        return 111;
    }
}

/*
 *error number:
 * 0   ---success!
 * 1   ---quantity too much
 * 2   ---
 * 3   ---
 * 100+---databse error
*/
int storagestreamdao::storageoutrecord(QString location,int quantity,QString dutypeople)
{
    int idlocation;
    int idcoupling;
    int total;
    QString state;
    if(this->connection()){
        query.prepare("select * from wms.storagelocation where storagelocation.location=?");
        query.bindValue(0,location);
        if(query.exec()){
            if(query.first()){
                idlocation = query.value(0).toInt();
                idcoupling = query.value(2).toInt();
                state = query.value(5).toString();
                total = query.value(3).toInt() - quantity;
                if(total >= 0){
                    query.prepare("update storagelocation set storagelocation.quantity=? "
                                  "where storagelocation.idstoragelocation=?");
                    query.bindValue(0,total);
                    query.bindValue(1,idlocation);
                    //-----------------------------------------------------
                    if(query.exec()){
                        query.prepare("insert into storageout(location,coupling,quantity,state,dutypeople) "
                                      "values(?,?,?,?,?)");
                        query.bindValue(0,idlocation);
                        query.bindValue(1,idcoupling);
                        query.bindValue(2,quantity);
                        query.bindValue(3,state);
                        query.bindValue(4,dutypeople);
                        if(query.exec()){
                            return 0;//success
                        }else{
                            return 101;
                        }
                    }else {
                        return 102;
                    }
                    //-----------------------------------------------------
                }else{
                    return 1;//quantity too much
                }
            }else{
                return 103;
            }
        }else{
            return 104;
        }
    }else{
        return 105;
    }
}

int storagestreamdao::stocktakerecord(QString location,QString model,int quantity,
                                      QString state,QString dutypeople)
{
    int idlocation;
    int idcoupling;
    if(this->connection()){
        query.prepare("select storagelocation.idstoragelocation from wms.storagelocation where location=?");
        query.bindValue(0,location);
        if(query.exec()){
            if(query.first()){
                idlocation = query.value(0).toInt();
            }else{
                return 101;
            }
        }else{
            return 102;
        }

        query.prepare("select coupling.idcoupling from wms.coupling where model=?");
        query.bindValue(0,model);
        if(query.exec()){
            if(query.first()){
                idcoupling = query.value(0).toInt();
            }else{
                return 103;
            }
        }else{
            return 104;
        }

        query.prepare("insert into stocktake(location,coupling,quantity,state,dutypeople) "
                      "values(?,?,?,?,?)");
        query.bindValue(0,idlocation);
        query.bindValue(1,idcoupling);
        query.bindValue(2,quantity);
        query.bindValue(3,state);
        query.bindValue(4,dutypeople);
        if(query.exec()){
            return 0;//success
        }else{
            return 105;
        }
    }else{
        return 106;
    }
}

bool storagestreamdao::exportstoragelogtotxt(const QString &filename, int table)
{
    //qDebug()<<filename;
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        //        qDebug()<<file.exists();
        qDebug()<<"file open failed!"<<file.errorString();
        return false;
    }
    QTextStream out(&file);
    switch (table) {
    case 0:
        out<<"********************************************************/"<<"\n"
          <<"THIS IS A STORAGEINLOG EXPORT FROM INTELLIGNET WMS SYSTEM!"<<"\n"
         <<"********************************************************/"<<"\n"
        <<"ID		TIME 		LOCATION	MODEL	UNIT    STATE   DUTYPEOPLE"<<"\n";
        query.exec("select storagein.idstoragein,storagein.time,storagelocation.location,"
                   "coupling.model,storagein.unit,storagein.state,storagein.dutypeople "
                   "from wms.storagein,wms.storagelocation,wms.coupling "
                   "where storagein.location=storagelocation.idstoragelocation and "
                   "storagein.coupling=coupling.idcoupling");
        break;
    case 1:
        out<<"********************************************************/"<<"\n"
          <<"THIS IS A STORAGEOUTLOG EXPORT FROM INTELLIGNET WMS SYSTEM!"<<"\n"
         <<"********************************************************/"<<"\n"
        <<"ID		TIME 		LOCATION	MODEL	UNIT    STATE   DUTYPEOPLE"<<"\n";
        query.exec("select storageout.idstorageout,storageout.time,storagelocation.location,"
                   "coupling.model,storageout.unit,storageout.state,storageout.dutypeople "
                   "from wms.storageout,wms.storagelocation,wms.coupling "
                   "where storageout.location=storagelocation.idstoragelocation and "
                   "storageout.coupling=coupling.idcoupling");
        break;
    case 2:
        out<<"********************************************************/"<<"\n"
          <<"THIS IS A STOCKTAKELOG EXPORT FROM INTELLIGNET WMS SYSTEM!"<<"\n"
         <<"********************************************************/"<<"\n"
        <<"ID		TIME 		LOCATION	MODEL	UNIT    STATE   DUTYPEOPLE"<<"\n";
        query.exec("select stocktake.idstocktake,stocktake.time,storagelocation.location,"
                   "coupling.model,stocktake.unit,stocktake.state,stocktake.dutypeople "
                   "from wms.stocktake,wms.storagelocation,wms.coupling "
                   "where stocktake.location=storagelocation.idstoragelocation and "
                   "stocktake.coupling=coupling.idcoupling");
        break;
    default:
        break;
    }
    while(query.next()){
        out<<query.value(0).toInt()<<"\t"
          <<query.value(1).toDateTime().toString(Qt::SystemLocaleLongDate)<<"\t"
         <<query.value(2).toString()<<"\t\t"
        <<query.value(3).toString()<<"\t"
        <<query.value(4).toString()<<"\t"
        <<query.value(5).toString()<<"\t"
        <<query.value(6).toString()<<"\n";
    }
    file.close();
    return true;
}



