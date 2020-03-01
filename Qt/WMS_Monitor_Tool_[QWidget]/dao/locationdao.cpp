#pragma execution_character_set("utf-8")
#include <QDebug>
#include "locationdao.h"

bool locationdao::showstoragelocation()
{
    if(this->connection()){
        rtmodel->setTable("storagelocation");
        rtmodel->setRelation(2,QSqlRelation("coupling","idcoupling","model"));
        if(rtmodel->select()){
            rtmodel->setHeaderData(0, Qt::Horizontal, "编号");
            rtmodel->setHeaderData(1, Qt::Horizontal, "位置");
            rtmodel->setHeaderData(2, Qt::Horizontal, "管料");
            rtmodel->setHeaderData(3, Qt::Horizontal, "数量");
            rtmodel->setHeaderData(4, Qt::Horizontal, "单位");
            rtmodel->setHeaderData(5, Qt::Horizontal, "状态");
            rtmodel->setHeaderData(6, Qt::Horizontal, "其他");
            rtmodel->setEditStrategy(QSqlTableModel::OnManualSubmit);

            return true;
        }
        else{
            qDebug()<<"showstoragelocation query failed!";
            return false;
        }
    }
    else{
        qDebug()<<"showstoragelocation connection failed!";
        return false;
    }
}
