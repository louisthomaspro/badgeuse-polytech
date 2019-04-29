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
    static QList<QMap<QString, QVariant>> getCardReaders();
    static QList<QMap<QString, QVariant>> getOptions(QString trainingUuid);
    static QList<QMap<QString, QVariant>> getTraining();

private:
    static QList<QMap<QString, QVariant>> generateQListFromSql(QString &sql);

};

#endif // UTILITIES_H
