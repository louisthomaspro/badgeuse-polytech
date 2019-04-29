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

    _dbSettings = new QSettings("dbsettings.ini", QSettings::NativeFormat);

    ui->le_host->setText(_dbSettings->value("db_host", "").toString());
    ui->sb_port->setValue(_dbSettings->value("db_port", "").toInt());
    ui->le_dbname->setText(_dbSettings->value("db_dbname", "").toString());
    ui->le_user->setText(_dbSettings->value("db_user", "").toString());
    ui->le_password->setText(_dbSettings->value("db_password", "").toString());


    _badgeuseModel = new BadgeuseModel(*_dbSettings, this);
    _presenceFilterProxyModel = new PresenceFilterProxyModel(this);



    // Filter
    connect(ui->le_pf_firstname, SIGNAL(textChanged(const QString &)), _presenceFilterProxyModel, SLOT(setFirstNameFilter(const QString&)));
    connect(ui->le_pf_lastname, SIGNAL(textChanged(const QString &)), _presenceFilterProxyModel, SLOT(setLastNameFilter(const QString&)));

    // Database save and connect
    connect(ui->pb_dbconnect, SIGNAL(clicked()), this, SLOT(dbSaveAndConnect()));

    // Refresh
    connect(ui->pb_refresh, SIGNAL(clicked()), this, SLOT(reload()));

    // Students
    connect(ui->pb_addstudent, SIGNAL(clicked()), this, SLOT(openDialog()));
    connect(ui->pb_modifystudent, SIGNAL(clicked()), this, SLOT(openDialog()));
    connect(ui->tv_students, SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(openDialog()));
    connect(ui->pb_deletestudent, SIGNAL(clicked()), this, SLOT(deleteStudent()));

    // Presences
    connect(ui->pb_addpresence, SIGNAL(clicked()), this, SLOT(openDialog()));
    connect(ui->pb_modifypresence, SIGNAL(clicked()), this, SLOT(openDialog()));
    connect(ui->tv_presences, SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(openDialog()));
    connect(ui->pb_deletepresence, SIGNAL(clicked()), this, SLOT(deletePresence()));

    // Training
    connect(ui->pb_addtraining, SIGNAL(clicked()), this, SLOT(openDialog()));
    connect(ui->pb_modifytraining, SIGNAL(clicked()), this, SLOT(openDialog()));
    connect(ui->tv_training, SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(openDialog()));
    connect(ui->pb_deletetraining, SIGNAL(clicked()), this, SLOT(deleteTraining()));

    // Options
    connect(ui->pb_addoption, SIGNAL(clicked()), this, SLOT(openDialog()));
    connect(ui->pb_modifyoption, SIGNAL(clicked()), this, SLOT(openDialog()));
    connect(ui->tv_options, SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(openDialog()));
    connect(ui->pb_deleteoption, SIGNAL(clicked()), this, SLOT(deleteOption()));



//    _presencesProxy = new QSortFilterProxyModel(this);
//    _presencesProxy->setSourceModel(_badgeuseModel->getPresencesModel());

//    _pfFirstname = new QSortFilterProxyModel(this);
//    _pfLastname = new QSortFilterProxyModel(this);
//    _pfFirstname->setFilterKeyColumn(6);
//    _pfLastname->setFilterKeyColumn(7);


//    _pfFirstname->setSourceModel(_presencesProxy);
//    _pfLastname->setSourceModel(_pfFirstname);

    _presenceFilterProxyModel->setSourceModel(_badgeuseModel->getPresencesModel());
    ui->tv_presences->setModel(_presenceFilterProxyModel);


//    // GO PROXY
//    _studentProxy = new QSortFilterProxyModel(this);
//    _studentProxy->setSourceModel(_badgeuseModel->getStudentsModel());
//    ui->tv_students->setModel(_studentProxy);

//    _trainingProxy = new QSortFilterProxyModel(this);
//    _trainingProxy->setSourceModel(_badgeuseModel->getTrainingModel());
//    ui->tv_training->setModel(_trainingProxy);

