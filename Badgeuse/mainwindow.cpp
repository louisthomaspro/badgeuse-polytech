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



    ui->tv_presences->setModel(_badgeuseModel->getFilterProxyPresencesModel());

    ui->tv_students->setModel(_badgeuseModel->getFilterProxyStudentsModel());

    ui->tv_training->setModel(_badgeuseModel->getTrainingModel());
    ui->tv_options->setModel(_badgeuseModel->getOptionsModel());





    //------- CONNECT -------//

    // Connect
    connect(ui->pb_exportpresences, SIGNAL(clicked()), this, SLOT(exportPresences()));

    // CSV export

    // Update options
    connect(ui->cb_pf_training, SIGNAL(currentIndexChanged(int)), this, SLOT(updatePfOptions()));
    connect(ui->cb_sf_training, SIGNAL(currentIndexChanged(int)), this, SLOT(updateSfOptions()));

    // Presence filter
    connect(ui->le_pf_firstname, SIGNAL(textChanged(const QString &)), _badgeuseModel->getFilterProxyPresencesModel(), SLOT(setFirstnameFilter(const QString&)));
    connect(ui->le_pf_lastname, SIGNAL(textChanged(const QString &)), _badgeuseModel->getFilterProxyPresencesModel(), SLOT(setLastnameFilter(const QString&)));
    connect(ui->le_pf_studentnumber, SIGNAL(textChanged(const QString &)), _badgeuseModel->getFilterProxyPresencesModel(), SLOT(setStudentNumberFilter(const QString&)));
    connect(ui->cb_pf_cardreader, SIGNAL(currentTextChanged(const QString &)), _badgeuseModel->getFilterProxyPresencesModel(), SLOT(setCardReaderFilter(const QString&)));
    connect(ui->cb_pf_training, SIGNAL(currentTextChanged(const QString &)), _badgeuseModel->getFilterProxyPresencesModel(), SLOT(setTrainingFilter(const QString&)));
    connect(ui->cb_pf_option, SIGNAL(currentTextChanged(const QString &)), _badgeuseModel->getFilterProxyPresencesModel(), SLOT(setOptionFilter(const QString&)));
    connect(ui->le_pf_groupnumber, SIGNAL(textChanged(const QString &)), _badgeuseModel->getFilterProxyPresencesModel(), SLOT(setGroupNumberFilter(const QString&)));
    connect(ui->le_pf_promotion, SIGNAL(textChanged(const QString &)), _badgeuseModel->getFilterProxyPresencesModel(), SLOT(setPromotionFilter(const QString&)));
    connect(ui->de_pf_begindate, SIGNAL(dateTimeChanged(const QDateTime &)), _badgeuseModel->getFilterProxyPresencesModel(), SLOT(setBeginFilter(const QDateTime &)));
    connect(ui->de_pf_enddate, SIGNAL(dateTimeChanged(const QDateTime &)), _badgeuseModel->getFilterProxyPresencesModel(), SLOT(setEndFilter(const QDateTime &)));
    connect(ui->gb_pf_period, SIGNAL(toggled(const bool &)), _badgeuseModel->getFilterProxyPresencesModel(), SLOT(setPeriodFilter(const bool &)));
    connect(ui->cb_pf_displaynull, SIGNAL(toggled(const bool &)), _badgeuseModel->getFilterProxyPresencesModel(), SLOT(setDisplayNullFilter(const bool &)));

    // Student filter
    connect(ui->le_sf_firstname, SIGNAL(textChanged(const QString &)), _badgeuseModel->getFilterProxyStudentsModel(), SLOT(setFirstnameFilter(const QString&)));
    connect(ui->le_sf_lastname, SIGNAL(textChanged(const QString &)), _badgeuseModel->getFilterProxyStudentsModel(), SLOT(setLastnameFilter(const QString&)));
    connect(ui->le_sf_studentnumber, SIGNAL(textChanged(const QString &)), _badgeuseModel->getFilterProxyStudentsModel(), SLOT(setStudentNumberFilter(const QString&)));
    connect(ui->cb_sf_training, SIGNAL(currentTextChanged(const QString &)), _badgeuseModel->getFilterProxyStudentsModel(), SLOT(setTrainingFilter(const QString&)));
    connect(ui->cb_sf_option, SIGNAL(currentTextChanged(const QString &)), _badgeuseModel->getFilterProxyStudentsModel(), SLOT(setOptionFilter(const QString&)));
    connect(ui->le_sf_groupnumber, SIGNAL(textChanged(const QString &)), _badgeuseModel->getFilterProxyStudentsModel(), SLOT(setGroupNumberFilter(const QString&)));
    connect(ui->le_sf_promotion, SIGNAL(textChanged(const QString &)), _badgeuseModel->getFilterProxyStudentsModel(), SLOT(setPromotionFilter(const QString&)));
    connect(ui->le_sf_promotion, SIGNAL(textChanged(const QString &)), _badgeuseModel->getFilterProxyStudentsModel(), SLOT(setPromotionFilter(const QString&)));
    connect(ui->le_sf_mail, SIGNAL(textChanged(const QString &)), _badgeuseModel->getFilterProxyStudentsModel(), SLOT(setMailFilter(const QString&)));


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



    initFilters();


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


