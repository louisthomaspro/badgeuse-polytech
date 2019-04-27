#include <QList>
#include <QSqlQuery>
#include <QSqlRecord>

QList<QMap<QString, QVariant>> getCardreader() {
    QSqlQuery queryCardreaders("select "
                    "cr.uuid, cr.information, cr.ip "
                    "from badgeuse.cardreaders cr;");

    QList<QMap<QString, QVariant>> allCardreaders = QList<QMap<QString, QVariant>>();

    while (queryCardreaders.next()) {
        QMap<QString, QVariant> cardreader;
        for (int col = 0; col < queryCardreaders.record().count(); col++) { // foreach colmns
            cardreader[queryCardreaders.record().fieldName(col)] = queryCardreaders.value(col);
        }
        allCardreaders.append(cardreader);
    }

    return allCardreaders;

}
