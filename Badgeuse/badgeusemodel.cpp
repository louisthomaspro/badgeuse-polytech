#include "badgeusemodel.h"

BadgeuseModel::BadgeuseModel(QSettings &dbSettings, QObject* parent) : QObject(parent)
{

    _dbSettings = &dbSettings;

    initDbConnection();
    _presencesModel = new PresencesModel(this);
    _studentsModel = new StudentsModel(this);
    _trainingModel = new TrainingModel(this);
    _optionsModel = new OptionsModel(this);
    initModels();


}

bool BadgeuseModel::initDbConnection()
{

    QString host = _dbSettings->value("db_host", "").toString();
    int port = _dbSettings->value("db_port", "").toInt();
    QString dbname = _dbSettings->value("db_dbname", "").toString();
    QString user = _dbSettings->value("db_user", "").toString();
    QString password = _dbSettings->value("db_password", "").toString();


    _db = QSqlDatabase::addDatabase("QMYSQL");
    _db.setHostName(host);
    _db.setDatabaseName(dbname);
    _db.setUserName(user);
    _db.setPassword(password);
    _db.setPort(port);
    _db.setConnectOptions("MYSQL_OPT_CONNECT_TIMEOUT=4");

    if (!_db.open())
    {
        qDebug("Problème de connexion à la base de données");
        return false;
    }

    return true;


}
void BadgeuseModel::initModels()
{
    _presencesModel->initModel();
    _studentsModel->initModel();
    _optionsModel->initModel();
    _trainingModel->initModel();
}

PresencesModel* BadgeuseModel::getPresencesModel() { return _presencesModel; }
StudentsModel* BadgeuseModel::getStudentsModel() { return _studentsModel; }
OptionsModel* BadgeuseModel::getOptionsModel() { return _optionsModel; }
TrainingModel* BadgeuseModel::getTrainingModel() { return  _trainingModel; }


void BadgeuseModel::reload() {
    _presencesModel->reload();
    _studentsModel->reload();
    _optionsModel->reload();
    _trainingModel->reload();
}