// Reload models and filters
void MainWindow::reload()
{
    _badgeuseModel->reload();
    initFilters();
}


void MainWindow::initFilters()
{

    // Fill pf cardreaders
    ui->cb_pf_cardreader->clear();
    ui->cb_pf_cardreader->addItem("");
    for (QMap<QString, QVariant> item : _badgeuseModel->getCardReaderModel()->get()) {
        ui->cb_pf_cardreader->addItem(item["information"].toString(), item["uuid"].toByteArray().toHex());
    }

    // Fill pf sf trainings
    ui->cb_pf_training->clear();
    ui->cb_pf_training->addItem("");
    ui->cb_sf_training->clear();
    ui->cb_sf_training->addItem("");
    for (QMap<QString, QVariant> item : _badgeuseModel->getTrainingModel()->get()) {
        ui->cb_pf_training->addItem(item["name"].toString(), item["uuid"].toByteArray().toHex());
        ui->cb_sf_training->addItem(item["name"].toString(), item["uuid"].toByteArray().toHex());
    }

    // Set default dates for presences period
    ui->de_pf_begindate->setDate(QDate(QDate::currentDate().year(), 1, 1));
    ui->de_pf_enddate->setDate(QDate(QDate::currentDate().year(), 12, 31));

    // Set default dates for export period
    ui->de_export_begin->setDate(QDate(QDate::currentDate().year(), 1, 1));
    ui->de_export_end->setDate(QDate(QDate::currentDate().year(), 12, 31));

    updatePfOptions();
    updateSfOptions();

    // Init studentList for export
    ui->cb_export_student->clear();
    ui->cb_export_student->addItem("");
    for (QMap<QString, QVariant> item : _badgeuseModel->getStudentsModel()->get()) {
        ui->cb_export_student->addItem(item["text"].toString(), item["uuid"].toByteArray().toHex());
    }

}


void MainWindow::updatePfOptions()
{
    // Fill options
    ui->cb_pf_option->clear();
    ui->cb_pf_option->addItem("");
    for (QMap<QString, QVariant> item : _badgeuseModel->getOptionsModel()->getFromTraining(ui->cb_pf_training->currentData().toString())) {
        ui->cb_pf_option->addItem(item["name"].toString(), item["uuid"].toByteArray().toHex());
    }
}

void MainWindow::updateSfOptions()
{
    // Fill options
    ui->cb_sf_option->clear();
    ui->cb_sf_option->addItem("");
    for (QMap<QString, QVariant> item : _badgeuseModel->getOptionsModel()->getFromTraining(ui->cb_sf_training->currentData().toString())) {
        ui->cb_sf_option->addItem(item["name"].toString(), item["uuid"].toByteArray().toHex());
    }
}


