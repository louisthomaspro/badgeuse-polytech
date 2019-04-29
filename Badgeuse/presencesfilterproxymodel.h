#ifndef PRESENCESFILTERPROXYMODEL_H
#define PRESENCESFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>
#include "presencesmodel.h"


class PresencesFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit PresencesFilterProxyModel(QObject *parent = nullptr);
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const  override;
public slots:
    void setFirstNameFilter(const QString& regExp);
    void setLastNameFilter(const QString& regExp);
private:
    QRegExp _firstNameRegExp;
    QRegExp _lastNameRegExp;
};

#endif // PRESENCEFILTERPROXYMODEL_H
