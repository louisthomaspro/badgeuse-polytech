#include "cardreadermodel.h"

CardReaderModel::CardReaderModel()
{

}


QList<QMap<QString, QVariant>> CardReaderModel::get() {
    QSqlQuery query;
    query.prepare("select "
                  "cr.uuid, cr.information, cr.ip "
                  "from badgeuse.cardreaders cr;");
    return Utilities::generateQListFromSql(query);
}
