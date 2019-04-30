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
#include "cardreadermodel.h"
#include <QSettings>
#include <QApplication>

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
    CardReaderModel *getCardReaderModel();

    void reload();

private:


private:
    QSqlDatabase _db;
    PresencesModel *_presencesModel;
    StudentsModel *_studentsModel;
    OptionsModel *_optionsModel;
    TrainingModel *_trainingModel;
    CardReaderModel *_cardReaderModel;

    QSettings *_dbSettings;


};

#endif // BADGEUSEMODEL_H
