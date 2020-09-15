#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->dateEditBeg->setDate(QDate::currentDate().addDays(-QDate::currentDate().dayOfYear()+1));
    ui->dateEditEnd->setDate(QDate(QDate::currentDate().year(),12,31));

    ui->actionPart->setIcon(this->style()->standardIcon(QStyle::SP_BrowserReload));

    ui->toolButtonUpd->setDefaultAction(ui->actionPart);

    modelTu = new ModelRo(this);
    ui->listViewGost->setModel(modelTu);

    modelVol = new ModelRo(this);
    modelNam = new ModelRo(this);

    ui->comboBoxVol->setModel(modelVol);
    ui->comboBoxNam->setModel(modelNam);

    modelPart = new ModelRo(this);
    ui->tableViewPart->setModel(modelPart);

    mapper = new QDataWidgetMapper(this);

    mapper->setModel(modelPart);

    mapper->addMapping(ui->lineEditPart,1);
    mapper->addMapping(ui->lineEditMark,2);
    mapper->addMapping(ui->lineEditDiam,3);
    mapper->addMapping(ui->lineEditSpool,4);
    mapper->addMapping(ui->dateEdit,6);
    mapper->addMapping(ui->dateEditPr,6);
    mapper->addMapping(ui->lineEditPlav,7);
    mapper->addMapping(ui->lineEditKvo,8);
    mapper->addMapping(ui->plainTextEdit,9);
    mapper->addMapping(ui->lineEditEanEd,10);
    mapper->addMapping(ui->lineEditEanGr,11);

    connect(ui->tableViewPart->selectionModel(),SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),mapper,SLOT(setCurrentModelIndex(QModelIndex)));
    connect(ui->tableViewPart->selectionModel(),SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),this,SLOT(refreshData(QModelIndex)));
    connect(ui->actionPart,SIGNAL(triggered(bool)),this,SLOT(updPart()));

    updPart();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updPart()
{
    QSqlQuery query;
    query.prepare("select p.id, m.n_s, w.nam, d.diam, k.short, i.nam, m.dat, b.n_plav, wp.mas_ed, w.description, we.ean_ed, we.ean_group "
                  "from wire_parti as p "
                  "inner join wire_parti_m as m on p.id_m=m.id "
                  "inner join provol as w on m.id_provol=w.id "
                  "inner join diam as d on m.id_diam=d.id "
                  "inner join wire_pack_kind as k on p.id_pack=k.id "
                  "inner join wire_source as i on m.id_source=i.id "
                  "inner join prov_buht as b on m.id_buht=b.id "
                  "inner join wire_pack as wp on wp.id = p.id_pack_type "
                  "left join wire_ean as we on we.id_prov=m.id_provol and we.id_diam=m.id_diam and we.id_spool=p.id_pack and we.id_pack=p.id_pack_type "
                  "where m.dat between :d1 and :d2 "
                  "order by m.dat, m.n_s");
    query.bindValue(":d1",ui->dateEditBeg->date());
    query.bindValue(":d2",ui->dateEditEnd->date());
    if (modelPart->execQuery(query)){
        ui->tableViewPart->setColumnHidden(0,true);
        ui->tableViewPart->resizeColumnsToContents();
        modelPart->setHeaderData(1,Qt::Horizontal,QString::fromUtf8("Парт."));
        modelPart->setHeaderData(2,Qt::Horizontal,QString::fromUtf8("Марка"));
        modelPart->setHeaderData(3,Qt::Horizontal,QString::fromUtf8("Диам."));
        modelPart->setHeaderData(4,Qt::Horizontal,QString::fromUtf8("Носитель"));
        modelPart->setHeaderData(5,Qt::Horizontal,QString::fromUtf8("Источник"));
        modelPart->setHeaderData(6,Qt::Horizontal,QString::fromUtf8("Дата"));
        for (int i=7; i<modelPart->columnCount(); i++){
            ui->tableViewPart->setColumnHidden(i,true);
        }
        if (modelPart->rowCount()){
            ui->tableViewPart->selectRow(modelPart->rowCount()-1);
        }
    }

    QSqlQuery queryVol;
    queryVol.prepare("select r.id, r.first_name||' '||substr(r.last_name,1,1)||'. '||substr(r.middle_name,1,1)||'. '||'('||n.num||')' as rab, n.num "
                     "from wire_namoch as n "
                     "inner join wire_empl as r on n.id_rab = r.id "
                     "where r.id <> 0 and n.id_pr = 2 "
                     "order by rab");
    if (modelVol->execQuery(queryVol)){
        ui->comboBoxVol->setModelColumn(1);
    }

    QSqlQuery queryNam;
    queryNam.prepare("select r.id, r.first_name||' '||substr(r.last_name,1,1)||'. '||substr(r.middle_name,1,1)||'. '||'('||n.num||')' as rab, n.num "
                     "from wire_namoch as n "
                     "inner join wire_empl as r on n.id_rab = r.id "
                     "where r.id <> 0 and n.id_pr = 3 "
                     "order by rab");
    if (modelNam->execQuery(queryNam)){
        ui->comboBoxNam->setModelColumn(1);
    }
}

void MainWindow::refreshData(QModelIndex index)
{
    int id_part=ui->tableViewPart->model()->data(ui->tableViewPart->model()->index(index.row(),1),Qt::EditRole).toInt();
    QSqlQuery tuQuery;
    tuQuery.prepare("select g.nam from wire_gost as w "
                    "inner join gost_new as g on w.id_gost=g.id "
                    "where w.id_provol=(select m.id_provol from wire_parti as p inner join wire_parti_m as m on p.id_m=m.id where p.id=:id) order by g.nam");
    tuQuery.bindValue(":id",id_part);
    if (modelTu->execQuery(tuQuery)){
        ui->listViewGost->setModelColumn(1);
        modelTu->setHeaderData(1,Qt::Horizontal,QString::fromUtf8("название"));
    }

}
