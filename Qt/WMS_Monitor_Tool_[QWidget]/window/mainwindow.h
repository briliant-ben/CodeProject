#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QpropertyAnimation>
#include <QMessageBox>
#include <QTreeWidgetItem>
#include <QCloseEvent>
#include "dao/stafflogdao.h"
#include "tabpersonnelwindow.h"
#include "tabstafflogwindow.h"
#include "tabstoragestockwindow.h"
#include "tabstoragestreamwindow.h"
#include "tabstoragelogwindow.h"
#include "tabmonitoragvwindow.h"
#include "systemconfigurewindow.h"
#include "tabstatisticone.h"
#include "tabreportformwindow.h"
#include "feedbackwindow.h"
#include "tabdispatchwindow.h"

#include <QtWebEngineWidgets/QWebEngineView>


namespace Ui {
class mainwindow;
}

class mainwindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit mainwindow(QWidget *parent = 0);

    ~mainwindow();

    void setitemexpand(QString name);

signals:
    void judgeprivilege();

    void judgeprivilegewhich(qint32);

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void timeoutdo();

    void receiveData(qint32,QString,qint32);

    void removeSubTab(qint32 index);

    void on_main_storageaction_triggered();

    void on_main_dispatchaction_triggered();

    void on_main_monitoraction_triggered();

    void on_main_personnelaction_triggered();

    void on_main_journalaction_triggered();

    void on_main_statisticaction_triggered();

    void on_main_reportaction_triggered();

    void on_main_exitaction_triggered();

    void on_main_inforaction_triggered();

    void on_treeWidget_itemClicked(QTreeWidgetItem *, int);

    void on_main_quitaction_triggered();

    void on_main_baiduaction_triggered();

    void on_main_referenceaction_triggered();

    void on_main_setupaction_triggered();

    void on_main_toolbar1action_triggered(bool);

    void on_main_toobar2action_triggered(bool);

    void on_mian_toolbar3action_triggered(bool);

    void on_main_optionaction_triggered(bool);

    void on_main_messageaction_triggered(bool);

    void on_main_adminaction_triggered();

    void on_main_systemaction_triggered();

    void on_main_aboutaction_triggered();

    void on_tabadmin_refreshbutton_clicked();

    void on_tabadmin_linkbutton1_clicked();

    void on_main_fullscreenaction_triggered(bool checked);

    void on_mian_feedbackaction_triggered();

private:
    Ui::mainwindow *ui;
    QTimer *timer;
    QMessageBox msgBox;
    QPropertyAnimation *animation;
    QList<QTreeWidgetItem*> itemlist;
    stafflogdao *newstafflogdao;
    tabpersonnelwindow *newtabper;
    tabstafflogwindow *newtabstalog;
    tabstoragestockwindow *newtabstock;
    tabstoragestreamwindow *newtabstream;
    tabstoragelogwindow *newtabstolog;
    tabmonitoragvwindow *newtabmonagv;
    systemconfigurewindow newconfigure;
    tabstatisticone *newstatisticone;
    tabreportformwindow *newreportform;
    feedbackwindow fbwindow;
    tabdispatchwindow *newtabdispatch;
    QWebEngineView *view;
};

#endif // MAINWINDOW_H
