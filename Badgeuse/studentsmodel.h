#ifndef STUDENTSMODEL_H
#define STUDENTSMODEL_H


#include <QSqlQueryModel>
#include <QTableView>
#include <QSqlQuery>
#include <QSqlError>
#include <QtDebug>
#include <QMessageBox>
#include <QSqlRecord>

class StudentsModel : public QSqlQueryModel
{

    Q_OBJECT


public:
    StudentsModel(QObject* parent = nullptr);

    QVariant data(const QModelIndex &item, int role) const override;

    void initModel();
    void reload();
    void addOptions(QString uuid, QStringList options);
    void updateOptions(const QString& value);
    void remove(QString uuid);
    void add(QString studentNumber, QString firstname, QString lastname, QString mail, int degreeYear, QString trainingUuid, int group, QString rfidNumber, QMap<QString, QVariant> options = QMap<QString, QVariant>());
    void modify(QString uuid, QString studentNumber, QString firstname, QString lastname, QString mail, int degreeYear, QString trainingUuid, int group, QString rfidNumber, QMap<QString, QVariant> options = QMap<QString, QVariant>());
    QMap<QString, QVariant> getStudent(QString uuid);


protected:
    void setQuery(const QSqlQuery &query);
};

#endif // STUDENTSMODEL_H
