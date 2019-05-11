#include "badgeusemodel.h"

BadgeuseModel::BadgeuseModel(QSettings &dbSettings, QObject* parent) : QObject(parent)
{

    _dbSettings = &dbSettings; // retrieve settings information

    _db = new QSqlDatabase(QSqlDatabase::addDatabase("QMYSQL")); // Init database object here to not have "duplicate connection name"
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

    // Retrieve information stored in QSettings
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
    _db->setConnectOptions("MYSQL_OPT_RECONNECT");

    if (!_db->open())
    {
        QMessageBox::critical(static_cast<QWidget*>(parent()), "Attention", "Impossible de se connecter à la base de données.\nParamètrez votre connexion dans 'Paramètre > Base de données'.", QMessageBox::Ok);
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


PresencesFilterProxyModel* BadgeuseModel::getFilterProxyPresencesModel()
{
    return _presencesFilterProxyModel;
}
StudentsFilterProxyModel* BadgeuseModel::getFilterProxyStudentsModel()
{
    return _studentsFilterProxyModel;
}


PresencesModel* BadgeuseModel::getPresencesModel()
{
    return _presencesModel;
}
StudentsModel* BadgeuseModel::getStudentsModel() {
    return _studentsModel;
}
OptionsModel* BadgeuseModel::getOptionsModel()
{
    return _optionsModel;
}
TrainingModel* BadgeuseModel::getTrainingModel()
{
    return  _trainingModel;
}
CardReadersModel* BadgeuseModel::getCardReaderModel()
{
    return  _cardReaderModel;
}


void BadgeuseModel::reload()
{
    _presencesModel->reload();
    _studentsModel->reload();
    _optionsModel->reload();
    _trainingModel->reload();
}
