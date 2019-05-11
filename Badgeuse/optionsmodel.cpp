#include "optionsmodel.h"

OptionsModel::OptionsModel(QObject* parent) : QSqlQueryModel(parent)
{

}

QVariant OptionsModel::data(const QModelIndex &index, int role) const
{
    QVariant value = QSqlQueryModel::data(index, role);
    if (value.isValid() && role == Qt::DisplayRole) {
        if (index.column() == UUID)
            return value.toByteArray().toHex();
    }
    return value;
}

void OptionsModel::initModel()
{
    QSqlQuery query("select o.uuid, t.name as 'Formation Parent', o.name as Options from badgeuse.training t "
                    "inner join badgeuse.toptions o on o.trainingUuid = t.uuid;");
    setQuery(query);
}

void OptionsModel::reload()
{
    initModel();
}

void OptionsModel::setQuery(const QSqlQuery &query)
{
    QSqlQueryModel::setQuery(query);
}


bool OptionsModel::add(QString name, QString trainingUuid)
{
    QSqlQuery insert;
    insert.prepare("insert into badgeuse.toptions VALUES("
                               "UNHEX(REPLACE(uuid(),'-','')), UNHEX(?), ?);");
    insert.addBindValue(trainingUuid);
    insert.addBindValue(name);

    return Utilities::exec(insert);
}

bool OptionsModel::remove(QString uuid)
{
    QSqlQuery remove;
    remove.prepare("delete from badgeuse.toptions where uuid = UNHEX(?)");
    remove.addBindValue(uuid);

    return Utilities::exec(remove);
}

bool OptionsModel::modify(QString uuid, QString name) {
    QSqlQuery modify;
    modify.prepare("update badgeuse.toptions set "
                               "name = ? "
                               "where uuid = UNHEX(?);");
    modify.addBindValue(name);
    modify.addBindValue(uuid);

    return Utilities::exec(modify);
}

QMap<QString, QVariant> OptionsModel::get(QString uuid)
{
    QSqlQuery select;
    select.prepare("select t.uuid, t.trainingUuid, t.name "
                            "from badgeuse.toptions t "
                            "where t.uuid = UNHEX(?);");
    select.addBindValue(uuid);

    return Utilities::generateQListFromSql(select).first();
}


QList<QMap<QString, QVariant>> OptionsModel::getFromTraining(QString trainingUuid)
{
    QSqlQuery select;
    select.prepare("select "
                  "o.uuid, o.name, o.trainingUuid, t.name as trainingName "
                  "from badgeuse.toptions o "
                  "inner join badgeuse.training t on t.uuid = o.trainingUuid "
                  "where o.trainingUuid = UNHEX(?);");
    select.addBindValue(trainingUuid);

    return Utilities::generateQListFromSql(select);
}


QList<QMap<QString, QVariant>> OptionsModel::getFromStudent(QString studentUuid) {
    QSqlQuery select;
    select.prepare("select o.uuid, o.name "
                                "from badgeuse.toptions o "
                                "inner join badgeuse.rlToptionsStudents rl on o.uuid = rl.toptionsUuid "
                                "where rl.studentsUuid = UNHEX(?);");
    select.addBindValue(studentUuid);

    return Utilities::generateQListFromSql(select);
}



