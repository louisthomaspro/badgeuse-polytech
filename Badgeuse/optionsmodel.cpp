#include "optionsmodel.h"

OptionsModel::OptionsModel(QObject* parent) : QSqlQueryModel(parent)
{

}

QVariant OptionsModel::data(const QModelIndex &index, int role) const
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

void OptionsModel::initModel()
{
    QSqlQuery query("select o.uuid, CONCAT(t.name, \" > \", o.name) as Options from badgeuse.training t "
                    "inner join badgeuse.toptions o on o.trainingUuid = t.uuid;"
);
    setQuery(query);
}

void OptionsModel::reload() {
    initModel();
}

void OptionsModel::setQuery(const QSqlQuery &query) {
    QSqlQueryModel::setQuery(query);
}


void OptionsModel::add(QString name, QString trainingUuid) {
    QSqlQuery insert("insert into badgeuse.toptions VALUES("
                               "UNHEX(REPLACE(uuid(),'-','')), UNHEX(?), ?);");
    insert.addBindValue(trainingUuid);
    insert.addBindValue(name);

    if(!insert.exec()) {
        qDebug() << "SqlError: " << insert.lastError().text();
        return;
    }
}

void OptionsModel::remove(QString uuid) {
    QSqlQuery remove("delete from badgeuse.toptions where uuid = UNHEX(?)");
    remove.addBindValue(uuid);

    if(!remove.exec()) {
        qDebug() << "SqlError: " << remove.lastError().text();
        return;
    }
}

void OptionsModel::modify(QString uuid, QString name, QString trainingUuid) {
    QSqlQuery modify("update badgeuse.toptions set "
                               "trainingUuid = UNHEX(?), "
                               "name = ? "
                               "where uuid = UNHEX(?);");
    modify.addBindValue(trainingUuid);
    modify.addBindValue(name);
    modify.addBindValue(uuid);

    if(!modify.exec()) {
        qDebug() << "SqlError: " << modify.lastError().text();
        return;
    }
}

QMap<QString, QVariant> OptionsModel::get(QString uuid) {
    QSqlQuery select("select t.uuid, t.trainingUuid, t.name "
                            "from badgeuse.toptions t "
                            "where t.uuid = UNHEX(?);");
    select.addBindValue(uuid);
    select.exec();

    QMap<QString, QVariant> info;

    if (select.first()) {
        for (int col = 0; col < select.record().count(); col++) { // foreach colmns
            info[select.record().fieldName(col)] = select.value(col);
        }
    } else {
        qDebug() << "Error select of uuid " << uuid << ".";
        return  QMap<QString, QVariant>();
    }
    return info;
}


QList<QMap<QString, QVariant>> OptionsModel::getFromTraining(QString trainingUuid) {
    QSqlQuery query("select "
                  "o.uuid, o.name, o.trainingUuid, t.name as trainingName "
                  "from badgeuse.toptions o "
                  "inner join badgeuse.training t on t.uuid = o.trainingUuid "
                  "where o.trainingUuid = UNHEX(?);");
    query.addBindValue(trainingUuid);
    return Utilities::generateQListFromSql(query);
}

