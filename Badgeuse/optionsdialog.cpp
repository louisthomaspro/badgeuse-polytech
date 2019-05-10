#include "optionsdialog.h"

OptionsDialog::OptionsDialog(OptionsModel *optionsModel, TrainingModel *trainingModel, QWidget *parent, QString optionUuid) :
    QDialog(parent),
    ui(new Ui::OptionsDialog)
{
    ui->setupUi(this);

    _optionsModel = optionsModel;
    _trainingModel = trainingModel;
    _optionUuid = &optionUuid;


    // Connect
    connect(this, SIGNAL(accepted()), this, SLOT(validateValues()));


    // Fill training combobox
    ui->cb_training->clear();
    for (QMap<QString, QVariant> item : _trainingModel->get()) {
        ui->cb_training->addItem(item["name"].toString(), item["uuid"].toByteArray().toHex());
    }

    if (!_optionUuid->isEmpty()) {
        ui->l_title->setText("Modification d'une option");
        QMap<QString, QVariant> info = _optionsModel->get(*_optionUuid);
        ui->le_name->setText(info["name"].toString());
        ui->cb_training->setCurrentIndex(ui->cb_training->findData(info["trainingUuid"].toByteArray().toHex()));
        ui->cb_training->setDisabled(true);
    } else {
        ui->l_title->setText("Ajout d'une option");
    }

}

OptionsDialog::~OptionsDialog()
{
    delete ui;
}



void OptionsDialog::accept()
{
    if (validateValues()) {

        if (_optionUuid->isEmpty()) {
            _optionsModel->add(ui->le_name->text(), ui->cb_training->currentData().toString());
        } else {
            _optionsModel->modify(*_optionUuid, ui->le_name->text());
        }
        QDialog::accept();
    }
}


bool OptionsDialog::validateValues()
{
    QString error = QString("");

    if (ui->le_name->text().length() < 1) {
        error += "\n - Le champ 'Nom' doit être rempli.";
    }

    if (error.length()>0) {
        QMessageBox::critical(this, "Attention",
        "Certain champ ne sont pas correct : " + error,
        QMessageBox::Ok);
        return false;
    }
    return true;
}
