#ifndef PRESENCEMODEL_H
#define PRESENCEMODEL_H

#include <QSqlQueryModel>
#include <QTableView>
#include <QSqlQuery>

class PresencesModel : public QSqlQueryModel
{

    Q_OBJECT


public:
    PresencesModel(QObject* parent = nullptr);

    QVariant data(const QModelIndex &item, int role) const override;

    void init();


protected:
    void setQuery(const QSqlQuery &query);
};


#endif // PRESENCEMODEL_H
