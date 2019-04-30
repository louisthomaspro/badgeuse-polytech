#include "utilities.h"

Utilities::Utilities()
{

}

QList<QMap<QString, QVariant>> Utilities::generateQListFromSql(QSqlQuery &query) {
    QList<QMap<QString, QVariant>> array = QList<QMap<QString, QVariant>>();
    if (query.exec()) {
        while (query.next()) {
            QMap<QString, QVariant> item;
            for (int col = 0; col < query.record().count(); col++) { // foreach colmns
                item[query.record().fieldName(col)] = query.value(col);
            }
            array.insert(array.size(), item);
        }
        return array;
    } else {
        qDebug() << "Error query " << query.lastError().text();
        return QList<QMap<QString, QVariant>>();
    }
}

bool Utilities::exec(QSqlQuery &query)
{
    if(!query.exec()) {
        qDebug() << "SqlError(" << query.lastError().nativeErrorCode() << "): " << query.lastError().text();
        return false;
    }
    return true;
}

QString Utilities::getLastUuid()
{
    QSqlQuery select("SELECT @last_uuid");
    if (select.first()) {
        return select.value(0).toByteArray().toHex();
    } else {
        qDebug() << "No last uuid found...";
        return QString();
    }
}


