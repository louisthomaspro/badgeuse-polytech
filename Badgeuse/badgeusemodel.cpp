#include "badgeusemodel.h"

BadgeuseModel::BadgeuseModel(QTableView* parent)
{
    initDbConnection();
    _model = new QSqlRelationalTableModel(parent);
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
     _model->setTable("scans");

     // Populate the model:
     if (!_model->select()) {
         qDebug("Populate failed ");
         qDebug(_model->lastError().text().toStdString().c_str());
         return;
     }
}

QSqlRelationalTableModel* BadgeuseModel::getModel()
{
    return _model;
}
