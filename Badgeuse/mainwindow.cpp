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


    // Init database settings
    _dbSettings = new QSettings("dbsettings.ini", QSettings::NativeFormat);
    ui->le_host->setText(_dbSettings->value("db_host", "").toString());
    ui->sb_port->setValue(_dbSettings->value("db_port", "").toInt());
    ui->le_dbname->setText(_dbSettings->value("db_dbname", "").toString());
    ui->le_user->setText(_dbSettings->value("db_user", "").toString());
    ui->le_password->setText(_dbSettings->value("db_password", "").toString());


    // Init models
    _badgeuseModel = new BadgeuseModel(*_dbSettings, this);
    _presencesFilterProxyModel = new PresencesFilterProxyModel(this);
//    _studentsFilterProxyModel = new StudentsFilterProxyModel(this);

    _presencesFilterProxyModel->setSourceModel(_badgeuseModel->getPresencesModel());
    ui->tv_presences->setModel(_presencesFilterProxyModel);



    //------- CONNECT -------//

    // Filters
    connect(ui->le_pf_firstname, SIGNAL(textChanged(const QString &)), _presencesFilterProxyModel, SLOT(setFirstNameFilter(const QString&)));
    connect(ui->le_pf_lastname, SIGNAL(textChanged(const QString &)), _presencesFilterProxyModel, SLOT(setLastNameFilter(const QString&)));

    // Database parameters
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


    ui->tv_presences->setColumnHidden(0, true);
    ui->tv_students->setColumnHidden(0, true);
    ui->tv_options->setColumnHidden(0, true);
    ui->tv_training->setColumnHidden(0, true);


//    ui->statusBar->sonPresenceFilterChangedhowMessage(tr("Status bar..."));


}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::reload() {
    _badgeuseModel->reload();
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


QString MainWindow::getTvSelectedUuid(QTableView *tv) {
    QModelIndexList selectedList = tv->selectionModel()->selectedRows();
    if (selectedList.length() > 0) {
        return tv->model()->data(tv->model()->index(selectedList.at(0).row(),0)).toString();
    } else {
        QMessageBox::information(this, "Information", "Veuillez selectionner une ligne.");
        return nullptr;
    }
}



void MainWindow::deleteStudent() {
    QString selectedUuid = getTvSelectedUuid(ui->tv_students);
    if (selectedUuid != nullptr) {
        QMessageBox msgBox;
        msgBox.setText("L'étudiant selectionné va être supprimé définitivement. Ses badgeages lié à sa carte étudiant vont être dissociés (mais pas supprimés).");
        msgBox.setInformativeText("Êtes-vous sûr de vouloir continuer ?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        int ret = msgBox.exec();

        if (ret == QMessageBox::Yes) {
            _badgeuseModel->getStudentsModel()->remove(selectedUuid);
        }
    }
}


void MainWindow::deletePresence() {
    QString selectedUuid = getTvSelectedUuid(ui->tv_presences);
    if (selectedUuid != nullptr) {
        QMessageBox msgBox;
        msgBox.setText("La présence selectionnée va être supprimée définitivement.");
        msgBox.setInformativeText("Êtes-vous sûr de vouloir continuer ?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        int ret = msgBox.exec();

        if (ret == QMessageBox::Yes) {
            _badgeuseModel->getPresencesModel()->remove(selectedUuid);
        }
    }
}


void MainWindow::deleteTraining() {
    QString selectedUuid = getTvSelectedUuid(ui->tv_training);
    if (selectedUuid != nullptr) {
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
    }
}




void MainWindow::deleteOption() {
    QString selectedUuid = getTvSelectedUuid(ui->tv_options);
    if (selectedUuid != nullptr) {
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
    }
}




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


