#ifndef STAFF_H
#define STAFF_H

#include <QObject>

class staff
{
public:
    staff();

    static qint32 staticid;
    static QString staticname;
    static qint32 staticrole;

    qint32 getid(){
        return id;
    }
    QString getnumber(){
        return number;
    }
    QString getpassword(){
        return password;
    }
    QString getname(){
        return name;
    }
    QString getunit(){
        return unit;
    }
    QString getposition(){
        return position;
    }
    QString getphone(){
        return phone;
    }
    QString getauthentication(){
        return authentication;
    }
    QString getcreatetime(){
        return createtime;
    }
    QString getupdatetime(){
        return updatetime;
    }
    qint32 getrole(){
        return role;
    }

    void setid(qint32 sid){
        this->id = sid;
    }
    void setnumber(QString snumber){
        this->number = snumber;
    }
    void setpassword(QString spassword){
        this->password = spassword;
    }
    void setname(QString sname){
        this->name = sname;
    }
    void setunit(QString sunit){
        this->unit = sunit;
    }
    void setposition(QString sposition){
        this->position = sposition;
    }
    void setphone(QString sphone){
        this->phone = sphone;
    }
    void setauthentication(QString sauthentication){
        this->authentication = sauthentication;
    }
    void setcreatetime(QString screatetime){
        this->createtime = screatetime;
    }
    void setupdatetime(QString supdatetime){
        this->updatetime = supdatetime;
    }
    void setrole(qint32 srole){
        this->role = srole;
    }

private:
    qint32 id;//need not?
    QString number;
    QString password;
    QString name;
    QString unit;
    QString position;
    QString phone;
    QString authentication;
    QString createtime;//QDate createtime;
    QString updatetime;//QDate updatetime;
    qint32 role;
};

#endif // STAFF_H
