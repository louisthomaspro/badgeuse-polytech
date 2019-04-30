#ifndef CARDREADERMODEL_H
#define CARDREADERMODEL_H

#include "utilities.h"
#include <QList>
#include <QMap>

class CardReaderModel
{
public:
    CardReaderModel();

    QList<QMap<QString, QVariant>> get();
};

#endif // CARDREADERMODEL_H
