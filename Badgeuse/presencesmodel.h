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
    void remove(QString uuid);
    void add(uint DateTimeEntry, uint DateTimeExit, QString cardReaderUuid, QString studentUuid);
    void modify(QString uuid, uint DateTimeEntry, uint DateTimeExit, QString cardReaderUuid, QString studentUuid);
    QMap<QString, QVariant> getPresence(QString uuid);


protected:
    void setQuery(const QSqlQuery &query);
};


#endif // PRESENCEMODEL_H
