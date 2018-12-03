#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QSqlTableModel>
#include <QSortFilterProxyModel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    // DATABASE
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("luigi21.heliohost.org");
    db.setDatabaseName("luigi21_db");
    db.setUserName("luigi21_db");
    db.setPassword("polytech");
    db.setPort(3306);

    if (!db.open())
    {
        QMessageBox::critical(nullptr, QObject::tr("Database Error"), db.lastError().text());
    }



    model = new QSqlTableModel(this, db);
    QSqlQuery *query = new QSqlQuery("SELECT s.name, s.family_name, p.name, s.student_number, s.mail_adress, s.rfid_number from student s inner join promotion p on s.promotion_id = p.id");
    model->setQuery(*query);

    for (int i = 0; i < static_cast<int>(sizeof(absencesHeaderTitles) / sizeof (absencesHeaderTitles[0])); i++) {
        model->setHeaderData(i, Qt::Horizontal, tr(absencesHeaderTitles[i].name.c_str()));
        ui->tv_students->setModel(model);
        ui->tv_students->setColumnHidden(i, !absencesHeaderTitles[i].show);
    }

    QSortFilterProxyModel *sort_filter = new QSortFilterProxyModel(this);
    sort_filter->setSourceModel(model);
    sort_filter->sort (0);
    ui->tv_students->setModel (sort_filter);

    ui->tv_students->setSortingEnabled(true);
    ui->tv_students->verticalHeader()->hide();
    ui->tv_students->setSelectionBehavior(QAbstractItemView::SelectRows);
//    QMessageBox msgBox;
//    msgBox.setText(QString::number(static_cast<int>(sizeof(absencesHeaderTitles) / sizeof (absencesHeaderTitles[0]))));
//    msgBox.exec();

    ui->tv_students->horizontalHeader()->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->tv_students->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->tv_students->show();

    connect(ui->tv_students->horizontalHeader(), SIGNAL(customContextMenuRequested(QPoint)), this,
            SLOT(customHeaderMenuRequested(QPoint)));



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
//    QModelIndex index = ui->tv_students->indexAt(pos);

    QMenu *menu=new QMenu(this);

    for (int i = 0; i < static_cast<int>(sizeof(absencesHeaderTitles) / sizeof (absencesHeaderTitles[0])); i++) {
        QAction* fooAction = new QAction(absencesHeaderTitles[i].name.c_str(), this);
        fooAction->setData(i);
        fooAction->setCheckable(true);
        fooAction->setChecked(absencesHeaderTitles[i].show);
//        connect(fooAction, SIGNAL(triggered()), this, SLOT(toggleColumn()));
        connect(fooAction, &QAction::triggered, [this, fooAction](){
                toggleColumn(fooAction->data());
            });
        menu->addAction(fooAction);
    }

    menu->popup(ui->tv_students->horizontalHeader()->viewport()->mapToGlobal(pos));
}

void MainWindow::refresh()
{
    //model->select();
}
void MainWindow::toggleColumn(QVariant v)
{
    bool exec = true;
    bool newValue = ui->tv_students->isColumnHidden(v.toInt());

    int cpt_show = 0;
    if (!newValue) { // si on cache un élement
        for (Col& s: absencesHeaderTitles){ // on compte le nombre d'élement affiché
            if (s.show) cpt_show++;
        }
        if (cpt_show < 2) exec = false; // si il reste 1 element, on ne le cache pas
    }

    if (exec) {
        absencesHeaderTitles[v.toInt()].show = newValue;
        ui->tv_students->setColumnHidden(v.toInt(), !newValue);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
