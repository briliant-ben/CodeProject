#pragma execution_character_set("utf-8")
#include <QDebug>
#include "staffdao.h"

bool staffdao::login(QString number, QString password){
    QString sql = "select staff.idstaff,staff.name,staff.role from wms.staff where number = ? and password = ?";
    if(this->connection()){
        //        if(this->getdatabase().isOpen()){
        //            qDebug()<<"is opened!";
        //        }
        QSqlQuery sqlquery(this->getdatabase());
        sqlquery.prepare(sql);
        sqlquery.bindValue(0, number);
        sqlquery.bindValue(1, password);
        if(sqlquery.exec()){
            if(sqlquery.first()){
                //code transformation due to VS compiler,MINGW will be good here!
                //QTextCodec *codec = QTextCodec::codecForName("GB18030");
                //QByteArray encodedString = codec->fromUnicode(sqlquery.value(0).toString());
                //astaff.setname(encodedString);

                astaff.setid(sqlquery.value(0).toInt());
                astaff.setname(sqlquery.value(1).toString());
                astaff.setrole(sqlquery.value(2).toInt());

                staff::staticid = astaff.getid();
                staff::staticname = astaff.getname();
                staff::staticrole = astaff.getrole();

                sqlquery.prepare("insert into stafflog(staffnumber,staffname,content) values(?,?,?)");
                sqlquery.bindValue(0, this->getstaff().getid());
                sqlquery.bindValue(1, this->getstaff().getid());
                sqlquery.bindValue(2, 1);//1-登录 2-退出 3-操作 4-其他
                if(!sqlquery.exec()){
                   qDebug()<<"insert into stafflog table failed!";
                }

                if(astaff.getrole() == 4){
                    return false;
                }
                this->closedatabse();
                return true;
            }
            qDebug()<<"no match!";
            this->closedatabse();
            return false;
        }
        qDebug()<<"sqlquery failed!";
        this->closedatabse();
        return false;
    }
    qDebug()<<"databse connection failed!";
    return false;
}

bool staffdao::staffregister(QString number, QString password,QString name,
                             QString unit, QString position,
                             QString phone, QString authentication){
    QString sql = "insert into wms.staff(number,password,name,unit,position,phone,authentication,role) values(?,?,?,?,?,?,?,?)";
    if(this->connection()){
        QSqlQuery sqlquery(this->getdatabase());
        sqlquery.prepare(sql);
        //code transformation due to VS compiler,MINGW will be good here!
        //sqlquery.bindValue(N, number.toUtf8());
        sqlquery.bindValue(0, number);
        sqlquery.bindValue(1, password);
        sqlquery.bindValue(2, name);
        sqlquery.bindValue(3, unit);
        sqlquery.bindValue(4, position);
        sqlquery.bindValue(5, phone);
        sqlquery.bindValue(6, authentication);
        sqlquery.bindValue(7, 4);
        if(sqlquery.exec()){
            this->closedatabse();
            return true;
        }
        qDebug()<<"sqlquery failed!";
        this->closedatabse();
        return false;
    }
    qDebug()<<"databse connection failed!";
    return false;
}

bool staffdao::showstaff(){
    if(this->connection()){
        rtmodel->setTable("staff");
        rtmodel->setRelation(10, QSqlRelation("role","idrole","role"));
        if(rtmodel->select()){//rtmodel->QSqlQueryModel::setQuery("select * from staff limit 0,13");
            rtmodel->setHeaderData(0, Qt::Horizontal, "编号");
            rtmodel->setHeaderData(1, Qt::Horizontal, "工号");
            rtmodel->setHeaderData(2, Qt::Horizontal, "密码");
            rtmodel->setHeaderData(3, Qt::Horizontal, "姓名");
            rtmodel->setHeaderData(4, Qt::Horizontal, "单位");
            rtmodel->setHeaderData(5, Qt::Horizontal, "职位");
            rtmodel->setHeaderData(6, Qt::Horizontal, "联系方式");
            rtmodel->setHeaderData(7, Qt::Horizontal, "认证信息");
            rtmodel->setHeaderData(8, Qt::Horizontal, "创建时间");
            rtmodel->setHeaderData(9, Qt::Horizontal, "更新时间");
            rtmodel->setHeaderData(10, Qt::Horizontal, "角色");

            rtmodel->setEditStrategy(QSqlTableModel::OnManualSubmit);//OnFieldChange//OnRowChange//OnManualSubmit
            return true;
        }
        else{
            qDebug()<<"showstaff sqlquery failed!";
            return false;
        }
    }
    else{
        qDebug()<<"showstaff connection failed!";
        return false;
    }
}
