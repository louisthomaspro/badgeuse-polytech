#include "utilities.h"

Utilities::Utilities()
{

}

QList<QMap<QString, QVariant>> Utilities::generateQListFromSql(QString &sql) {
    QSqlQuery query(sql);
    QList<QMap<QString, QVariant>> array = QList<QMap<QString, QVariant>>();

    while (query.next()) {
        QMap<QString, QVariant> item;
        for (int col = 0; col < query.record().count(); col++) { // foreach colmns
            item[query.record().fieldName(col)] = query.value(col);
        }
        array.insert(array.size(), item);
    }
    return array;
}



