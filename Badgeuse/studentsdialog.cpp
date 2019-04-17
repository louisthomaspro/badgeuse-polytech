#include "studentsdialog.h"
#include "ui_studentsdialog.h"

StudentsDialog::StudentsDialog(QWidget *parent, QString studentUuid) :
    QDialog(parent),
    ui(new Ui::StudentsDialog)
{
    ui->setupUi(this);

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
        queryStudent.prepare("select stu.studentNumber, stu.lastname, stu.firstname, stu.degreeYear, t.name, stu.`group`, o.name, stu.rfidNumber  from badgeuse.students stu "
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
            ui->sb_degreeYear->setValue(queryStudent.value(3).toInt());
            ui->cb_trainingName->setCurrentIndex(ui->cb_trainingName->findText(queryStudent.value(4).toString()));
            ui->sb_group->setValue(queryStudent.value(5).toInt());
            ui->cb_optionName->setCurrentIndex(ui->cb_optionName->findText(queryStudent.value(6).toString()));
            ui->le_rfidNumber->setText(queryStudent.value(7).toByteArray().toHex().toUpper());
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
        ui->sb_degreeYear->text(),
        ui->cb_trainingName->currentText(),
        ui->sb_group->text(),
        ui->cb_optionName->currentText(),
        ui->le_rfidNumber->text()
    };
    return inputValues;
}

void StudentsDialog::updateOptions(const QString& value) {
    qDebug() << "Loading " + value;

    // INIT TRAINING
    QSqlQuery query;
    query.prepare("select o.name from badgeuse.toptions o "
                  "inner join badgeuse.training t on o.trainingUuid = t.uuid "
                  "where t.name like ?;");
    query.addBindValue(value);
    query.exec();

    ui->cb_optionName->clear();
    while (query.next()) {
        QString option = query.value(0).toString();
        qDebug() << option;
        ui->cb_optionName->addItem(option);
    }
    ui->cb_optionName->addItem("");
}


void StudentsDialog::accept()
{

    if (validateValues()) {


//        try insert in database


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



    if (error.length()>0) {
        QMessageBox::critical(this, "Attention",
        "Certain champ ne sont pas correct : " + error,
        QMessageBox::Ok);
        return false;
    }

    return true;


}
