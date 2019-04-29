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



QList<QMap<QString, QVariant>> Utilities::getCardReaders() {
    QString sql = "select "
                  "cr.uuid, cr.information, cr.ip "
                  "from badgeuse.cardreaders cr;";
    return generateQListFromSql(sql);
}

QList<QMap<QString, QVariant>> Utilities::getOptions(QString trainingUuid) {
    QString sql = QString("select "
                  "o.uuid, o.name, o.trainingUuid, t.name as trainingName "
                  "from badgeuse.toptions o "
                  "inner join badgeuse.training t on t.uuid = o.trainingUuid "
                  "where o.trainingUuid = UNHEX('%1');").arg(trainingUuid);
    return generateQListFromSql(sql);
}

QList<QMap<QString, QVariant>> Utilities::getTraining() {
    QString sql = "select "
                  "t.uuid, t.name "
                  "from badgeuse.training t;";
    return generateQListFromSql(sql);
}
