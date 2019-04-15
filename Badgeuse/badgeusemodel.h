#ifndef BADGEUSEMODEL_H
#define BADGEUSEMODEL_H

#include <QDebug>
#include <QSqlQuery>
#include <QTableView>
#include <QSqlRelationalTableModel>
#include <QSqlError>
#include "presencesmodel.h"
#include "studentsmodel.h"

class BadgeuseModel : public QObject
{

    Q_OBJECT


public:
    BadgeuseModel(QObject* parent = nullptr);
    void initDbConnection();
    void initModels();
    PresencesModel *getPresencesModel();
    StudentsModel *getStudentsModel();

private:


private:
    QSqlDatabase _db;
    PresencesModel *_presencesModel;
    StudentsModel *_studentsModel;


};

#endif // BADGEUSEMODEL_H
