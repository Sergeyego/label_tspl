#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    printerSrc = new TPrinter("src",this);
    printerPack = new TPrinter("pack",this);
    printerPBig = new TPrinter("pbig",this);
    printerPSmall = new TPrinter("psmall",this);

    loadSettings();

    refreshDocType();

    ui->dateEditBeg->setDate(QDate::currentDate().addDays(-QDate::currentDate().dayOfYear()+1));
    ui->dateEditEnd->setDate(QDate(QDate::currentDate().year(),12,31));

    ui->tableViewPart->verticalHeader()->setDefaultSectionSize(ui->tableViewPart->verticalHeader()->fontMetrics().height()*1.5);
    ui->tableViewOdobr->verticalHeader()->setDefaultSectionSize(ui->tableViewOdobr->verticalHeader()->fontMetrics().height()*1.5);

    ui->actionPart->setIcon(this->style()->standardIcon(QStyle::SP_BrowserReload));
    ui->actionSrc->setIcon(QIcon::fromTheme("document-print"));
    ui->actionPack->setIcon(QIcon::fromTheme("document-print"));
    ui->actionPBig->setIcon(QIcon::fromTheme("document-print"));
    ui->actionPSmall->setIcon(QIcon::fromTheme("document-print"));
    ui->actionExit->setIcon(this->style()->standardIcon(QStyle::SP_DialogCancelButton));

    ui->toolButtonSrc->setDefaultAction(ui->actionSrc);
    ui->toolButtonPack->setDefaultAction(ui->actionPack);
    ui->toolButtonUpd->setDefaultAction(ui->actionPart);
    ui->toolButtonPBig->setDefaultAction(ui->actionPBig);
    ui->toolButtonPSmall->setDefaultAction(ui->actionPSmall);

    modelTu = new ModelRo(this);
    ui->listViewGost->setModel(modelTu);

    modelOtk = new ModelRo(this);
    modelNam = new ModelRo(this);

    modelOdobr = new ModelRo(this);
    ui->tableViewOdobr->setModel(modelOdobr);

    ui->comboBoxOtk->setModel(modelOtk);
    ui->comboBoxNam->setModel(modelNam);

    modelPartOrig = new ModelRo(this);
    ui->comboBoxOPart->setModel(modelPartOrig);
    ui->comboBoxOPart->completer()->setCompletionMode(QCompleter::PopupCompletion);
    ui->comboBoxOPart->completer()->setCaseSensitivity(Qt::CaseInsensitive);

    modelPart = new ModelRo(this);
    ui->tableViewPart->setModel(modelPart);

    mapper = new QDataWidgetMapper(this);

    mapper->setModel(modelPart);

    mapper->addMapping(ui->lineEditPart,1);
    mapper->addMapping(ui->lineEditMark,2);
    mapper->addMapping(ui->lineEditDiam,3);
    mapper->addMapping(ui->lineEditSpool,4);
    mapper->addMapping(ui->dateEdit,6);
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
    connect(ui->actionPBig,SIGNAL(triggered(bool)),this,SLOT(createPBigLabel()));
    connect(ui->actionPSmall,SIGNAL(triggered(bool)),this,SLOT(createPSmallLabel()));

    connect(ui->actionSetPrintSrc,SIGNAL(triggered(bool)),this,SLOT(settingsPrintSrc()));
    connect(ui->actionSetPrintPack,SIGNAL(triggered(bool)),this,SLOT(settingsPrintPack()));
    connect(ui->actionSetPrintPBig,SIGNAL(triggered(bool)),this,SLOT(settingsPrintPBig()));
    connect(ui->actionSetPrintPSmall,SIGNAL(triggered(bool)),this,SLOT(settingsPrintPSmall()));

    connect(ui->actionViewSrc,SIGNAL(triggered(bool)),this,SLOT(viewCmdSrc()));
    connect(ui->actionViewPack,SIGNAL(triggered(bool)),this,SLOT(viewCmdPack()));
    connect(ui->actionViewPBig,SIGNAL(triggered(bool)),this,SLOT(viewCmdPBig()));
    connect(ui->actionViewPSmall,SIGNAL(triggered(bool)),this,SLOT(viewCmdPSmall()));

    connect(ui->comboBoxOPart->lineEdit(),SIGNAL(editingFinished()),this,SLOT(setOrigPart()));

    connect(ui->actionExit,SIGNAL(triggered(bool)),this,SLOT(close()));

    updPart();
}

