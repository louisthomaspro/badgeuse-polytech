#include "studentsdialog.h"
#include "ui_studentsdialog.h"

StudentsDialog::StudentsDialog(QWidget *parent, QString studentUuid) :
    QDialog(parent),
    ui(new Ui::StudentsDialog)
{
    ui->setupUi(this);


    _optionsList = new QCheckList(this);
    ui->formLayout->replaceWidget(ui->l_optionsList, _optionsList);



    connect(ui->cb_trainingName, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(updateOptions(const QString&)));
    connect(this, SIGNAL(accepted()), this, SLOT(validateValues()));



    // INIT COMBOBOX
    QSqlQuery queryTraining("select t.name, t.uuid from badgeuse.training t;");
    while (queryTraining.next()) {
        QString training = queryTraining.value(0).toString();
        ui->cb_trainingName->addItem(training);
    }


    if (studentUuid.isEmpty()) {



        ui->sb_degreeYear->setValue(QDate::currentDate().year()+3);

        QSqlQuery queryRfid("SELECT "
                            "DISTINCT s.rfidNumber "
                            "FROM badgeuse.scans s "
                            "WHERE s.studentUuid IS NULL "
                            "order by s.DateTimeExit desc, s.dateTimeEntry desc limit 1;");

        if (queryRfid.next()) {
            ui->le_rfidNumber->setText(queryRfid.value(0).toByteArray().toHex().toUpper());
        } else {
            ui->le_rfidNumber->setText("No rfid found");
        }



    } else { // uuid found


        qDebug() << "Loading uuid " + studentUuid;

        QSqlQuery queryStudent;
        queryStudent.prepare("select stu.studentNumber, stu.lastname, stu.firstname, stu.mail stu.degreeYear, t.name, stu.`group`, o.name, stu.rfidNumber  from badgeuse.students stu "
                      "left join badgeuse.training t on stu.trainingUuid = t.uuid "
                      "left join badgeuse.rlToptionsStudents ostu on ostu.studentsUuid = stu.uuid "
                      "left join badgeuse.toptions o on o.uuid = ostu.toptionsUuid "
                      "where stu.uuid = UNHEX(?);");

        queryStudent.addBindValue(studentUuid);
        queryStudent.exec();

        if (queryStudent.next()) {
            ui->le_studentNumber->setText(queryStudent.value(0).toString());
            ui->le_lastname->setText(queryStudent.value(1).toString());
            ui->le_firstname->setText(queryStudent.value(2).toString());
            ui->le_mail->setText(queryStudent.value(3).toString());
            ui->sb_degreeYear->setValue(queryStudent.value(4).toInt());
            ui->cb_trainingName->setCurrentIndex(ui->cb_trainingName->findText(queryStudent.value(5).toString()));
            ui->sb_group->setValue(queryStudent.value(6).toInt());
//            ui->cb_optionName->setCurrentIndex(ui->cb_optionName->findText(queryStudent.value(7).toString()));
            ui->le_rfidNumber->setText(queryStudent.value(8).toByteArray().toHex().toUpper());
        } else {
            QMessageBox::critical(this, "Erreur", "Impossible de récupérer les données de l'étudiant.");
        }

    }



}

StudentsDialog::~StudentsDialog()
{
    delete ui;
}

QList<QString> StudentsDialog::getValues()
{
    QList<QString> inputValues  {
        ui->le_studentNumber->text(),
        ui->le_lastname->text(),
        ui->le_firstname->text(),
        ui->le_mail->text(),
        ui->sb_degreeYear->text(),
        ui->cb_trainingName->currentText(),
        ui->sb_group->text(),
//        ui->cb_optionName->currentText(),
        ui->le_rfidNumber->text()
    };
    return inputValues;
}

