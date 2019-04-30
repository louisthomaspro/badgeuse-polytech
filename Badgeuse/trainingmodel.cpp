#include "trainingmodel.h"

TrainingModel::TrainingModel(QObject* parent) : QSqlQueryModel(parent)
{

}

QVariant TrainingModel::data(const QModelIndex &index, int role) const
{
    QVariant value = QSqlQueryModel::data(index, role);
    if (value.isValid() && role == Qt::DisplayRole) {
        if (index.column() == 0)
            return value.toByteArray().toHex();
    }
    if (role == Qt::TextColorRole && index.column() == 1)
        return QVariant::fromValue(QColor(Qt::red));
    return value;
}

void TrainingModel::initModel()
{
    QSqlQuery query("select t.uuid, t.name as Formations from badgeuse.training t;");
    setQuery(query);
}

void TrainingModel::reload() {
    initModel();
}

void TrainingModel::setQuery(const QSqlQuery &query) {
    QSqlQueryModel::setQuery(query);
}

void TrainingModel::add(QString name) {
    QSqlQuery queryTrainingInsert("insert into badgeuse.training VALUES("
                               "UNHEX(REPLACE(uuid(),'-','')), ?);");
    queryTrainingInsert.addBindValue(name);

    if(!queryTrainingInsert.exec()) {
        qDebug() << "SqlError: " << queryTrainingInsert.lastError().text();
        return;
    }
}

void TrainingModel::remove(QString uuid) {
    QSqlQuery queryTrainingDelete("delete from badgeuse.training where uuid = UNHEX(?)");
    queryTrainingDelete.addBindValue(uuid);

    if(!queryTrainingDelete.exec()) {
        qDebug() << "SqlError: " << queryTrainingDelete.lastError().text();
        return;
    }
}

void TrainingModel::modify(QString uuid, QString name) {
    QSqlQuery queryTrainingModify("update badgeuse.training set "
                               "name = ? "
                               "where uuid = UNHEX(?);");
    queryTrainingModify.addBindValue(name);
    queryTrainingModify.addBindValue(uuid);

    if(!queryTrainingModify.exec()) {
        qDebug() << "SqlError: " << queryTrainingModify.lastError().text();
        return;
    }
}

QMap<QString, QVariant> TrainingModel::get(QString uuid) {
    QSqlQuery queryTraining("select t.uuid, t.name "
                            "from badgeuse.training t "
                            "where t.uuid = UNHEX(?);");

    queryTraining.addBindValue(uuid);
    queryTraining.exec();

    QMap<QString, QVariant> trainingInfo;


    if (queryTraining.first()) {
        for (int col = 0; col < queryTraining.record().count(); col++) { // foreach colmns
            trainingInfo[queryTraining.record().fieldName(col)] = queryTraining.value(col);
        }
    } else {
        qDebug() << "Error queryTraining of uuid " << uuid << ".";
        return  QMap<QString, QVariant>();
    }

    return trainingInfo;
}


QList<QMap<QString, QVariant>> TrainingModel::get() {
    QSqlQuery query("select "
                  "t.uuid, t.name "
                  "from badgeuse.training t;");
    return Utilities::generateQListFromSql(query);
}