//    _optionsProxy = new QSortFilterProxyModel(this);
//    _optionsProxy->setSourceModel(_badgeuseModel->getOptionsModel());
//    ui->tv_options->setModel(_optionsProxy);


    ui->tv_presences->setColumnHidden(0, true);
    ui->tv_students->setColumnHidden(0, true);
    ui->tv_options->setColumnHidden(0, true);
    ui->tv_training->setColumnHidden(0, true);









//    ui->statusBar->sonPresenceFilterChangedhowMessage(tr("Connexion à la base de données..."));


//    model = new presencesModel(this, _db);
//    QSqlQuery *query = new QSqlQuery("SELECT s.firstname, s.lastname, s.student_number, s.mail_adress, s.rfid_number from student s inner join promotion p on s.promotion_id = p.id");
//    model->setQuery(*query);

//    for (int i = 0; i < static_cast<int>(sizeof(absencesHeaderTitles) / sizeof (absencesHeaderTitles[0])); i++) {
//        model->setHeaderData(i, Qt::Horizontal, tr(absencesHeaderTitles[i].name.c_str()));
//        ui->tv_students->setModel(model);
//        ui->tv_students->setColumnHidden(i, !absencesHeaderTitles[i].show);
//    }






//    fnFilter = new QSortFilterProxyModel(model);
//    fnFilter->setSourceModel(nmFilter);
//    fnFilter->setFilterKeyColumn(1);

//    ui->tv_students->setModel(fnFilter);


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


MainWindow::~MainWindow()
{
    delete ui;
}




/* Dialog add modify student, training, presence, option */
void MainWindow::openDialog()
{
    QString selectedUuid;
    QTableView *tv = nullptr;

    // Student
    if (sender() == ui->pb_modifystudent || sender() == ui->tv_students) {
        tv = ui->tv_students;
    } else if (sender() == ui->pb_modifypresence || sender() == ui->tv_presences) {
        tv = ui->tv_presences;
    } else if (sender() == ui->pb_modifytraining || sender() == ui->tv_training) {
        tv = ui->tv_training;
    } else if (sender() == ui->pb_modifyoption || sender() == ui->tv_options) {
        tv = ui->tv_options;
    }

    if (tv != nullptr) {
        QModelIndexList selectedList = tv->selectionModel()->selectedRows();
        if (selectedList.length() > 0) {
            selectedUuid = tv->model()->data(tv->model()->index(selectedList.at(0).row(),0)).toString();
        } else {
            QMessageBox::information(this, "Information", "Veuillez selectionner une ligne.");
            return;
        }
    }

    if (sender() == ui->pb_modifystudent || sender() == ui->pb_addstudent || sender() == ui->tv_students)
    {
        _studentsDialog = new StudentsDialog(_badgeuseModel->getStudentsModel(), this, selectedUuid);
        if (_studentsDialog->exec() == QDialog::Accepted) {
            _badgeuseModel->reload();
        }
        delete _studentsDialog;
    }
    else if (sender() == ui->pb_modifypresence || sender() == ui->pb_addpresence || sender() == ui->tv_presences)
    {
        _presencesDialog = new PresencesDialog(_badgeuseModel->getPresencesModel(), this, selectedUuid);
        if (_presencesDialog->exec() == QDialog::Accepted) {
            _badgeuseModel->reload();
        }
        delete _presencesDialog;
    }
    else if (sender() == ui->pb_modifytraining || sender() == ui->pb_addtraining || sender() == ui->tv_training)
    {
        _trainingDialog = new TrainingDialog(_badgeuseModel->getTrainingModel(), this, selectedUuid);
        if (_trainingDialog->exec() == QDialog::Accepted) {
            _badgeuseModel->reload();
        }
        delete _trainingDialog;
    }
    else if (sender() == ui->pb_modifyoption || sender() == ui->pb_addoption || sender() == ui->tv_options)
    {
        _optionsDialog = new OptionsDialog(_badgeuseModel->getOptionsModel(), this, selectedUuid);
        if (_optionsDialog->exec() == QDialog::Accepted) {
            _badgeuseModel->reload();
        }
        delete _optionsDialog;
    }

}


