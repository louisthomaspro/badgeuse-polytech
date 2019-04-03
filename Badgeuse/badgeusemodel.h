#ifndef BADGEUSEMODEL_H
#define BADGEUSEMODEL_H

#include <QDebug>
#include <QSqlQuery>
#include <QTableView>
#include <QSqlRelationalTableModel>
#include <QSqlError>
#include "presencesmodel.h"

class BadgeuseModel : public QObject
{

    Q_OBJECT


public:
    BadgeuseModel(QObject* parent = nullptr);
    void initDbConnection();
    void initModels();
    PresencesModel *getPresencesModel();

private:


private:
    QSqlDatabase _db;
    PresencesModel *_presencesModel;

};

#endif // BADGEUSEMODEL_H
