#include "presencefilterproxymodel.h"

PresenceFilterProxyModel::PresenceFilterProxyModel(QObject *parent) : QSortFilterProxyModel(parent)
{
    _firstNameRegExp.setCaseSensitivity(Qt::CaseInsensitive);
    _lastNameRegExp.setCaseSensitivity(Qt::CaseInsensitive);
    _firstNameRegExp.setPatternSyntax(QRegExp::RegExp);
    _lastNameRegExp.setPatternSyntax(QRegExp::RegExp);
}
bool PresenceFilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    QModelIndex firstNameIndex = sourceModel()->index(sourceRow, 6, sourceParent);
    QModelIndex lastNameIndex = sourceModel()->index(sourceRow, 7, sourceParent);

    QString firstName = sourceModel()->data(firstNameIndex).toString();
    QString lastName = sourceModel()->data(lastNameIndex).toString();

    return (firstName.contains(_firstNameRegExp) && lastName.contains(_lastNameRegExp));
}

void PresenceFilterProxyModel::setFirstNameFilter(const QString& regExp){
    _firstNameRegExp.setPattern(regExp);
    invalidateFilter();
}
void PresenceFilterProxyModel::setLastNameFilter(const QString& regExp){
    _lastNameRegExp.setPattern(regExp);
    invalidateFilter();
}
