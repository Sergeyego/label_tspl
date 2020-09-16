#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    loadSettings();

    refreshDocType();

    ui->dateEditBeg->setDate(QDate::currentDate().addDays(-QDate::currentDate().dayOfYear()+1));
    ui->dateEditEnd->setDate(QDate(QDate::currentDate().year(),12,31));

    ui->tableViewPart->verticalHeader()->setDefaultSectionSize(ui->tableViewPart->verticalHeader()->fontMetrics().height()*1.5);
    ui->tableViewOdobr->verticalHeader()->setDefaultSectionSize(ui->tableViewOdobr->verticalHeader()->fontMetrics().height()*1.5);

    ui->actionPart->setIcon(this->style()->standardIcon(QStyle::SP_BrowserReload));
    ui->actionSrc->setIcon(QIcon::fromTheme("document-print"));
    ui->actionPack->setIcon(QIcon::fromTheme("document-print"));
    ui->actionExit->setIcon(this->style()->standardIcon(QStyle::SP_DialogCancelButton));

    ui->toolButtonSrc->setDefaultAction(ui->actionSrc);
    ui->toolButtonPack->setDefaultAction(ui->actionPack);
    ui->toolButtonUpd->setDefaultAction(ui->actionPart);

    modelTu = new ModelRo(this);
    ui->listViewGost->setModel(modelTu);

    modelVol = new ModelRo(this);
    modelNam = new ModelRo(this);

    modelOdobr = new ModelRo(this);
    ui->tableViewOdobr->setModel(modelOdobr);

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
    connect(ui->actionSrc,SIGNAL(triggered(bool)),this,SLOT(createSrcLabel()));
    connect(ui->actionPack,SIGNAL(triggered(bool)),this,SLOT(createPackLabel()));
    connect(ui->actionExit,SIGNAL(triggered(bool)),this,SLOT(close()));
    connect(ui->actionPrintCfg,SIGNAL(triggered(bool)),this,SLOT(settings()));

    connect(ui->actionViewSrc,SIGNAL(triggered(bool)),this,SLOT(viewCmdSrc()));
    connect(ui->actionViewPack,SIGNAL(triggered(bool)),this,SLOT(viewCmdPack()));

    updPart();
}

MainWindow::~MainWindow()
{
    saveSettings();
    delete ui;
}

bool MainWindow::printData(const QString &data)
{
    QTcpSocket tcpSocket;
    QTextCodec *codec = QTextCodec::codecForName("Windows-1251");
    tcpSocket.connectToHost(ipAdr,port);
    bool ok=tcpSocket.waitForConnected(1000);
    if (ok) {
        tcpSocket.write(codec->fromUnicode(data));
        tcpSocket.waitForBytesWritten();
        tcpSocket.disconnectFromHost();
    } else {
        QMessageBox::critical(this,QString::fromUtf8("Ошибка"),tcpSocket.errorString(),QMessageBox::Ok);
    }
    return ok;
}

QString MainWindow::getCodSrc()
{
    QString cod;
    cod.push_back("DIRECTION 1,0\n");
    cod.push_back("CLS\n");
    cod.push_back("SIZE 80 mm,101.6 mm\n");
    cod.push_back("GAP 4 mm\n");
    cod.push_back("CODEPAGE 1251\n");
    cod.push_back("DENSITY 15\n");
    cod.push_back("PUTBMP 170,110, \"logo.BMP\",1,100\n");
    cod.push_back(QString::fromUtf8("TEXT 50,350,\"0\",0,12,12,\"Марка - %1\"\n").arg(ui->lineEditMark->text()));
    cod.push_back(QString::fromUtf8("TEXT 50,390,\"0\",0,12,12,\"Диаметр, мм - %1\"\n").arg(QLocale().toString(ui->lineEditDiam->text().toDouble(),'f',1)));
    cod.push_back(QString::fromUtf8("TEXT 50,430,\"0\",0,12,12,\"Плавка - %1\"\n").arg(ui->lineEditPlav->text()));
    cod.push_back(QString::fromUtf8("TEXT 50,470,\"0\",0,12,12,\"Партия - %1\"\n").arg(ui->lineEditPart->text()));
    cod.push_back(QString::fromUtf8("TEXT 50,510,\"0\",0,12,12,\"Носитель - %1\"\n").arg(ui->lineEditSpool->text()));
    cod.push_back(QString::fromUtf8("TEXT 50,550,\"0\",0,12,12,\"№ - %1%2%3\"\n").arg(ui->dateEditPr->date().toString("yyMMdd")).arg(getNum(ui->comboBoxNam)).arg(getNum(ui->comboBoxVol)));
    cod.push_back(QString::fromUtf8("TEXT 50,590,\"0\",0,12,12,\"Масса нетто, кг - %1\"\n").arg(ui->lineEditKvo->text()));
    cod.push_back(QString::fromUtf8("TEXT 50,630,\"0\",0,12,12,\"Дата изг. - %1\"\n").arg(ui->dateEdit->date().toString("dd.MM.yyyy")));
    if (ui->checkBoxEan->isChecked() && !ui->lineEditEanEd->text().isEmpty()){
        cod.push_back(QString("BARCODE 600,350, \"EAN13\",140,2,90,3,3,\"%1\"\n").arg(ui->lineEditEanEd->text().left(12)));
    }
    cod.push_back(QString("PRINT %1\n").arg(ui->spinBox->value()));
    return cod;
}

