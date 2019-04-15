#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QSqlTableModel>
#include <QSortFilterProxyModel>
#include <QProgressDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _badgeuseModel = new BadgeuseModel(this);


    ui->tv_presences->setModel(_badgeuseModel->getPresencesModel());
    ui->tv_students->setModel(_badgeuseModel->getStudentsModel());


//    ui->statusBar->showMessage(tr("Connexion à la base de données..."));


//    model = new presencesModel(this, _db);
//    QSqlQuery *query = new QSqlQuery("SELECT s.firstname, s.lastname, s.student_number, s.mail_adress, s.rfid_number from student s inner join promotion p on s.promotion_id = p.id");
//    model->setQuery(*query);

//    for (int i = 0; i < static_cast<int>(sizeof(absencesHeaderTitles) / sizeof (absencesHeaderTitles[0])); i++) {
//        model->setHeaderData(i, Qt::Horizontal, tr(absencesHeaderTitles[i].name.c_str()));
//        ui->tv_students->setModel(model);
//        ui->tv_students->setColumnHidden(i, !absencesHeaderTitles[i].show);
//    }

//    sort_filter = new QSortFilterProxyModel(this);
//    sort_filter->setSourceModel(model);
//    sort_filter->sort(0);
//    ui->tv_students->setModel(sort_filter);


//    nmFilter = new QSortFilterProxyModel(model);
//    nmFilter->setSourceModel(model);
//    nmFilter->setFilterKeyColumn(0);

//    fnFilter = new QSortFilterProxyModel(model);
//    fnFilter->setSourceModel(nmFilter);
//    fnFilter->setFilterKeyColumn(1);

//    ui->tv_students->setModel(fnFilter);

//    connect(ui->lineEdit_4, &QLineEdit::textChanged,
//            this, &MainWindow::textFilterNameChanged);
//    connect(ui->lineEdit_5, &QLineEdit::textChanged,
//            this, &MainWindow::textFilterFamilyNameChanged);


//    ui->tv_students->verticalHeader()->hide();
//    ui->tv_students->setSelectionBehavior(QAbstractItemView::SelectRows);

//    ui->tv_students->horizontalHeader()->setContextMenuPolicy(Qt::CustomContextMenu);
//    ui->tv_students->setEditTriggers(QAbstractItemView::NoEditTriggers);

//    ui->tv_students->show();

//    connect(ui->tv_students->horizontalHeader(), SIGNAL(customContextMenuRequested(QPoint)), this,
//            SLOT(customHeaderMenuRequested(QPoint)));


    //connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(refresh()));



}

void MainWindow::textFilterNameChanged()
{
    QRegExp regExp(ui->lineEdit_4->text());
    nmFilter->setFilterRegExp(regExp);
}

void MainWindow::textFilterFamilyNameChanged()
{
    QRegExp regExp(ui->lineEdit_5->text());
    fnFilter->setFilterRegExp(regExp);
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
