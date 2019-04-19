#include "studentsdialog.h"
#include "ui_studentsdialog.h"

StudentsDialog::StudentsDialog(StudentsModel *studentModel, QWidget *parent, QString studentUuid) :
    QDialog(parent),
    ui(new Ui::StudentsDialog)
{
    ui->setupUi(this);

    _studentModel = studentModel;
    _studentUuid = &studentUuid;

    // init QCheckList for options
    _optionsList = new QCheckList(this);
    ui->formLayout->replaceWidget(ui->l_optionsList, _optionsList);
    _optionsList->setTabOrder(ui->sb_group, _optionsList);


    // Connect
    connect(ui->cb_trainingName, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(updateOptions(const QString&)));
    connect(this, SIGNAL(accepted()), this, SLOT(validateValues()));



    // Init training combobox
    QSqlQuery queryTraining("select t.name, t.uuid from badgeuse.training t;");
    while (queryTraining.next()) {
        QString training = queryTraining.value(0).toString();
        ui->cb_trainingName->addItem(training);
    }

    // Set default degreeYear
    ui->sb_degreeYear->setValue(QDate::currentDate().year()+3);


    if (_studentUuid->isEmpty()) {

        // Set last alone rfidNumber
        QSqlQuery queryRfid("SELECT "
                            "DISTINCT s.rfidNumber "
                            "FROM badgeuse.scans s "
                            "WHERE s.studentUuid IS NULL "
                            "order by s.DateTimeExit desc, s.dateTimeEntry desc limit 1;");

        if (queryRfid.first()) {
            ui->le_rfidNumber->setText(queryRfid.value(0).toByteArray().toHex().toUpper());
        } else {
            ui->le_rfidNumber->setText("No rfid found");
        }



    } else { // uuid found


        qDebug() << "Loading uuid " + *_studentUuid;

        QMap<QString, QVariant> studentInfo = _studentModel->getStudent(*_studentUuid);

        ui->le_studentNumber->setText(studentInfo["studentNumber"].toString());
        ui->le_firstname->setText(studentInfo["firstname"].toString());
        ui->le_lastname->setText(studentInfo["lastname"].toString());
        ui->le_mail->setText(studentInfo["mail"].toString());
        ui->sb_degreeYear->setValue(studentInfo["degreeYear"].toInt());
        ui->cb_trainingName->setCurrentIndex(ui->cb_trainingName->findText(studentInfo["trainingName"].toString()));
        ui->sb_group->setValue(studentInfo["group"].toInt());
        ui->le_rfidNumber->setText(studentInfo["rfidNumber"].toByteArray().toHex().toUpper());

        // Check options
        for(QString s: (studentInfo["options"].toMap()["optionsName"]).toStringList()) {
            _optionsList->setCheckStateByText(s, Qt::CheckState::Checked);
        }

    }



}

StudentsDialog::~StudentsDialog()
{
    delete ui;
}


void StudentsDialog::updateOptions(const QString& value) {
    qDebug() << "Loading " + value;

    // INIT TRAINING
    QSqlQuery query;
    query.prepare("select o.uuid, o.name from badgeuse.toptions o "
                  "inner join badgeuse.training t on o.trainingUuid = t.uuid "
                  "where t.name like ?;");
    query.addBindValue(value);
    query.exec();

    _optionsList->clear();
    while (query.next()) {
        _optionsList->addCheckItem(query.value(1).toString(), query.value(0).toByteArray().toHex(), Qt::CheckState::Unchecked);
    }

}


void StudentsDialog::accept()
{

    if (validateValues()) {

        if (_studentUuid->isEmpty()) {
            _studentModel->add(
                        ui->le_studentNumber->text(),
                        ui->le_firstname->text(),
                        ui->le_lastname->text(),
                        ui->le_mail->text(),
                        ui->sb_degreeYear->value(),
                        ui->cb_trainingName->currentText(),
                        ui->sb_group->value(),
                        ui->le_rfidNumber->text(),
                        _optionsList->getCheckedItems());
        } else {
            _studentModel->modify(
                        *_studentUuid,
                        ui->le_studentNumber->text(),
                        ui->le_firstname->text(),
                        ui->le_lastname->text(),
                        ui->le_mail->text(),
                        ui->sb_degreeYear->value(),
                        ui->cb_trainingName->currentText(),
                        ui->sb_group->value(),
                        ui->le_rfidNumber->text(),
                        _optionsList->getCheckedItems());
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