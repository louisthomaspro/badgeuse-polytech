#ifndef STUDENTSMODEL_H
#define STUDENTSMODEL_H


#include <QSqlQueryModel>
#include <QTableView>
#include <QSqlQuery>

class StudentsModel : public QSqlQueryModel
{

    Q_OBJECT


public:
    StudentsModel(QObject* parent = nullptr);

    QVariant data(const QModelIndex &item, int role) const override;

    void init();


protected:
    void setQuery(const QSqlQuery &query);
};

#endif // STUDENTSMODEL_H
