#ifndef PRESENCESDIALOG_H
#define PRESENCESDIALOG_H

#include <QDialog>
#include <QList>
#include <QSqlQuery>
#include <QDebug>
#include <QDate>
#include <QMessageBox>
#include <QSqlError>
#include <QListIterator>
#include "presencesmodel.h"
#include "qchecklist.h"
#include "ui_presencesdialog.h"


namespace Ui {
class PresencesDialog;
}

class PresencesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PresencesDialog(PresencesModel *presenceModel, QWidget *parent = nullptr, QString presenceUuid = QString());
    ~PresencesDialog();


private slots:
    virtual void accept();
    bool validateValues();


private:
    Ui::PresencesDialog *ui;
    QList<QString> _values;
    QCheckList *_optionsList;
    PresencesModel *_presenceModel;
    QString *_presenceUuid;
};

#endif // PRESENCESDIALOG_H
