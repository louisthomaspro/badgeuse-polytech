#ifndef PRESENCEMODEL_H
#define PRESENCEMODEL_H

#include <QSqlQueryModel>
#include <QTableView>
#include <QSqlQuery>
#include <QSqlError>
#include <QtDebug>
#include <QMessageBox>
#include <QSqlRecord>
#include <QDateTime>
#include "utilities.h"

class PresencesModel : public QSqlQueryModel
{

    Q_OBJECT

public:
    enum ColumnIndex
    {
        UUID = 0,
        RFIDNUMBER = 1,
        ENTRY = 2,
        EXIT = 3,
        CARDREADER = 4,
        STUDENTNUMBER = 5,
        FIRSTNAME = 6,
        LASTNAME = 7,
        PROMOTION = 8,
        TRAINING = 9,
        GROUPNUMBER = 10,
        OPTION = 11
    };



public:
    PresencesModel(QObject* parent = nullptr);

    QVariant data(const QModelIndex &item, int role) const override;

    void initModel();
    void reload();
    bool remove(QString uuid);
    bool add(QDateTime DateTimeEntry, QDateTime DateTimeExit, QString cardReaderUuid, QString studentUuid);
    bool modify(QString uuid, QDateTime DateTimeEntry, QDateTime DateTimeExit, QString cardReaderUuid, QString studentUuid);
    QMap<QString, QVariant> getPresence(QString uuid);
    QList<QMap<QString, QVariant>> getExport(QString studentUuid, QDateTime QDateTimeBegin, QDateTime QDateTimeEnd);


protected:
    void setQuery(const QSqlQuery &query);
};


#endif // PRESENCEMODEL_H
