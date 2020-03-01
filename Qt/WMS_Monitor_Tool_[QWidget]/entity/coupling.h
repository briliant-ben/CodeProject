#ifndef COUPLING_H
#define COUPLING_H

#include <QObject>

class coupling
{
public:
    coupling();

    qint32 getid(){
        return id;
    }
    QString getmodel(){
        return model;
    }
    float getdiamter(){
        return diamter;
    }
    float getcdiameter(){
        return cdiameter;
    }
    float getlength(){
        return length;
    }
    float getweigh(){
        return weigh;
    }
    qint32 getnumberperbasket(){
        return numberperbasket;
    }
    float totalweighgetweigh(){
        return totalweigh;
    }

    void setid(qint32 id1){
        this->id = id1;
    }
    void setmodel(QString model1){
        this->model = model1;
    }
    void setdiamter(float diamter1){
        this->diamter = diamter1;
    }
    void setcdiameter(float cdiameter1){
        this->cdiameter = cdiameter1;
    }
    void setlength(float length1){
        this->length = length1;
    }
    void setweigh(float weigh1){
        this->weigh = weigh1;
    }
    void setnumberperbasket1(qint32 numberperbasket1){
        this->numberperbasket = numberperbasket1;
    }
    void settotalweigh(float totalweigh1){
        this->totalweigh = totalweigh1;
    }

private:
    qint32 id;
    QString model;
    float diamter;
    float cdiameter;
    float length;
    float weigh;
    qint32 numberperbasket;
    float totalweigh;
};

#endif // COUPLING_H
