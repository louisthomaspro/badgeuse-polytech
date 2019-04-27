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
