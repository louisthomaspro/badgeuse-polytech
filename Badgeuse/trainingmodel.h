#ifndef TRAININGMODEL_H
#define TRAININGMODEL_H

#include <QSqlQueryModel>
#include <QTableView>
#include <QSqlQuery>
#include <QSqlError>
#include <QtDebug>
#include <QMessageBox>
#include <QSqlRecord>
#include <QDateTime>
#include "utilities.h"

class TrainingModel : public QSqlQueryModel
{

    Q_OBJECT


public:
    enum ColumnIndex
    {
        UUID = 0,
        TRAINING = 1
    };


public:
    TrainingModel(QObject* parent = nullptr);

    QVariant data(const QModelIndex &item, int role) const override;

    void initModel();
    void reload();
    bool add(QString name);
    bool remove(QString uuid);
    bool modify(QString uuid, QString name);
    QMap<QString, QVariant> get(QString uuid);
    QList<QMap<QString, QVariant>> get();


protected:
    void setQuery(const QSqlQuery &query);
};


#endif // PRESENCEMODEL_H