void MainWindow::exportPresences()
{

    QList<QMap<QString, QVariant>> values = _badgeuseModel->getPresencesModel()->getExport(
        ui->cb_export_student->currentData().toString(),
        (ui->gb_export_period->isChecked() ? ui->de_export_begin->dateTime() : QDateTime()),
        (ui->gb_export_period->isChecked() ? ui->de_export_end->dateTime() : QDateTime())
    );

    if (values.size() <= 0) {
        QMessageBox::information(this, "Information", "Aucune donnée trouvée.");
        return;
    }


    QString textData;
    foreach( QString key, values.first().keys() ) {
        textData += key;
        textData += ", ";
    }
    textData += "\n";

    for (QMap<QString, QVariant> row : values) {
        foreach (QVariant col, row) {
           textData += col.toString();
           textData += ", ";
        }
        textData += "\n";
    }

    // .csv
    QString savefile = QFileDialog::getSaveFileName(this,
                                                    tr("Open File"),
                                                    QStandardPaths::writableLocation(QStandardPaths::DownloadLocation),
                                                    tr("*.csv"));
    QFile csvFile(savefile.split(".",QString::SkipEmptyParts).at(0) + ".csv");
    if(csvFile.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        QTextStream out(&csvFile);
        out << textData;
        csvFile.close();
    }
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
        _studentsDialog = new StudentsDialog(_badgeuseModel->getStudentsModel(), _badgeuseModel->getTrainingModel(), _badgeuseModel->getPresencesModel(), _badgeuseModel->getOptionsModel(), this, selectedUuid);
        if (_studentsDialog->exec() == QDialog::Accepted) {
            reload();
        }
        delete _studentsDialog;
    }
    else if (sender() == ui->pb_modifypresence || sender() == ui->pb_addpresence || sender() == ui->tv_presences)
    {
        _presencesDialog = new PresencesDialog(_badgeuseModel->getPresencesModel(), _badgeuseModel->getCardReaderModel(), _badgeuseModel->getStudentsModel(), this, selectedUuid);
        if (_presencesDialog->exec() == QDialog::Accepted) {
            reload();
        }
        delete _presencesDialog;
    }
    else if (sender() == ui->pb_modifytraining || sender() == ui->pb_addtraining || sender() == ui->tv_training)
    {
        _trainingDialog = new TrainingDialog(_badgeuseModel->getTrainingModel(), this, selectedUuid);
        if (_trainingDialog->exec() == QDialog::Accepted) {
            reload();
        }
        delete _trainingDialog;
    }
    else if (sender() == ui->pb_modifyoption || sender() == ui->pb_addoption || sender() == ui->tv_options)
    {
        _optionsDialog = new OptionsDialog(_badgeuseModel->getOptionsModel(), _badgeuseModel->getTrainingModel(), this, selectedUuid);
        if (_optionsDialog->exec() == QDialog::Accepted) {
            reload();
        }
        delete _optionsDialog;
    }

}


QString MainWindow::getTvSelectedUuid(QTableView *tv)
{
    QModelIndexList selectedList = tv->selectionModel()->selectedRows();
    if (selectedList.length() > 0) {
        return tv->model()->data(tv->model()->index(selectedList.at(0).row(),0)).toString();
    } else {
        QMessageBox::information(this, "Information", "Veuillez selectionner une ligne.");
        return nullptr;
    }
}



void MainWindow::deleteStudent()
{
    QString selectedUuid = getTvSelectedUuid(ui->tv_students);
    if (selectedUuid != nullptr) {
        QMessageBox msgBox;
        msgBox.setText("L'étudiant selectionné va être supprimé définitivement. Ses badgeages lié à sa carte étudiant vont être dissociés (mais pas supprimés).");
        msgBox.setInformativeText("Êtes-vous sûr de vouloir continuer ?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        int ret = msgBox.exec();

        if (ret == QMessageBox::Yes) {
            _badgeuseModel->getStudentsModel()->remove(selectedUuid);
            _badgeuseModel->reload();
        }
    }
}


void MainWindow::deletePresence()
{
    QString selectedUuid = getTvSelectedUuid(ui->tv_presences);
    if (selectedUuid != nullptr) {
        QMessageBox msgBox;
        msgBox.setText("La présence selectionnée va être supprimée définitivement.");
        msgBox.setInformativeText("Êtes-vous sûr de vouloir continuer ?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        int ret = msgBox.exec();

        if (ret == QMessageBox::Yes) {
            _badgeuseModel->getPresencesModel()->remove(selectedUuid);
            _badgeuseModel->reload();
        }
    }
}


void MainWindow::deleteTraining()
{
    QString selectedUuid = getTvSelectedUuid(ui->tv_training);
    if (selectedUuid != nullptr) {


        QMessageBox msgBox;
        msgBox.setText("La formation selectionnée va être supprimée définitivement.");
        msgBox.setInformativeText("Êtes-vous sûr de vouloir continuer ?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        int ret = msgBox.exec();

        if (ret == QMessageBox::Yes) {
            if (!_badgeuseModel->getTrainingModel()->remove(selectedUuid)) {
                QMessageBox::critical(this, "Impossible", "Une erreur est survenu. Merci de vérifier si aucun étudiant n'est affectés à cette formation.");
            }
            _badgeuseModel->reload();
            initFilters();
        }
    }
}




void MainWindow::deleteOption()
{
    QString selectedUuid = getTvSelectedUuid(ui->tv_options);
    if (selectedUuid != nullptr) {
        QMessageBox msgBox;
        msgBox.setText("La formation selectionnée va être supprimée définitivement.");
        msgBox.setInformativeText("Êtes-vous sûr de vouloir continuer ?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        int ret = msgBox.exec();

        if (ret == QMessageBox::Yes) {
            if (!_badgeuseModel->getOptionsModel()->remove(selectedUuid)) {
                QMessageBox::critical(this, "Impossible", "Une erreur est survenu. Merci de vérifier si aucun étudiant n'est affectés à cette options.");
            }
            _badgeuseModel->reload();
            initFilters();
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
     }
}


