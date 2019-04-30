#ifndef STUDENTSMODEL_H
#define STUDENTSMODEL_H


#include <QSqlQueryModel>
#include <QTableView>
#include <QSqlQuery>
#include <QSqlError>
#include <QtDebug>
#include <QMessageBox>
#include <QSqlRecord>
#include "utilities.h"
#include "optionsmodel.h"

class StudentsModel : public QSqlQueryModel
{

    Q_OBJECT

public:
    enum ColumnIndex
    {
        UUID = 0,
        RFIDNUMBER = 1,
        STUDENTNUMBER = 2,
        FIRSTNAME = 3,
        LASTNAME = 4,
        PROMOTION = 5,
        MAIL = 6,
        TRAINING = 7,
        GROUPNUMBER = 8,
        OPTION = 9
    };

public:
    StudentsModel(OptionsModel &optionsModel, QObject* parent = nullptr);

    QVariant data(const QModelIndex &item, int role) const override;

    void initModel();
    void reload();
    bool addOptions(QString uuid, QStringList options);
    void updateOptions(const QString& value);
    bool remove(QString uuid);
    bool add(QString studentNumber, QString firstname, QString lastname, QString mail, int degreeYear, QString trainingUuid, int group, QString rfidNumber, QMap<QString, QVariant> options = QMap<QString, QVariant>());
    bool modify(QString uuid, QString studentNumber, QString firstname, QString lastname, QString mail, int degreeYear, QString trainingUuid, int group, QString rfidNumber, QMap<QString, QVariant> options = QMap<QString, QVariant>());
    QMap<QString, QVariant> getStudent(QString uuid);
    QList<QMap<QString, QVariant>> get();


private:
    OptionsModel *_optionsModel;

protected:
    void setQuery(const QSqlQuery &query);
};

#endif // STUDENTSMODEL_H