MainWindow::~MainWindow()
{
    saveSettings();
    delete ui;
}


QString MainWindow::getCodSrc(int dpi)
{
    QString cod;
    cod.push_back("DIRECTION 1,0\n");
    cod.push_back("CLS\n");
    cod.push_back("SIZE 80 mm,101.6 mm\n");
    cod.push_back("GAP 4 mm\n");
    cod.push_back("CODEPAGE 1251\n");
    cod.push_back("DENSITY 15\n");
    cod.push_back(QString::fromUtf8("PUTBMP %1,%2, \"logo.BMP\",1,100\n").arg(getDots(15,dpi)).arg(getDots(13.75,dpi)));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,12,12,\"Марка - %3\"\n").arg(getDots(6.25,dpi)).arg(getDots(43.75,dpi)).arg(ui->lineEditMark->text()));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,12,12,\"Диаметр, мм - %3\"\n").arg(getDots(6.25,dpi)).arg(getDots(48.75,dpi)).arg(QLocale().toString(ui->lineEditDiam->text().toDouble(),'f',1)));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,12,12,\"Плавка - %3\"\n").arg(getDots(6.25,dpi)).arg(getDots(53.75,dpi)).arg(ui->lineEditPlav->text()));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,12,12,\"Партия - %3\"\n").arg(getDots(6.25,dpi)).arg(getDots(58.75,dpi)).arg(ui->lineEditPart->text()));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,12,12,\"Тип носителя - %3\"\n").arg(getDots(6.25,dpi)).arg(getDots(63.75,dpi)).arg(ui->lineEditSpool->text()));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,12,12,\"Код продукции - %3\"\n").arg(getDots(6.25,dpi)).arg(getDots(68.75,dpi)).arg(getCod()));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,12,12,\"Масса нетто, кг - %3\"\n").arg(getDots(6.25,dpi)).arg(getDots(73.75,dpi)).arg(ui->lineEditKvo->text()));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,12,12,\"Дата изг. - %3\"\n").arg(getDots(6.25,dpi)).arg(getDots(78.75,dpi)).arg(ui->dateEdit->date().toString("dd.MM.yyyy")));
    if (ui->checkBoxEan->isChecked() && !ui->lineEditEanEd->text().isEmpty()){
        cod.push_back(QString("BARCODE %1,%2,\"EAN13\",%3,2,90,%4,%5,\"%6\"\n").arg(getDots(75,dpi)).arg(getDots(43.75,dpi)).arg(getDots(17.5,dpi)).arg(getDots(0.375,dpi)).arg(getDots(0.375,dpi)).arg(ui->lineEditEanEd->text().left(12)));
    }
    cod.push_back(getOtkStamp(55,20,dpi));
    cod.push_back(QString("PRINT %1\n").arg(ui->spinBox->value()));
    return cod;
}

