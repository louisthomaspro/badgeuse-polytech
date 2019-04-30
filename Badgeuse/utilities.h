#ifndef UTILITIES_H
#define UTILITIES_H

#include <QList>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>
#include <QSqlError>
#include <QMessageBox>

class Utilities
{
public:
    Utilities();
    static QList<QMap<QString, QVariant>> generateQListFromSql(QSqlQuery &sql);
    static bool exec(QSqlQuery &query);

private:


};

#endif // UTILITIES_H
