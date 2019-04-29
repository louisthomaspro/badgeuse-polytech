#include "optionsdialog.h"

OptionsDialog::OptionsDialog(OptionsModel *optionsModel, QWidget *parent, QString optionUuid) :
    QDialog(parent),
    ui(new Ui::OptionsDialog)
{
    ui->setupUi(this);

    _optionsModel = optionsModel;
    _optionUuid = &optionUuid;

    // Connect
    connect(this, SIGNAL(accepted()), this, SLOT(validateValues()));

    if (!_optionUuid->isEmpty()) {
        ui->l_title->setText("Modification d'une option");

        QMap<QString, QVariant> info = _optionsModel->get(*_optionUuid);
        ui->le_name->setText(info["name"].toString());

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
            _optionsModel->modify(*_optionUuid, ui->le_name->text(), ui->cb_training->currentData().toString());
        }

        QDialog::accept();
    }
}


bool OptionsDialog::validateValues()
{
    QString error = QString("");

    // TODO

    if (error.length()>0) {
        QMessageBox::critical(this, "Attention",
        "Certain champ ne sont pas correct : " + error,
        QMessageBox::Ok);
        return false;
    }
    return true;
}