QString MainWindow::getCodPack(int dpi)
{
    QString cod;
    cod.push_back("DIRECTION 1,0\n");
    cod.push_back("CLS\n");
    cod.push_back("SIZE 95 mm,110 mm\n");
    cod.push_back("GAP 4 mm\n");
    cod.push_back("CODEPAGE 1251\n");
    cod.push_back("DENSITY 15\n");
    cod.push_back(QString("PUTBMP %1,%2,\"logo.BMP\",1,100\n").arg(getDots(6.25,dpi)).arg(getDots(13.75,dpi)));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,12,12,\"Проволока сварочная\"\n").arg(getDots(6.25,dpi)).arg(getDots(32.5,dpi)));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,14,14,\"%3\"\n").arg(getDots(45,dpi)).arg(getDots(31.875,dpi)).arg(ui->lineEditMark->text()));
    //cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,12,12,\"%3\"\n").arg(getDots(6.25,dpi)).arg(getDots(37.5,dpi)).arg(strGost()));
    cod.push_back(QString::fromUtf8("BLOCK %1,%2,%3,%4,\"0\",0,12,12,0,0,1,\"%5\"\n").arg(getDots(6.25,dpi)).arg(getDots(37.5,dpi)).arg(getDots(86.25,dpi)).arg(getDots(10,dpi)).arg(strGost()));
    cod.push_back(QString::fromUtf8("BLOCK %1,%2,%3,%4,\"0\",0,10,10,0,0,1,\"%5\"\n").arg(getDots(6.25,dpi)).arg(getDots(47.5,dpi)).arg(getDots(86.25,dpi)).arg(getDots(15,dpi)).arg(ui->plainTextEdit->toPlainText()));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,12,12,\"Диаметр, мм - %3\"\n").arg(getDots(6.25,dpi)).arg(getDots(62.5,dpi)).arg(QLocale().toString(ui->lineEditDiam->text().toDouble(),'f',1)));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,12,12,\"Плавка - %3\"\n").arg(getDots(6.25,dpi)).arg(getDots(67.5,dpi)).arg(ui->lineEditPlav->text()));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,12,12,\"Партия № %3\"\n").arg(getDots(6.25,dpi)).arg(getDots(72.5,dpi)).arg(ui->lineEditPart->text()));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,12,12,\"Тип носителя - %3\"\n").arg(getDots(6.25,dpi)).arg(getDots(77.5,dpi)).arg(ui->lineEditSpool->text()));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,12,12,\"Дата изг. - %3\"\n").arg(getDots(45,dpi)).arg(getDots(62.5,dpi)).arg(ui->dateEdit->date().toString("dd.MM.yyyy")));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,12,12,\"Масса нетто, кг - %3\"\n").arg(getDots(45,dpi)).arg(getDots(67.5,dpi)).arg(ui->lineEditKvo->text()));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,12,12,\"Упаковщик № %3\"\n").arg(getDots(45,dpi)).arg(getDots(72.5,dpi)).arg(ui->lineEditUpk->text()));
    cod.push_back(QString::fromUtf8("BLOCK %1,%2,%3,%4,\"0\",0,10,10,0,0,1,\"%5\"\n").arg(getDots(6.25,dpi)).arg(getDots(82.5,dpi)).arg(getDots(86.25,dpi)).arg(getDots(25,dpi)).arg(getSert()));
    if (ui->checkBoxEan->isChecked() && !getEanPack().isEmpty()){
        cod.push_back(QString("BARCODE %1,%2,\"EAN13\",%3,2,0,%4,%5,\"%6\"\n").arg(getDots(46.25,dpi)).arg(getDots(13.75,dpi)).arg(getDots(12.5,dpi)).arg(getDots(0.375,dpi)).arg(getDots(0.375,dpi)).arg(getEanPack()));
    }
    cod.push_back(getOtkStamp(60,75,dpi));
    cod.push_back(QString("PRINT %1\n").arg(ui->spinBox->value()));
    return cod;
}