void StudentsDialog::updateOptions(const QString& value) {
    qDebug() << "Loading " + value;

    // INIT TRAINING
    QSqlQuery query;
    query.prepare("select o.name, o.uuid from badgeuse.toptions o "
                  "inner join badgeuse.training t on o.trainingUuid = t.uuid "
                  "where t.name like ?;");
    query.addBindValue(value);
    query.exec();

    _optionsList->clear();
    while (query.next()) {
        QString option = query.value(0).toString();
        _optionsList->addCheckItem(query.value(0).toString(), query.value(1).toByteArray().toHex(), Qt::CheckState::Unchecked);
    }

}


void StudentsDialog::accept()
{

    if (validateValues()) {

        QSqlQuery queryInsertStudent;
        queryInsertStudent.prepare("insert into badgeuse.students VALUES("
                                   "UNHEX(REPLACE(uuid(),'-','')), ?, ?, ?, ?, ?, (SELECT t.uuid from badgeuse.training t WHERE t.name like ? LIMIT 1), ?, UNHEX(?));");
        queryInsertStudent.addBindValue(ui->le_firstname->text());
        queryInsertStudent.addBindValue(ui->le_lastname->text());
        queryInsertStudent.addBindValue(ui->sb_degreeYear->value());
        queryInsertStudent.addBindValue(ui->le_studentNumber->text());
        queryInsertStudent.addBindValue(ui->le_mail->text());
        queryInsertStudent.addBindValue(ui->cb_trainingName->currentText());
        queryInsertStudent.addBindValue(ui->sb_group->value());
        queryInsertStudent.addBindValue(ui->le_rfidNumber->text());

        if(!queryInsertStudent.exec()) {
            qDebug() << "Error:" << queryInsertStudent.lastError().text() << ", Code:" << queryInsertStudent.lastError().number() << ", Type:" << queryInsertStudent.lastError().type();
            return;
        } else {
            qDebug() << ui->le_studentNumber->text() << " inserted.";
        }

        QString lastUuid = QString();
        QSqlQuery queryLastUuid("SELECT @last_uuid");
        if (queryLastUuid.next()) {
            lastUuid = queryLastUuid.value(0).toByteArray().toHex();
            qDebug() << "uuid trouvé !! " + lastUuid;
        } else {
            qDebug() << "No uuid found...";
            return;
        }


        QSqlQuery queryInsertStudentOptions;
        queryInsertStudentOptions.prepare("insert into badgeuse.rlToptionsStudents VALUES(UNHEX(?), UNHEX(?))");

        QVariantList uuids;
        for( int a = 0; a < _optionsList->getCheckedItemsData().length(); a++) {
          uuids << lastUuid;
       }

        queryInsertStudentOptions.addBindValue(uuids);
        queryInsertStudentOptions.addBindValue(_optionsList->getCheckedItemsData());
        if (!queryInsertStudentOptions.execBatch()) {
            qDebug() << "Error:" << queryInsertStudentOptions.lastError().text() << ", Code:" << queryInsertStudentOptions.lastError().number() << ", Type:" << queryInsertStudentOptions.lastError().type();
            return;
        } else {
            qDebug() << _optionsList->getCheckedItemsData() << " inserted.";
        }


        if (!queryInsertStudentOptions.execBatch()) {
            qDebug() << queryInsertStudentOptions.lastError();
            return;
        }


        QDialog::accept();
    }


}


bool StudentsDialog::validateValues() {

    QString error = QString("");


    if (ui->le_studentNumber->text().length() != 8) {
        error += "\n - La taille du numéro étudiant est incorrect";
    }
    QRegExp re("\\d*");  // a digit (\d), zero or more times (*)
    if (!re.exactMatch(ui->le_studentNumber->text())) {
        error += "\n - Le numéro étudiant doit être composé uniquement de chiffre";
    }

    if (ui->le_firstname->text().length() < 1) {
        error += "\n - Le champ 'Nom' doit être rempli";
    }
    if (ui->le_lastname->text().length() < 1) {
        error += "\n - Le champ 'Prénom' doit être rempli";
    }

    // CHECK MAIL
    // CHECK RFID IF ITS GOOD



    if (error.length()>0) {
        QMessageBox::critical(this, "Attention",
        "Certain champ ne sont pas correct : " + error,
        QMessageBox::Ok);
        return false;
    }

    return true;


}
