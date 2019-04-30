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
    return value;
}

void TrainingModel::initModel()
{
    QSqlQuery query("select t.uuid, t.name as Formations from badgeuse.training t;");
    setQuery(query);
}

void TrainingModel::reload()
{
    initModel();
}

void TrainingModel::setQuery(const QSqlQuery &query)
{
    QSqlQueryModel::setQuery(query);
}

bool TrainingModel::add(QString name)
{
    QSqlQuery insert;
    insert.prepare("insert into badgeuse.training VALUES(UNHEX(REPLACE(uuid(),'-','')), ?);");
    insert.addBindValue(name);

    return Utilities::exec(insert);
}

bool TrainingModel::remove(QString uuid)
{
    QSqlQuery remove;
    remove.prepare("delete from badgeuse.training where uuid = UNHEX(?)");
    remove.addBindValue(uuid);

    return Utilities::exec(remove);
}

bool TrainingModel::modify(QString uuid, QString name)
{
    QSqlQuery modify;
    modify.prepare("update badgeuse.training set "
                               "name = ? "
                               "where uuid = UNHEX(?);");
    modify.addBindValue(name);
    modify.addBindValue(uuid);

    return Utilities::exec(modify);
}

QMap<QString, QVariant> TrainingModel::get(QString uuid)
{
    QSqlQuery select;
    select.prepare("select t.uuid, t.name "
                            "from badgeuse.training t "
                            "where t.uuid = UNHEX(?);");

    select.addBindValue(uuid);

    return Utilities::generateQListFromSql(select).first();
}


QList<QMap<QString, QVariant>> TrainingModel::get()
{
    QSqlQuery select;
    select.prepare("select "
                  "t.uuid, t.name "
                  "from badgeuse.training t;");
    return Utilities::generateQListFromSql(select);
}