QString MainWindow::getCodPBig(int dpi)
{
    QString cod;
    cod.push_back("DIRECTION 1,0\n");
    cod.push_back("CLS\n");
    cod.push_back("SIZE 100 mm,100 mm\n");
    cod.push_back("GAP 2.8 mm\n");
    cod.push_back("CODEPAGE 1251\n");
    cod.push_back("DENSITY 15\n");
    cod.push_back(QString("PUTBMP %1,%2,\"logo.BMP\",1,100\n").arg(getDots(6.25,dpi)).arg(getDots(6.25,dpi)));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,12,12,\"Проволока сварочная\"\n").arg(getDots(6.25,dpi)).arg(getDots(25,dpi)));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,14,14,\"%3\"\n").arg(getDots(45,dpi)).arg(getDots(24.375,dpi)).arg(ui->lineEditMark->text()));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,12,12,\"%3\"\n").arg(getDots(6.25,dpi)).arg(getDots(30,dpi)).arg(strGost()));
    cod.push_back(QString::fromUtf8("BLOCK %1,%2,%3,%4,\"0\",0,10,10,0,0,1,\"%5\"\n").arg(getDots(6.25,dpi)).arg(getDots(35,dpi)).arg(getDots(86.25,dpi)).arg(getDots(15,dpi)).arg(ui->plainTextEdit->toPlainText()));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,12,12,\"Диаметр, мм - %3\"\n").arg(getDots(6.25,dpi)).arg(getDots(50,dpi)).arg(QLocale().toString(ui->lineEditDiam->text().toDouble(),'f',1)));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,12,12,\"Плавка - %3\"\n").arg(getDots(6.25,dpi)).arg(getDots(55,dpi)).arg(ui->lineEditPlav->text()));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,12,12,\"Партия № %3\"\n").arg(getDots(6.25,dpi)).arg(getDots(60,dpi)).arg(ui->lineEditPart->text()));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,12,12,\"Тип носителя - %3\"\n").arg(getDots(6.25,dpi)).arg(getDots(65,dpi)).arg(ui->lineEditSpool->text()));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,12,12,\"Дата изг. - %3\"\n").arg(getDots(45,dpi)).arg(getDots(50,dpi)).arg(ui->dateEdit->date().toString("dd.MM.yyyy")));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,12,12,\"Масса нетто, кг - %3\"\n").arg(getDots(45,dpi)).arg(getDots(55,dpi)).arg(ui->lineEditKvo->text()));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,12,12,\"Упаковщик № %3\"\n").arg(getDots(45,dpi)).arg(getDots(60,dpi)).arg(ui->lineEditUpk->text()));
    cod.push_back(QString::fromUtf8("BLOCK %1,%2,%3,%4,\"0\",0,10,10,0,0,1,\"%5\"\n").arg(getDots(6.25,dpi)).arg(getDots(70,dpi)).arg(getDots(86.25,dpi)).arg(getDots(25,dpi)).arg(getSert()));
    if (ui->checkBoxEan->isChecked() && !getEanPack().isEmpty()){
        cod.push_back(QString("BARCODE %1,%2,\"EAN13\",%3,2,0,%4,%5,\"%6\"\n").arg(getDots(46.25,dpi)).arg(getDots(6.25,dpi)).arg(getDots(12.5,dpi)).arg(getDots(0.375,dpi)).arg(getDots(0.375,dpi)).arg(getEanPack()));
    }
    cod.push_back(getOtkStamp(60,75,dpi));
    cod.push_back(QString("PRINT %1\n").arg(ui->spinBox->value()));
    return cod;
}

