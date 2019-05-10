#ifndef OPTIONSMODEL_H
#define OPTIONSMODEL_H

#include <QSqlQueryModel>
#include <QTableView>
#include <QSqlQuery>
#include <QSqlError>
#include <QtDebug>
#include <QMessageBox>
#include <QSqlRecord>
#include <QDateTime>
#include "utilities.h"

class OptionsModel : public QSqlQueryModel
{

    Q_OBJECT


public:
    OptionsModel(QObject* parent = nullptr);

    QVariant data(const QModelIndex &item, int role) const override;

    void initModel();
    void reload();
    bool add(QString name, QString trainingUuid);
    bool remove(QString uuid);
    bool modify(QString uuid, QString name);
    QMap<QString, QVariant> get(QString uuid);
    QList<QMap<QString, QVariant>> getFromTraining(QString trainingUuid);
    QList<QMap<QString, QVariant>> getFromStudent(QString studentUuid);


protected:
    void setQuery(const QSqlQuery &query);
};


#endif // PRESENCEMODEL_H
