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
//        else if (index.column() == 1)
//            return value.toByteArray().toHex(':');
////        else if (index.column() == 4)
////            return value.toByteArray().toHex();
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

}

void OptionsModel::remove(QString uuid) {

}

void OptionsModel::modify(QString uuid, QString trainingUuid, QString name) {

}

QMap<QString, QVariant> OptionsModel::get(QString uuid) {

}