void MainWindow::reload() {
    _badgeuseModel->reload();
}



void MainWindow::deleteStudent() {
    QString selectedUuid;

    QModelIndexList selectedList = ui->tv_students->selectionModel()->selectedRows();
    if (selectedList.length() > 0) {
        selectedUuid = ui->tv_students->model()->data(ui->tv_students->model()->index(selectedList.at(0).row(),0)).toString();

        QMessageBox msgBox;
        msgBox.setText("L'étudiant selectionné va être supprimé définitivement. Ses badgeages lié à sa carte étudiant vont être dissociés (mais pas supprimés).");
        msgBox.setInformativeText("Êtes-vous sûr de vouloir continuer ?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        int ret = msgBox.exec();

        if (ret == QMessageBox::Yes) {
            _badgeuseModel->getStudentsModel()->remove(selectedUuid);
        }

    } else {
        QMessageBox::information(this, "Information", "Veuillez selectionner une ligne.");
        return;
    }

}


void MainWindow::deletePresence() {
    QString selectedUuid;

    QModelIndexList selectedList = ui->tv_presences->selectionModel()->selectedRows();
    if (selectedList.length() > 0) {
        selectedUuid = ui->tv_presences->model()->data(ui->tv_presences->model()->index(selectedList.at(0).row(),0)).toString();

        QMessageBox msgBox;
        msgBox.setText("La présence selectionnée va être supprimée définitivement.");
        msgBox.setInformativeText("Êtes-vous sûr de vouloir continuer ?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        int ret = msgBox.exec();

        if (ret == QMessageBox::Yes) {
            _badgeuseModel->getPresencesModel()->remove(selectedUuid);
        }

    } else {
        QMessageBox::information(this, "Information", "Veuillez selectionner une ligne.");
        return;
    }

}


void MainWindow::deleteTraining() {
    QString selectedUuid;
    QTableView *tv = ui->tv_training;

    QModelIndexList selectedList = tv->selectionModel()->selectedRows();
    if (selectedList.length() > 0) {
        selectedUuid = tv->model()->data(tv->model()->index(selectedList.at(0).row(),0)).toString();

        QSqlQuery queryCount("select count(*) from badgeuse.students stu where stu.trainingUuid = UNHEX(?);");
        queryCount.addBindValue(selectedUuid);
        queryCount.exec();
        int count;
        if (queryCount.first()) {
            count = queryCount.value(0).toInt();
            if (count > 0) {
                QString text = QString("Impossible de supprimer cette formation. Il y a %1 étudiant(s) qui y sont rattaché(s).").arg(count);
                QMessageBox::critical(this, "Impossible", text);
                return;
            }
        } else {
            qDebug() << "Error queryCount " << queryCount.lastError().text();
            return;
        }

        QMessageBox msgBox;
        msgBox.setText("La formation selectionnée va être supprimée définitivement.");
        msgBox.setInformativeText("Êtes-vous sûr de vouloir continuer ?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        int ret = msgBox.exec();

        if (ret == QMessageBox::Yes) {
            _badgeuseModel->getTrainingModel()->remove(selectedUuid);
        }

    } else {
        QMessageBox::information(this, "Information", "Veuillez selectionner une ligne.");
        return;
    }
}




void MainWindow::deleteOption() {
    QString selectedUuid;
    QTableView *tv = ui->tv_options;

    QModelIndexList selectedList = tv->selectionModel()->selectedRows();
    if (selectedList.length() > 0) {
        selectedUuid = tv->model()->data(tv->model()->index(selectedList.at(0).row(),0)).toString();

        QSqlQuery queryCount("select count(*) from badgeuse.students stu where stu.trainingUuid = UNHEX(?);");
        queryCount.addBindValue(selectedUuid);
        queryCount.exec();
        int count;
        if (queryCount.first()) {
            count = queryCount.value(0).toInt();
            if (count > 0) {
                QString text = QString("Impossible de supprimer cette formation. Il y a %1 étudiant(s) qui y sont rattaché(s).").arg(count);
                QMessageBox::critical(this, "Impossible", text);
                return;
            }
        } else {
            qDebug() << "Error queryCount " << queryCount.lastError().text();
            return;
        }

        QMessageBox msgBox;
        msgBox.setText("La formation selectionnée va être supprimée définitivement.");
        msgBox.setInformativeText("Êtes-vous sûr de vouloir continuer ?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        int ret = msgBox.exec();

        if (ret == QMessageBox::Yes) {
            _badgeuseModel->getTrainingModel()->remove(selectedUuid);
        }

    } else {
        QMessageBox::information(this, "Information", "Veuillez selectionner une ligne.");
        return;
    }
}





/*void MainWindow::onPresenceFilterChanged()
{

    if (sender() == ui->le_pf_firstname) { applyFilter(6, ui->le_pf_firstname->text()); }
    if (sender() == ui->le_pf_lastname) { applyFilter(7, ui->le_pf_lastname->text()); }

}*/


// GO PROXY
/*void MainWindow::applyFilter(int index, QString ntext)
{
    switch(index)
    {
        case 6:
            _pfFirstname->setFilterRegExp(QRegExp(ntext, Qt::CaseInsensitive));
            break;
        case 7:
            _pfLastname->setFilterRegExp(QRegExp(ntext, Qt::CaseInsensitive));
            break;
    }
}*/




void MainWindow::dbSaveAndConnect()
{
     _dbSettings->setValue("db_host", ui->le_host->text());
     _dbSettings->setValue("db_port", ui->sb_port->value());
     _dbSettings->setValue("db_dbname", ui->le_dbname->text());
     _dbSettings->setValue("db_user", ui->le_user->text());
     _dbSettings->setValue("db_password", ui->le_password->text());

     if (_badgeuseModel->initDbConnection()) {
         QMessageBox::information(this, "Succès", "Connexion réussie.", QMessageBox::Ok);
     } else {
         QMessageBox::critical(this, "Attention", "Impossible de se connecter à la base de données.", QMessageBox::Ok);
     }
}



//void MainWindow::textFilterFamilyNameChanged()
//{
//    QRegExp regExp(ui->lineEdit_5->text());
//    fnFilter->setFilterRegExp(regExp);
//}


//void MainWindow::customHeaderMenuRequested(QPoint pos){
////    QModelIndex index = ui->tv_students->indexAt(pos);

//    QMenu *menu=new QMenu(this);

//    for (int i = 0; i < static_cast<int>(sizeof(absencesHeaderTitles) / sizeof (absencesHeaderTitles[0])); i++) {
//        QAction* fooAction = new QAction(absencesHeaderTitles[i].name.c_str(), this);
//        fooAction->setData(i);
//        fooAction->setCheckable(true);
//        fooAction->setChecked(absencesHeaderTitles[i].show);
////        connect(fooAction, SIGNAL(triggered()), this, SLOT(toggleColumn()));
//        connect(fooAction, &QAction::triggered, [this, fooAction](){
//                toggleColumn(fooAction->data());
//            });
//        menu->addAction(fooAction);
//    }

//    menu->popup(ui->tv_students->horizontalHeader()->viewport()->mapToGlobal(pos));
//}

//void MainWindow::refresh()
//{
//    //model->select();
//}
//void MainWindow::toggleColumn(QVariant v)
//{
//    bool exec = true;
//    bool newValue = ui->tv_students->isColumnHidden(v.toInt());

//    int cpt_show = 0;
//    if (!newValue) { // si on cache un élement
//        for (Col& s: absencesHeaderTitles){ // on compte le nombre d'élement affiché
//            if (s.show) cpt_show++;
//        }
//        if (cpt_show < 2) exec = false; // si il reste 1 element, on ne le cache pas
//    }

//    if (exec) {
//        absencesHeaderTitles[v.toInt()].show = newValue;
//        ui->tv_students->setColumnHidden(v.toInt(), !newValue);
//    }
//}


