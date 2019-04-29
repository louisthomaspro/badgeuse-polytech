#ifndef OPTIONSDIALOG_H
#define TRAININGDIALOG_H

#include <QDialog>
#include <QList>
#include <QSqlQuery>
#include <QDebug>
#include <QDate>
#include <QMessageBox>
#include <QSqlError>
#include <QListIterator>
#include "optionsmodel.h"
#include "qchecklist.h"
#include "ui_optionsdialog.h"


namespace Ui {
class OptionsDialog;
}

class OptionsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OptionsDialog(OptionsModel *optionsModel, QWidget *parent = nullptr, QString optionUuid = QString());
    ~OptionsDialog();


private slots:
    virtual void accept();
    bool validateValues();


private:
    Ui::OptionsDialog *ui;
    OptionsModel *_optionsModel;
    QString *_optionUuid;
};

#endif // PRESENCESDIALOG_H
