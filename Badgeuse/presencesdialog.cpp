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

        ui->dt_entry->setDateTime(presenceInfo["presenceEntry"].toDateTime());
        ui->dt_exit->setDateTime(presenceInfo["firstname"].toDateTime());

        int indexCardreader = ui->cb_cardReader->findData(presenceInfo["cardreaderUuid"]);
        if ( indexCardreader != -1 ) { // -1 for not found
           ui->cb_cardReader->setCurrentIndex(indexCardreader);
        }

        int indexStudent = ui->cb_student->findData(presenceInfo["studentUuid"]);
        if ( indexStudent != -1 ) { // -1 for not found
           ui->cb_student->setCurrentIndex(indexStudent);
        }

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

//        if (_presenceUuid->isEmpty()) {
//            _presenceModel->add(
//                        ui->le_studentNumber->text(),
//                        ui->le_firstname->text(),
//                        ui->le_lastname->text(),
//                        ui->le_mail->text(),
//                        ui->sb_degreeYear->value(),
//                        ui->cb_trainingName->currentData().toString(),
//                        ui->sb_group->value(),
//                        ui->cb_rfidNumber->currentData().toString(),
//                        _optionsList->getCheckedItems());
//        } else {
//            _presenceModel->modify(
//                        *_presenceUuid,
//                        ui->le_studentNumber->text(),
//                        ui->le_firstname->text(),
//                        ui->le_lastname->text(),
//                        ui->le_mail->text(),
//                        ui->sb_degreeYear->value(),
//                        ui->cb_trainingName->currentData().toString(),
//                        ui->sb_group->value(),
//                        ui->cb_rfidNumber->currentData().toString(),
//                        _optionsList->getCheckedItems());
//        }

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
