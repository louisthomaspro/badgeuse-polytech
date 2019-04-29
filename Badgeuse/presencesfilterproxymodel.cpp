#include "presencesfilterproxymodel.h"

PresencesFilterProxyModel::PresencesFilterProxyModel(QObject *parent) : QSortFilterProxyModel(parent)
{
    _firstNameRegExp.setCaseSensitivity(Qt::CaseInsensitive);
    _firstNameRegExp.setPatternSyntax(QRegExp::RegExp);

    _lastNameRegExp.setCaseSensitivity(Qt::CaseInsensitive);
    _lastNameRegExp.setPatternSyntax(QRegExp::RegExp);
}
bool PresencesFilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    QModelIndex firstNameIndex = sourceModel()->index(sourceRow, PresencesModel::FIRSTNAME, sourceParent);
    QModelIndex lastNameIndex = sourceModel()->index(sourceRow, PresencesModel::LASTNAME, sourceParent);

    QString firstName = sourceModel()->data(firstNameIndex).toString();
    QString lastName = sourceModel()->data(lastNameIndex).toString();

    return (firstName.contains(_firstNameRegExp) && lastName.contains(_lastNameRegExp));
}

void PresencesFilterProxyModel::setFirstNameFilter(const QString& regExp){
    _firstNameRegExp.setPattern(regExp);
    invalidateFilter();
}
void PresencesFilterProxyModel::setLastNameFilter(const QString& regExp){
    _lastNameRegExp.setPattern(regExp);
    invalidateFilter();
}