QString MainWindow::getCodPSmall(int dpi)
{
    QString cod;
    cod.push_back("DIRECTION 1,0\n");
    cod.push_back("CLS\n");
    cod.push_back("SIZE 45 mm,70 mm\n");
    cod.push_back("GAP 2 mm\n");
    cod.push_back("CODEPAGE 1251\n");
    cod.push_back("DENSITY 15\n");
    cod.push_back(QString::fromUtf8("PUTBMP %1,%2, \"logo.BMP\",1,100\n").arg(getDots(2,dpi)).arg(getDots(2,dpi)));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,10,10,\"Марка - %3\"\n").arg(getDots(5,dpi)).arg(getDots(35,dpi)).arg(ui->lineEditMark->text()));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,10,10,\"Диаметр, мм - %3\"\n").arg(getDots(5,dpi)).arg(getDots(39,dpi)).arg(QLocale().toString(ui->lineEditDiam->text().toDouble(),'f',1)));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,10,10,\"Плавка - %3\"\n").arg(getDots(5,dpi)).arg(getDots(43,dpi)).arg(ui->lineEditPlav->text()));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,10,10,\"Партия - %3\"\n").arg(getDots(5,dpi)).arg(getDots(47,dpi)).arg(ui->lineEditPart->text()));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,10,10,\"Тип носителя - %3\"\n").arg(getDots(5,dpi)).arg(getDots(51,dpi)).arg(ui->lineEditSpool->text()));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,10,10,\"Код продукции - %3\"\n").arg(getDots(5,dpi)).arg(getDots(55,dpi)).arg(getCod()));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,10,10,\"Масса нетто, кг - %3\"\n").arg(getDots(5,dpi)).arg(getDots(59,dpi)).arg(ui->lineEditKvo->text()));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,10,10,\"Дата изг. - %3\"\n").arg(getDots(5,dpi)).arg(getDots(63,dpi)).arg(ui->dateEdit->date().toString("dd.MM.yyyy")));
    if (ui->checkBoxEan->isChecked() && !ui->lineEditEanEd->text().isEmpty()){
        cod.push_back(QString("BARCODE %1,%2,\"EAN13\",%3,2,0,%4,%5,\"%6\"\n").arg(getDots(5,dpi)).arg(getDots(20.5,dpi)).arg(getDots(9,dpi)).arg(getDots(0.375,dpi)).arg(getDots(0.375,dpi)).arg(ui->lineEditEanEd->text().left(12)));
    }
    cod.push_back(getOtkStamp(31,40,dpi));
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
    this->restoreGeometry(settings.value("main_geometry").toByteArray());
}

void MainWindow::saveSettings()
{
    QSettings settings("szsm", QApplication::applicationName());
    settings.setValue("main_geometry", this->saveGeometry());
}

QString MainWindow::getCod()
{
    int n=ui->comboBoxOPart->currentIndex();
    QString npart=ui->comboBoxOPart->model()->data(ui->comboBoxOPart->model()->index(n,2),Qt::EditRole).toString();
    QString year=ui->comboBoxOPart->model()->data(ui->comboBoxOPart->model()->index(n,3),Qt::EditRole).toDate().toString("yy");
    year=year.rightJustified(2,QChar('0'));
    npart=npart.rightJustified(4,QChar('0'));
    return year+npart+getNum(ui->comboBoxNam);
}

int MainWindow::getDots(double mm, int dpi)
{
    return dpi*mm/25;
}

QString MainWindow::getOtkStamp(double x, double y, int dpi)
{
    QString cod;
    if (ui->comboBoxOtk->currentIndex()!=-1){
        cod.push_back(QString("CIRCLE %1,%2,%3,%4\n").arg(getDots(x,dpi)).arg(getDots(y,dpi)).arg(getDots(11,dpi)).arg(getDots(0.5,dpi)));
        cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,12,12,\"ОТК\"\n").arg(getDots(x+2.0,dpi)).arg(getDots(y+2.0,dpi)));
        cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,12,12,\"%3\"\n").arg(getDots(x+3.5,dpi)).arg(getDots(y+6.0,dpi)).arg(getNum(ui->comboBoxOtk)));
    }
    return cod;
}

