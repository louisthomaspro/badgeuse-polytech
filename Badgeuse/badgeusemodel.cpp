#include "badgeusemodel.h"

BadgeuseModel::BadgeuseModel(QSettings &dbSettings, QObject* parent) : QObject(parent)
{

    _dbSettings = &dbSettings;

    _db = new QSqlDatabase(QSqlDatabase::addDatabase("QMYSQL"));
    initDbConnection();

    _presencesFilterProxyModel = new PresencesFilterProxyModel(this);
    _studentsFilterProxyModel = new StudentsFilterProxyModel(this);

    _presencesModel = new PresencesModel(this);
    _optionsModel = new OptionsModel(this);
    _studentsModel = new StudentsModel(*_optionsModel, this);
    _trainingModel = new TrainingModel(this);
    initModels();


}

bool BadgeuseModel::initDbConnection()
{

    QString host = _dbSettings->value("db_host", "").toString();
    int port = _dbSettings->value("db_port", "").toInt();
    QString dbname = _dbSettings->value("db_dbname", "").toString();
    QString user = _dbSettings->value("db_user", "").toString();
    QString password = _dbSettings->value("db_password", "").toString();

    _db->setHostName(host);
    _db->setDatabaseName(dbname);
    _db->setUserName(user);
    _db->setPassword(password);
    _db->setPort(port);
    _db->setConnectOptions("MYSQL_OPT_CONNECT_TIMEOUT=4");

    if (!_db->open())
    {
        qDebug("Problème de connexion à la base de données");
        return false;
    }

    return true;


}
void BadgeuseModel::initModels()
{

    _presencesFilterProxyModel->setSourceModel(_presencesModel);
    _studentsFilterProxyModel->setSourceModel(_studentsModel);

    _presencesModel->initModel();
    _studentsModel->initModel();
    _optionsModel->initModel();
    _trainingModel->initModel();
}

PresencesModel* BadgeuseModel::getPresencesModel() { return _presencesModel; }
StudentsModel* BadgeuseModel::getStudentsModel() { return _studentsModel; }
PresencesFilterProxyModel* BadgeuseModel::getFilterProxyPresencesModel() { return _presencesFilterProxyModel; }
StudentsFilterProxyModel* BadgeuseModel::getFilterProxyStudentsModel() { return _studentsFilterProxyModel; }

OptionsModel* BadgeuseModel::getOptionsModel() { return _optionsModel; }
TrainingModel* BadgeuseModel::getTrainingModel() { return  _trainingModel; }
CardReadersModel* BadgeuseModel::getCardReaderModel() { return  _cardReaderModel; }


void BadgeuseModel::reload() {
    _presencesModel->reload();
    _studentsModel->reload();
    _optionsModel->reload();
    _trainingModel->reload();
}
