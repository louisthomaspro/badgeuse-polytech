#ifndef UTILITIES_H
#define UTILITIES_H

#include <QList>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>

class Utilities
{
public:
    Utilities();
    static QList<QMap<QString, QVariant>> generateQListFromSql(QString &sql);

private:


};

#endif // UTILITIES_H