void MainWindow::updPart()
{
    QSqlQuery queryOtk;
    queryOtk.prepare("select o.id, o.nam ||' ('||o.num||')', o.num from otk as o where o.num<>0 order by o.nam");
    if (modelOtk->execQuery(queryOtk)){
        ui->comboBoxOtk->setModelColumn(1);
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

    QSqlQuery queryOPart;
    queryOPart.prepare("select p.id, m.n_s ||'-'||date_part('year',m.dat) ||' '||pr.nam ||' '|| d.sdim || ' '|| k.short  as part, m.n_s, m.dat "
                       "from wire_parti as p "
                       "inner join wire_parti_m as m on p.id_m=m.id "
                       "inner join provol as pr on pr.id=m.id_provol "
                       "inner join diam as d on d.id=m.id_diam "
                       "inner join wire_pack_kind as k on k.id=p.id_pack "
                       "where m.dat>= :dat "
                       "order by part desc");
    queryOPart.bindValue(":dat",QDate::currentDate().addYears(-2));
    if (modelPartOrig->execQuery(queryOPart)){
        ui->comboBoxOPart->setModelColumn(1);
    }

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
}

void MainWindow::setOrigPart()
{
    ui->comboBoxOPart->setCurrentIndex(ui->comboBoxOPart->findText(ui->comboBoxOPart->currentText()));
}

void MainWindow::refreshData(QModelIndex index)
{
    int id_part=ui->tableViewPart->model()->data(ui->tableViewPart->model()->index(index.row(),0),Qt::EditRole).toInt();
    QSqlQuery tuQuery;
    tuQuery.prepare("select g.nam from wire_parti_gost as w "
                    "inner join gost_new as g on w.id_gost=g.id "
                    "where w.id_parti = (select p.id_m from wire_parti as p where p.id = :id) order by g.nam");
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

    for (int i=0; i<ui->comboBoxOPart->model()->rowCount(); i++){
        QModelIndex ind=ui->comboBoxOPart->model()->index(i,0);
        if (ui->comboBoxOPart->model()->data(ind,Qt::EditRole).toInt()==id_part){
            ui->comboBoxOPart->setCurrentIndex(i);
            break;
        }
    }

    ui->spinBox->setValue(1);
}

void MainWindow::createSrcLabel()
{
    QString c=getCodSrc(printerSrc->getDpi());
    printerSrc->printDecode(c);
}

void MainWindow::createPackLabel()
{
    QString c=getCodPack(printerPack->getDpi());
    printerPack->printDecode(c);
}

void MainWindow::createPBigLabel()
{
    QString c=getCodPBig(printerPBig->getDpi());
    printerPBig->printDecode(c);
}

void MainWindow::createPSmallLabel()
{
    QString c=getCodPSmall(printerPSmall->getDpi());
    printerPSmall->printDecode(c);
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

void MainWindow::settingsPrintSrc()
{
    DialogSettings d(printerSrc);
    d.setWindowTitle(d.windowTitle()+": "+ui->actionSetPrintSrc->text());
    d.setLblSize(101.6,80,4);
    d.exec();
}

void MainWindow::settingsPrintPack()
{
    DialogSettings d(printerPack);
    d.setWindowTitle(d.windowTitle()+": "+ui->actionSetPrintPack->text());
    d.setLblSize(110,95,4);
    d.exec();
}

void MainWindow::settingsPrintPBig()
{
    DialogSettings d(printerPBig);
    d.setWindowTitle(d.windowTitle()+": "+ui->actionSetPrintPBig->text());
    d.setLblSize(100,100,2.8);
    d.exec();
}

void MainWindow::settingsPrintPSmall()
{
    DialogSettings d(printerPSmall);
    d.setWindowTitle(d.windowTitle()+": "+ui->actionSetPrintPSmall->text());
    d.setLblSize(70,45,2);
    d.exec();
}

void MainWindow::viewCmdSrc()
{
    DialogCmd c(getCodSrc(printerSrc->getDpi()),printerSrc);
    c.exec();
}

void MainWindow::viewCmdPack()
{
    DialogCmd c(getCodPack(printerPack->getDpi()),printerPack);
    c.exec();
}

void MainWindow::viewCmdPBig()
{
    DialogCmd c(getCodPBig(printerPBig->getDpi()),printerPBig);
    c.exec();
}

void MainWindow::viewCmdPSmall()
{
    DialogCmd c(getCodPSmall(printerPSmall->getDpi()),printerPSmall);
    c.exec();
}
