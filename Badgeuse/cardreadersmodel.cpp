#include "cardreadersmodel.h"

CardReadersModel::CardReadersModel()
{

}


QList<QMap<QString, QVariant>> CardReadersModel::get()
{
    QSqlQuery query;
    query.prepare("select "
                  "cr.uuid, cr.information, cr.ip "
                  "from badgeuse.cardreaders cr;");
    return Utilities::generateQListFromSql(query);
}
