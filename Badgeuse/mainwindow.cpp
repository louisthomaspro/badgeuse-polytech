#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QSqlTableModel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    // DATABASE
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/home/louis/Documents/Git/badgeuse-polytech/Badgeuse/badgeuse");
    if (!db.open())
    {
        QMessageBox::critical(nullptr, QObject::tr("Database Error"),
                              db.lastError().text());
    }


    model = new QSqlTableModel(this, db);
    model->setTable("student");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();
    model->setHeaderData(0, Qt::Horizontal, tr("Nom"));
    model->setHeaderData(1, Qt::Horizontal, tr("Prénom"));
    model->setHeaderData(2, Qt::Horizontal, tr("Promotion"));

    ui->tv_students->horizontalHeader()->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->tv_students->horizontalHeader(),
            SIGNAL(customContextMenuRequested(QPoint)),
            this,
            SLOT(customHeaderMenuRequested(QPoint)));


    ui->tv_students->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tv_students->setModel(model);
    //ui->tv_students->setColumnHidden(2, true);
    ui->tv_students->show();

    //connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(refresh()));


    model2 = new QSqlTableModel(this, db);

    model2->setTable("presence");
    model2->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model2->select();
    model2->setHeaderData(0, Qt::Horizontal, tr("Prénom"));
    model2->setHeaderData(1, Qt::Horizontal, tr("Nom"));
    model2->setHeaderData(2, Qt::Horizontal, tr("Date/Heure début"));
    model2->setHeaderData(3, Qt::Horizontal, tr("Date/Heure fin"));
    model2->setHeaderData(4, Qt::Horizontal, tr("Etat"));

    QModelIndex vIndex = model2->index(0,0);
    model2->setData(vIndex, QBrush(Qt::red), Qt::ForegroundRole);



    ui->tv_presence->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tv_presence->setModel(model2);
    ui->tv_presence->show();


}
void MainWindow::customHeaderMenuRequested(QPoint pos){
    int column=ui->tv_students->horizontalHeader()->logicalIndexAt(pos);

    QMenu *menu=new QMenu(this);
    static QAction *saveAction = new QAction("firstname : " + QString::number(ui->tv_students->isColumnHidden(0)), this);
    connect(saveAction, SIGNAL(triggered()), this, SLOT(toggleColumn()));
    menu->addAction(saveAction);
    menu->addAction(new QAction("lastname : " + QString::number(ui->tv_students->isColumnHidden(1)), this));
    menu->addAction(new QAction("promo : " + QString::number(ui->tv_students->isColumnHidden(2)), this));
    menu->popup(ui->tv_students->horizontalHeader()->viewport()->mapToGlobal(pos));
}

void MainWindow::refresh()
{
    model->select();
}
void MainWindow::toggleColumn()
{
    ui->tv_students->setColumnHidden(0, !ui->tv_students->isColumnHidden(0));
}

MainWindow::~MainWindow()
{
    delete ui;
}
