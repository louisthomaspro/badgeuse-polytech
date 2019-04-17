#ifndef STUDENTSDIALOG_H
#define STUDENTSDIALOG_H

#include <QDialog>
#include <QList>
#include <QSqlQuery>
#include <QDebug>
#include <QDate>
#include <QMessageBox>


namespace Ui {
class StudentsDialog;
}

class StudentsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StudentsDialog(QWidget *parent = nullptr, QString studentUuid = QString());
    ~StudentsDialog();

    QList<QString> getValues();


private slots:
    virtual void accept();
    bool validateValues();
    void updateOptions(const QString& value);


private:
    Ui::StudentsDialog *ui;
    QList<QString> _values;
};

#endif // STUDENTSDIALOG_H
