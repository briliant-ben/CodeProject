#pragma execution_character_set("utf-8")
#include <QDebug>
#include "couplingdao.h"

bool couplingdao::showcoupling()
{
    if(this->connection()){
        rtmodel->setTable("coupling");
        if(rtmodel->select()){
            rtmodel->setHeaderData(0, Qt::Horizontal, "编号");
            rtmodel->setHeaderData(1, Qt::Horizontal, "型号");
            rtmodel->setHeaderData(2, Qt::Horizontal, "外径");
            rtmodel->setHeaderData(3, Qt::Horizontal, "接箍外径");
            rtmodel->setHeaderData(4, Qt::Horizontal, "长度");
            rtmodel->setHeaderData(5, Qt::Horizontal, "单个重量");
            rtmodel->setHeaderData(6, Qt::Horizontal, "每筐个数");
            rtmodel->setHeaderData(7, Qt::Horizontal, "总重");
            rtmodel->setEditStrategy(QSqlTableModel::OnManualSubmit);
            return true;
        }
        else{
            qDebug()<<"showcoupling query failed!";
            return false;
        }
    }
    else{
        qDebug()<<"showcoupling connection failed!";
        return false;
    }
}
