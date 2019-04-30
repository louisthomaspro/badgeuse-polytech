#include "cardreadermodel.h"

CardReaderModel::CardReaderModel()
{

}


QList<QMap<QString, QVariant>> CardReaderModel::get() {
    QString sql = "select "
                  "cr.uuid, cr.information, cr.ip "
                  "from badgeuse.cardreaders cr;";
    return Utilities::generateQListFromSql(sql);
}
