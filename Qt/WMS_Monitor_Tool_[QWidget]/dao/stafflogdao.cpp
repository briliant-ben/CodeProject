#pragma execution_character_set("utf-8")
#include <QFile>
#include <QAxObject>
#include "stafflogdao.h"

bool stafflogdao::showstafflog(){
    if(this->connection()){
        rtmodel->setTable("stafflog");
        rtmodel->setRelation(2,QSqlRelation("staff","idstaff","number"));
        rtmodel->setRelation(3,QSqlRelation("staff","idstaff","name"));
        rtmodel->setEditStrategy(QSqlTableModel::OnManualSubmit);
        if(rtmodel->select()){
            rtmodel->setHeaderData(0, Qt::Horizontal, "编号");
            rtmodel->setHeaderData(1, Qt::Horizontal, "时间");
            rtmodel->setHeaderData(2, Qt::Horizontal, "工号");
            rtmodel->setHeaderData(3, Qt::Horizontal, "姓名");
            rtmodel->setHeaderData(4, Qt::Horizontal, "操作内容");
            return true;
        }
        else{
            qDebug()<<"showstafflog query failed!";
            return false;
        }
    }
    else{
        qDebug()<<"showstafflog connection failed!";
        return false;
    }
}

bool stafflogdao::clearstafflog(int arg){
    if(this->connection()){
        if(arg == 0){
            query->prepare("detele from stafflog");//should need judgement
        }
        else{
            query->prepare("truncate table stafflog");//should need judgement
        }
        if(!query->exec()){
            qDebug()<<"clearstafflog query exec failed!";
            return false;
        }
        this->closedatabse();
        return true;
    }
    else{
        qDebug()<<"clearstafflog connection failed!";
        return false;
    }
}

bool stafflogdao::insertstafflog(int id){
    if(this->connection()){
        query->prepare("insert into stafflog(staffnumber,staffname,content) values(?,?,?)");
        query->bindValue(0, id);
        query->bindValue(1, id);
        query->bindValue(2, 2);//1-登录 2-退出 3-操作 4-其他
        if(!query->exec()){
            qDebug()<<"insert into stafflog table failed!";
        }
        this->closedatabse();
        return true;
    }
    else{
        qDebug()<<"insert into stafflog failed!";
        return false;
    }
}

bool stafflogdao::exportstafflogtotxt(QString filename)
{
    //qDebug()<<filename;
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        //        qDebug()<<file.exists();
        qDebug()<<"file open failed!"<<file.errorString();
        return false;
    }
    QTextStream out(&file);
    out<<"/*****************************************************/"<<"\n"
      <<"THIS IS A STAFFLOG EXPORT FROM INTELLIGNET WMS SYSTEM!"<<"\n"
     <<"******************************************************/"<<"\n"
    <<"ID		TIME		NUMBER	NAME	CONTENT"<<"\n";
    query->exec("select stafflog.idstafflog,stafflog.time,staff.number,staff.name,stafflog.content "
                "from stafflog,staff where stafflog.staffnumber=staff.idstaff");
    while (query->next()) {
        out<<query->value(0).toInt()<<"\t"
          <<query->value(1).toDateTime().toString(Qt::SystemLocaleLongDate)<<"\t"
         <<query->value(2).toString()<<"\t"
        <<query->value(3).toString()<<"\t"
        <<query->value(4).toString()<<"\n";
    }
    file.close();
    return true;
}

bool stafflogdao::exportstafflogtoexcel(QString filename)
{
    QAxObject *excel = new QAxObject;//new QAxObject("Excel.Application");
    if (excel->setControl("Excel.Application")){
        qDebug()<<"IN!";
        excel->dynamicCall("SetVisible (bool Visible)","false");
        excel->setProperty("DisplayAlerts", false);
        QAxObject *workbooks = excel->querySubObject("WorkBooks");
        workbooks->dynamicCall("Add");\
        QAxObject *workbook = excel->querySubObject("ActiveWorkBook");
        QAxObject *worksheet = workbook->querySubObject("Worksheets(int)", 1);
        QAxObject *range = worksheet->querySubObject("Cells(int,int)", 1, 1);
        range->dynamicCall("SetValue(const QString&)", QString("Intelligent WMS System staff log---%1")
                           .arg(QDateTime::currentDateTime().toString(Qt::SystemLocaleLongDate)));
        //        cell->querySubObject("Font")->setProperty("Size", 18);
        //        worksheet->querySubObject("Range(const QString&)", "1:1")->setProperty("RowHeight", 30);
        worksheet->querySubObject("Cells(int,int)", 2, 1)->dynamicCall("SetValue(const QString&)","ID");
        worksheet->querySubObject("Cells(int,int)", 2, 2)->dynamicCall("SetValue(const QString&)","TIME");
        worksheet->querySubObject("Cells(int,int)", 2, 3)->dynamicCall("SetValue(const QString&)","NUMBER");
        worksheet->querySubObject("Cells(int,int)", 2, 4)->dynamicCall("SetValue(const QString&)","NAME");
        worksheet->querySubObject("Cells(int,int)", 2, 5)->dynamicCall("SetValue(const QString&)","CONTENT");

        if(query->exec("select stafflog.idstafflog,stafflog.time,staff.number,staff.name,stafflog.content "
                       "from stafflog,staff where stafflog.staffnumber=staff.idstaff")){
            int i=1;
            while (query->next()) {//query->size()
                worksheet->querySubObject("Cells(int,int)", 2+i, 1)
                        ->dynamicCall("SetValue(const QString&)", query->value(0).toString());
                worksheet->querySubObject("Cells(int,int)", 2+i, 2)
                        ->dynamicCall("SetValue(const QString&)", query->value(1).toDateTime().toString(Qt::SystemLocaleLongDate));
                worksheet->querySubObject("Cells(int,int)", 2+i, 3)
                        ->dynamicCall("SetValue(const QString&)", query->value(2).toString());
                worksheet->querySubObject("Cells(int,int)", 2+i, 4)
                        ->dynamicCall("SetValue(const QString&)", query->value(3).toString());
                worksheet->querySubObject("Cells(int,int)", 2+i, 5)
                        ->dynamicCall("SetValue(const QString&)", query->value(4).toString());
                i++;
            }
            workbook->dynamicCall("SaveAs(const QString&)",QDir::toNativeSeparators(filename));
            workbook->dynamicCall("Close()");//关闭工作簿
            excel->dynamicCall("Quit()");//关闭excel
            delete excel;
            excel=NULL;
            return true;
        }
        else{
            qDebug()<<"query exec failed!";
            return false;
        }
    }
    qDebug()<<"excel setControl failed!";
    return false;
}