QString MainWindow::getCodPack()
{
    QString cod;
    cod.push_back("DIRECTION 1,0\n");
    cod.push_back("CLS\n");
    cod.push_back("SIZE 95 mm,110 mm\n");
    cod.push_back("GAP 4 mm\n");
    cod.push_back("CODEPAGE 1251\n");
    cod.push_back("DENSITY 15\n");
    cod.push_back("PUTBMP 50,110, \"logo.BMP\",1,100\n");
    cod.push_back(QString::fromUtf8("TEXT 50,260,\"0\",0,12,12,\"Проволока сварочная\"\n"));
    cod.push_back(QString::fromUtf8("TEXT 350,255,\"0\",0,14,14,\"%1\"\n").arg(ui->lineEditMark->text()));
    cod.push_back(QString::fromUtf8("TEXT 50,300,\"0\",0,12,12,\"%1\"\n").arg(strGost()));
    cod.push_back(QString::fromUtf8("BLOCK 50,340,690,120,\"0\",0,10,10,0,0,1,\"%1\"\n").arg(ui->plainTextEdit->toPlainText()));
    cod.push_back(QString::fromUtf8("TEXT 50,460,\"0\",0,12,12,\"Диаметр, мм - %1\"\n").arg(QLocale().toString(ui->lineEditDiam->text().toDouble(),'f',1)));
    cod.push_back(QString::fromUtf8("TEXT 50,500,\"0\",0,12,12,\"Плавка - %1\"\n").arg(ui->lineEditPlav->text()));
    cod.push_back(QString::fromUtf8("TEXT 50,540,\"0\",0,12,12,\"Партия № %1\"\n").arg(ui->lineEditPart->text()));
    cod.push_back(QString::fromUtf8("TEXT 50,580,\"0\",0,12,12,\"Тип намотки - %1\"\n").arg(ui->lineEditSpool->text()));
    cod.push_back(QString::fromUtf8("TEXT 350,460,\"0\",0,12,12,\"Дата изг. - %1\"\n").arg(ui->dateEdit->date().toString("dd.MM.yyyy")));
    cod.push_back(QString::fromUtf8("TEXT 350,500,\"0\",0,12,12,\"Масса нетто, кг - %1\"\n").arg(ui->lineEditKvo->text()));
    cod.push_back(QString::fromUtf8("TEXT 350,540,\"0\",0,12,12,\"Упаковщик № %1\"\n").arg(ui->lineEditUpk->text()));
    cod.push_back(QString::fromUtf8("BLOCK 50,620,690,200,\"0\",0,10,10,0,0,1,\"%1\"\n").arg(getSert()));
    if (ui->checkBoxEan->isChecked() && !getEanPack().isEmpty()){
        cod.push_back(QString("BARCODE 370,110, \"EAN13\",100,2,0,3,3,\"%1\"\n").arg(getEanPack()));
    }
    cod.push_back(QString("PRINT %1\n").arg(ui->spinBox->value()));
    return cod;
}

QString MainWindow::getNum(QComboBox *c)
{
    int n=0;
    if (c->findText(c->currentText())!=-1 && c->model()->columnCount()>2){
        n=c->model()->data(c->model()->index(c->currentIndex(),2),Qt::EditRole).toInt();
    }
    return QString("%1").arg((n),2,'d',0,QChar('0'));
}

QString MainWindow::strGost()
{
    QString s;
    for (int i=0; i<modelTu->rowCount(); i++){
        if (!s.isEmpty()){
            s+=", ";
        }
        s+=modelTu->data(modelTu->index(i,0),Qt::EditRole).toString();
    }
    return s;
}

