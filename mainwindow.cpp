#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    loadSettings();
    ui->actionPart->setIcon(this->style()->standardIcon(QStyle::SP_BrowserReload));

    data = new FormData(this);
    ui->verticalLayoutData->addWidget(data);

    labelE801016 = new LabelE801016(QString::fromUtf8("Этикетка 80*101.6 (пластик)"),80,101.6,4,data,this);
    createActions(labelE801016);

    labelG95110 = new LabelG95110(QString::fromUtf8("Этикетка 95*110 (пластик)"),95,110,4,data,this);
    createActions(labelG95110);

    labelE4570 = new LabelE4570(QString::fromUtf8("Этикетка 45*70"),45,70,2,data,this);
    createActions(labelE4570);

    labelG100100 = new LabelG100100(QString::fromUtf8("Этикетка 100*100"),100,100,2.8,data,this);
    createActions(labelG100100);

    labelG100100Pal = new LabelG100100Pal(QString::fromUtf8("Этикетка 100*100 поддон"),100,100,2.8,data,this);
    createActions(labelG100100Pal);

    connect(ui->actionPart,SIGNAL(triggered(bool)),data,SLOT(updPart()));
    connect(ui->actionExit,SIGNAL(triggered(bool)),this,SLOT(close()));

}

MainWindow::~MainWindow()
{
    saveSettings();
    delete ui;
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

void MainWindow::createActions(LabelBase *l)
{
    QAction *printAction=ui->menuFile->addAction(QIcon::fromTheme("document-print"), l->getName());
    QAction *viewAction=ui->menuView->addAction(QString::fromUtf8("Команды ")+l->getName());
    QAction *cfgAction=ui->menuCfg->addAction(QString::fromUtf8("Принтер для ")+l->getName());
    l->setActions(cfgAction,viewAction,printAction);
    QToolButton *b = new QToolButton(this);
    b->setDefaultAction(printAction);
    b->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    ui->horizontalLayoutToolButton->addWidget(b);
}
