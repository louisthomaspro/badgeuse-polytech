#ifndef BADGEUSEMODEL_H
#define BADGEUSEMODEL_H

#include <QDebug>
#include <QSqlQuery>
#include <QTableView>
#include <QSqlRelationalTableModel>
#include <QSqlError>

class BadgeuseModel
{
public:
    BadgeuseModel(QTableView* parent);
    void initDbConnection();
    void initModels();
    QSqlRelationalTableModel *getModel();

private:


private:
    QSqlDatabase _db;
    QSqlRelationalTableModel *_model;

};

#endif // BADGEUSEMODEL_H
