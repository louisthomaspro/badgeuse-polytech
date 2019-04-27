#include "presencesdialog.h"

PresencesDialog::PresencesDialog(PresencesModel *presenceModel, QWidget *parent, QString presenceUuid) :
    QDialog(parent),
    ui(new Ui::PresencesDialog)
{
    ui->setupUi(this);

    _presenceModel = presenceModel;
    _presenceUuid = &presenceUuid;


    // Connect
    connect(this, SIGNAL(accepted()), this, SLOT(validateValues()));


    // Init cardreaders combobox
    QSqlQuery queryCardreaders("select cr.uuid, cr.information from badgeuse.cardreaders cr;");
    ui->cb_cardReader->addItem("", "");
    while (queryCardreaders.next()) {
        ui->cb_cardReader->addItem(queryCardreaders.value(1).toString(), queryCardreaders.value(0).toByteArray().toHex());
    }

    // Init students combobox
    QSqlQuery queryStudents("select stu.uuid, CONCAT(stu.studentNumber, ' - ', stu.firstname, ' ', stu.lastname) from badgeuse.students stu;");
    ui->cb_student->addItem("", "");
    while (queryStudents.next()) {
        ui->cb_student->addItem(queryStudents.value(1).toString(), queryStudents.value(0).toByteArray().toHex());
    }

    // Init dateTime
    ui->dt_entry->setDate(QDate::currentDate());
    ui->dt_exit->setDate(QDate::currentDate());



    if (!_presenceUuid->isEmpty()) {

        ui->l_title->setText("Modification d'une présence");


//        qDebug() << "Loading uuid " + *_presenceUuid;

        QMap<QString, QVariant> presenceInfo = _presenceModel->getPresence(*_presenceUuid);

        ui->cb_cardReader->setCurrentIndex(ui->cb_cardReader->findData(presenceInfo["cardreaderUuid"].toByteArray().toHex()));
        ui->cb_student->setCurrentIndex(ui->cb_student->findData(presenceInfo["studentUuid"].toByteArray().toHex()));

        ui->dt_entry->setDateTime(QDateTime::fromTime_t(presenceInfo["dateTimeEntry"].toUInt()));
        ui->dt_exit->setDateTime(QDateTime::fromTime_t(presenceInfo["dateTimeExit"].toUInt()));


    } else {
        ui->l_title->setText("Ajout d'une présence");
    }



}

PresencesDialog::~PresencesDialog()
{
    delete ui;
}



void PresencesDialog::accept()
{

    if (validateValues()) {

        if (_presenceUuid->isEmpty()) {
            _presenceModel->add(
                        ui->dt_entry->dateTime().toTime_t(),
                        ui->dt_exit->dateTime().toTime_t(),
                        ui->cb_cardReader->currentData().toString(),
                        ui->cb_student->currentData().toString()
                        );
        } else {
            _presenceModel->modify(
                        *_presenceUuid,
                        ui->dt_entry->dateTime().toTime_t(),
                        ui->dt_exit->dateTime().toTime_t(),
                        ui->cb_cardReader->currentData().toString(),
                        ui->cb_student->currentData().toString()
                        );
        }

        QDialog::accept();
    }


}


bool PresencesDialog::validateValues() {

    QString error = QString("");


//    if (ui->le_studentNumber->text().length() != 8) {
//        error += "\n - La taille du numéro étudiant est incorrect.";
//    }
//    QRegExp digitREX("\\d*");  // a digit (\d), zero or more times (*)
//    if (!digitREX.exactMatch(ui->le_studentNumber->text())) {
//        error += "\n - Le numéro étudiant doit être composé uniquement de chiffre.";
//    }

//    if (ui->le_firstname->text().length() < 1) {
//        error += "\n - Le champ 'Nom' doit être rempli.";
//    }
//    if (ui->le_lastname->text().length() < 1) {
//        error += "\n - Le champ 'Prénom' doit être rempli.";
//    }

//    QRegExp mailREX("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b");
//    mailREX.setCaseSensitivity(Qt::CaseInsensitive);
//    mailREX.setPatternSyntax(QRegExp::RegExp);
//    if (!mailREX.exactMatch(ui->le_mail->text())) {
//        error += "\n - L'adresse mail est incorrect.";
//    }


    // CHECK RFID IF ITS GOOD and not empty



    if (error.length()>0) {
        QMessageBox::critical(this, "Attention",
        "Certain champ ne sont pas correct : " + error,
        QMessageBox::Ok);
        return false;
    }

    return true;


}
