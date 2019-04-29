#include "trainingdialog.h"

TrainingDialog::TrainingDialog(TrainingModel *trainingModel, QWidget *parent, QString trainingUuid) :
    QDialog(parent),
    ui(new Ui::TrainingDialog)
{
    ui->setupUi(this);

    _trainingModel = trainingModel;
    _trainingUuid = &trainingUuid;

    // Connect
    connect(this, SIGNAL(accepted()), this, SLOT(validateValues()));

    if (!_trainingUuid->isEmpty()) {
        ui->l_title->setText("Modification d'une formation");

        QMap<QString, QVariant> info = _trainingModel->get(*_trainingUuid);
        ui->le_name->setText(info["name"].toString());

    } else {
        ui->l_title->setText("Ajout d'une formation");
    }

}

TrainingDialog::~TrainingDialog()
{
    delete ui;
}



void TrainingDialog::accept()
{
    if (validateValues()) {

        if (_trainingUuid->isEmpty()) {
            _trainingModel->add(ui->le_name->text());
        } else {
            _trainingModel->modify(*_trainingUuid, ui->le_name->text());
        }

        QDialog::accept();
    }
}


bool TrainingDialog::validateValues()
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