QString MainWindow::getSert()
{
    QString srtStr;
    QMultiMap <int, QString> srt;
    for (int i=0; i<modelOdobr->rowCount(); i++){
        int id_doc_t=modelOdobr->data(modelOdobr->index(i,0),Qt::EditRole).toInt();
        QString ved=modelOdobr->data(modelOdobr->index(i,1),Qt::EditRole).toString();
        QString grade=modelOdobr->data(modelOdobr->index(i,2),Qt::EditRole).toString();

        QString s=ved;
        if (!grade.isEmpty()){
            s+=QString::fromUtf8(" категория ")+grade;
        }

        if (srt.contains(id_doc_t, ved) && (ved!=s)){
            srt.remove(id_doc_t,ved);
        }

        QStringList list(srt.values(id_doc_t));

        if (list.indexOf(QRegExp(QString("^"+s+".*")))==-1){
            srt.insert(id_doc_t,s);
        }
    }

    QList<int> keys = srt.uniqueKeys();

    for (int i=0; i<keys.size(); ++i){
        if (!srtStr.isEmpty()){
            srtStr+="\n";
        }
        srtStr+=docType.value(keys.at(i))+":";
        QList<QString> v = srt.values(keys.at(i));
        qSort(v.begin(),v.end());
        for (QString st:v){
            if (!srtStr.isEmpty()){
                srtStr+="\n";
            }
            srtStr+=st;
        }
    }
    return srtStr;
}

QString MainWindow::getEanPack()
{
    QString ean;
    if (!ui->lineEditEanGr->text().isEmpty()){
        ean=ui->lineEditEanGr->text().left(12);
    } else if (!ui->lineEditEanEd->text().isEmpty()){
        ean=ui->lineEditEanEd->text().left(12);
    }
    return ean;
}

void MainWindow::loadSettings()
{
    QSettings settings("szsm", QApplication::applicationName());
    ipAdr=settings.value("ip","192.168.1.118").toString();
    port=settings.value("port",9100).toInt();
}

void MainWindow::saveSettings()
{
    QSettings settings("szsm", QApplication::applicationName());
    settings.setValue("ip",ipAdr);
    settings.setValue("port",port);
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
    int id_part=ui->tableViewPart->model()->data(ui->tableViewPart->model()->index(index.row(),0),Qt::EditRole).toInt();
    QSqlQuery tuQuery;
    tuQuery.prepare("select g.nam from wire_gost as w "
                    "inner join gost_new as g on w.id_gost=g.id "
                    "where w.id_provol=(select m.id_provol from wire_parti as p inner join wire_parti_m as m on p.id_m=m.id where p.id=:id) order by g.nam");
    tuQuery.bindValue(":id",id_part);
    if (modelTu->execQuery(tuQuery)){
        ui->listViewGost->setModelColumn(1);
        modelTu->setHeaderData(1,Qt::Horizontal,QString::fromUtf8("Название"));
    }

    QSqlQuery sertQuery;
    sertQuery.prepare("select i.id_doc_t, i.ved_short, i.grade "
                      "from zvd_get_wire_sert( "
                      "(select dat from wire_parti_m where id= (select p.id_m from wire_parti as p where p.id= :id1 ) ), "
                      "(select id_provol from wire_parti_m where id= (select p.id_m from wire_parti as p where p.id= :id2 ) ), "
                      "(select id_diam from wire_parti_m where id= (select p.id_m from wire_parti as p where p.id= :id3 ) ) "
                      ") as i group by i.id_doc_t, i.ved_short, i.grade order by i.id_doc_t ");
    sertQuery.bindValue(":id1",id_part);
    sertQuery.bindValue(":id2",id_part);
    sertQuery.bindValue(":id3",id_part);
    if (modelOdobr->execQuery(sertQuery)){
        ui->tableViewOdobr->setColumnHidden(0,true);
        ui->tableViewOdobr->resizeColumnsToContents();
        modelOdobr->setHeaderData(1,Qt::Horizontal,QString::fromUtf8("Ведомство"));
        modelOdobr->setHeaderData(2,Qt::Horizontal,QString::fromUtf8("Категория"));
    }
    ui->spinBox->setValue(1);
}

void MainWindow::createSrcLabel()
{
    printData(getCodSrc());
}

void MainWindow::createPackLabel()
{
    printData(getCodPack());
}

void MainWindow::refreshDocType()
{
    docType.clear();
    QSqlQuery query;
    query.prepare("select id, nam from zvd_doc_type order by nam");
    bool ok=query.exec();
    if (ok){
        while(query.next()){
            docType.insert(query.value(0).toInt(),query.value(1).toString());
        }
    } else {
        QMessageBox::critical(this,QString::fromUtf8("Ошибка"),query.lastError().text(),QMessageBox::Ok);
    }
}

void MainWindow::settings()
{
    DialogSettings d(ipAdr,port);
    connect(&d,SIGNAL(cmdPrint(QString)),this,SLOT(printData(QString)));
    if (d.exec()==QDialog::Accepted){
        ipAdr=d.getIp();
        port=d.getPort();
    }
}

void MainWindow::viewCmdSrc()
{
    DialogCmd c(getCodSrc());
    connect(&c,SIGNAL(cmdPrint(QString)),this,SLOT(printData(QString)));
    c.exec();
}

void MainWindow::viewCmdPack()
{
    DialogCmd c(getCodPack());
    connect(&c,SIGNAL(cmdPrint(QString)),this,SLOT(printData(QString)));
    c.exec();
}
