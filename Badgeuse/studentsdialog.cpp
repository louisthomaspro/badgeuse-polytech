#include "studentsdialog.h"

StudentsDialog::StudentsDialog(StudentsModel *studentModel, TrainingModel *trainingModel, PresencesModel *presencesModel, OptionsModel *optionsModel, QWidget *parent, QString studentUuid) :
    QDialog(parent),
    ui(new Ui::StudentsDialog)
{
    ui->setupUi(this);

    _studentModel = studentModel;
    _trainingModel = trainingModel;
    _presencesModel = presencesModel;
    _optionsModel = optionsModel;
    _studentUuid = &studentUuid;

    // init QCheckList for options
    _optionsList = new QCheckList(this);
    ui->formLayout->replaceWidget(ui->l_optionsList, _optionsList);
    _optionsList->setTabOrder(ui->sb_group, _optionsList);
    delete ui->l_optionsList;


    // Connect
    connect(ui->cb_trainingName, SIGNAL(currentIndexChanged(const int&)), this, SLOT(updateOptions(const int&)));
    connect(this, SIGNAL(accepted()), this, SLOT(validateValues()));


    // Fill training combobox
    ui->cb_trainingName->clear();
    for (QMap<QString, QVariant> item : _trainingModel->get()) {
        ui->cb_trainingName->addItem(item["name"].toString(), item["uuid"].toByteArray().toHex());
    }

    // Set default degreeYear
    ui->sb_degreeYear->setValue(QDate::currentDate().year()+3);


    // Set last alone rfidNumber
    QList<QMap<QString, QVariant>> aloneRfid = _presencesModel->getLastAloneRfid();
    for (QMap<QString, QVariant> item : aloneRfid) {
        ui->cb_rfidNumber->addItem(item["rfidNumber"].toByteArray().toHex(':') + " (Entrée: " + item["dateTimeEntry"].toDateTime().toString(Qt::LocalDate) + ")" , item["rfidNumber"].toByteArray().toHex());
    }


    if (!_studentUuid->isEmpty()) {

        ui->l_title->setText("Modification d'un étudiant");

        QMap<QString, QVariant> studentInfo = _studentModel->getStudent(*_studentUuid);

        ui->le_studentNumber->setText(studentInfo["studentNumber"].toString());
        ui->le_firstname->setText(studentInfo["firstname"].toString());
        ui->le_lastname->setText(studentInfo["lastname"].toString());
        ui->le_mail->setText(studentInfo["mail"].toString());
        ui->sb_degreeYear->setValue(studentInfo["degreeYear"].toInt());
        ui->cb_trainingName->setCurrentText(studentInfo["trainingName"].toString());
        ui->sb_group->setValue(studentInfo["group"].toInt());

        if (studentInfo["rfidNumber"].toByteArray().toHex().isEmpty()) {
            ui->cb_rfidNumber->insertItem(0, "");
            ui->cb_rfidNumber->setCurrentIndex(0);
        } else {
            ui->cb_rfidNumber->insertItem(
                        0,
                        studentInfo["rfidNumber"].toByteArray().toHex() + "(rfid actuel)",
                        studentInfo["rfidNumber"].toByteArray().toHex()
                        );
            ui->cb_rfidNumber->setCurrentIndex(0);
        }

        // Check options
        for(QVariant item: (studentInfo["options"].toList())) {
            _optionsList->setCheckStateByData(item.toMap()["uuid"].toByteArray().toHex(), Qt::CheckState::Checked);
        }

    } else {
        ui->l_title->setText("Ajout d'un étudiant");
        ui->cb_rfidNumber->insertItem(0, "");
        ui->cb_rfidNumber->setCurrentIndex(0);
        if (aloneRfid.size() == 0) {
            QMessageBox::critical(this, "Attention",
            "Aucun rfid libre disponible pour créer un nouvel étudiant.",
            QMessageBox::Ok);
            QMetaObject::invokeMethod(this, "close", Qt::QueuedConnection);
        }
    }

}


StudentsDialog::~StudentsDialog()
{
    delete ui;
}


void StudentsDialog::updateOptions(const int& index) {

    // update options combobox
    _optionsList->clear();
    for (QMap<QString, QVariant> item : _optionsModel->getFromTraining(ui->cb_trainingName->itemData(index).toString())) {
        _optionsList->addCheckItem(item["name"].toString(), item["uuid"].toByteArray().toHex(), Qt::CheckState::Unchecked);
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
                        ui->cb_trainingName->currentData().toString(),
                        ui->sb_group->value(),
                        ui->cb_rfidNumber->currentData().toString(),
                        _optionsList->getCheckedItems());
        } else {
            _studentModel->modify(
                        *_studentUuid,
                        ui->le_studentNumber->text(),
                        ui->le_firstname->text(),
                        ui->le_lastname->text(),
                        ui->le_mail->text(),
                        ui->sb_degreeYear->value(),
                        ui->cb_trainingName->currentData().toString(),
                        ui->sb_group->value(),
                        ui->cb_rfidNumber->currentData().toString(),
                        _optionsList->getCheckedItems());
        }
        QDialog::accept();
    }
}


bool StudentsDialog::validateValues() {

    QString error = QString("");


    if (ui->le_studentNumber->text().length() != 8) {
        error += "\n - La taille du numéro étudiant est incorrect.";
    }
    QRegExp digitREX("\\d*");  // a digit (\d), zero or more times (*)
    if (!digitREX.exactMatch(ui->le_studentNumber->text())) {
        error += "\n - Le numéro étudiant doit être composé uniquement de chiffre.";
    }

    if (ui->le_firstname->text().length() < 1) {
        error += "\n - Le champ 'Nom' doit être rempli.";
    }
    if (ui->le_lastname->text().length() < 1) {
        error += "\n - Le champ 'Prénom' doit être rempli.";
    }

    QRegExp mailREX("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b");
    mailREX.setCaseSensitivity(Qt::CaseInsensitive);
    mailREX.setPatternSyntax(QRegExp::RegExp);
    if (!mailREX.exactMatch(ui->le_mail->text())) {
        error += "\n - L'adresse mail est incorrect.";
    }


    if (error.length()>0) {
        QMessageBox::critical(this, "Attention",
        "Certain champ ne sont pas correct : " + error,
        QMessageBox::Ok);
        return false;
    }

    return true;


}
