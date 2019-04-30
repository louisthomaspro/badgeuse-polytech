#ifndef CARDREADERSMODEL_H
#define CARDREADERSMODEL_H

#include "utilities.h"
#include <QList>
#include <QMap>

class CardReadersModel
{
public:
    CardReadersModel();

    QList<QMap<QString, QVariant>> get();
};

#endif // CARDREADERSMODEL_H
