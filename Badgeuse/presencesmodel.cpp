#include "presencesmodel.h"

PresencesModel::PresencesModel(QObject* parent) : QSqlQueryModel(parent)
{

}

QVariant PresencesModel::data(const QModelIndex &index, int role) const
{
    QVariant value = QSqlQueryModel::data(index, role);
    if (value.isValid() && role == Qt::DisplayRole) {
        if (index.column() == 0)
            return value.toByteArray().toHex();
        else if (index.column() == 1)
            return value.toByteArray().toHex(':');
        else if (index.column() == 3)
            return value.toByteArray().toHex();
    }
    if (role == Qt::TextColorRole && index.column() == 1)
        return QVariant::fromValue(QColor(Qt::red));
    return value;
}

void PresencesModel::init()
{
    QSqlQuery query("SELECT * from scans");
    setQuery(query);
}


void PresencesModel::setQuery(const QSqlQuery &query) {
    QSqlQueryModel::setQuery(query);
}
