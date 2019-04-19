#include "badgeusemodel.h"

BadgeuseModel::BadgeuseModel(QObject* parent) : QObject(parent)
{
    initDbConnection();
    _presencesModel = new PresencesModel(this);
    _studentsModel = new StudentsModel(this);
    initModels();
}

void BadgeuseModel::initDbConnection()
{
    _db = QSqlDatabase::addDatabase("QMYSQL");
    _db.setHostName("localhost");
    _db.setDatabaseName("badgeuse");
    _db.setUserName("root");
    _db.setPassword("root");
    _db.setPort(3306);
    _db.setConnectOptions("MYSQL_OPT_CONNECT_TIMEOUT=4");

    if (!_db.open())
    {
        qDebug("Problème de connexion à la base de données");
    }
}
void BadgeuseModel::initModels()
{
    _presencesModel->initModel();
    _studentsModel->initModel();
    // init view
}

PresencesModel* BadgeuseModel::getPresencesModel() { return _presencesModel; }
StudentsModel* BadgeuseModel::getStudentsModel() { return _studentsModel; }
