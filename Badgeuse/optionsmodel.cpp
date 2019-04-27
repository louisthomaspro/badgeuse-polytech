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
        else if (index.column() == 1)
            return value.toByteArray().toHex(':');
//        else if (index.column() == 4)
//            return value.toByteArray().toHex();
    }
    if (role == Qt::TextColorRole && index.column() == 1)
        return QVariant::fromValue(QColor(Qt::red));
    return value;
}

void OptionsModel::initModel()
{
    QSqlQuery query("");
    setQuery(query);
}

void OptionsModel::reload() {
    initModel();
}

void OptionsModel::setQuery(const QSqlQuery &query) {
    QSqlQueryModel::setQuery(query);
}



