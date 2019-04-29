#ifndef TRAININGDIALOG_H
#define TRAININGDIALOG_H

#include <QDialog>
#include <QList>
#include <QSqlQuery>
#include <QDebug>
#include <QDate>
#include <QMessageBox>
#include <QSqlError>
#include <QListIterator>
#include "trainingmodel.h"
#include "qchecklist.h"
#include "ui_trainingdialog.h"


namespace Ui {
class TrainingDialog;
}

class TrainingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TrainingDialog(TrainingModel *trainingModel, QWidget *parent = nullptr, QString trainingUuid = QString());
    ~TrainingDialog();


private slots:
    virtual void accept();
    bool validateValues();


private:
    Ui::TrainingDialog *ui;
    TrainingModel *_trainingModel;
    QString *_trainingUuid;
};

#endif // PRESENCESDIALOG_H
