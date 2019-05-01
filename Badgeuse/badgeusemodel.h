#ifndef BADGEUSEMODEL_H
#define BADGEUSEMODEL_H

#include <QDebug>
#include <QSqlQuery>
#include <QTableView>
#include <QSqlRelationalTableModel>
#include <QSqlError>
#include "presencesmodel.h"
#include "studentsmodel.h"
#include "optionsmodel.h"
#include "trainingmodel.h"
#include "cardreadersmodel.h"
#include <QSettings>
#include <QApplication>
#include "presencesfilterproxymodel.h"
#include "studentsfilterproxymodel.h"

class BadgeuseModel : public QObject
{

    Q_OBJECT


public:
    BadgeuseModel(QSettings &dbSettings, QObject* parent = nullptr);
    bool initDbConnection();
    void initModels();
    PresencesModel *getPresencesModel();
    StudentsModel *getStudentsModel();
    OptionsModel *getOptionsModel();
    TrainingModel *getTrainingModel();
    CardReadersModel *getCardReaderModel();

    PresencesFilterProxyModel* getFilterProxyPresencesModel();
    StudentsFilterProxyModel* getFilterProxyStudentsModel();

    void reload();

private:


private:
    QSqlDatabase *_db;
    PresencesModel *_presencesModel;
    StudentsModel *_studentsModel;
    OptionsModel *_optionsModel;
    TrainingModel *_trainingModel;
    CardReadersModel *_cardReaderModel;

    QSettings *_dbSettings;

    PresencesFilterProxyModel *_presencesFilterProxyModel;
    StudentsFilterProxyModel *_studentsFilterProxyModel;


};

#endif // BADGEUSEMODEL_H
