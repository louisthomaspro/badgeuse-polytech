#include "presencesfilterproxymodel.h"

PresencesFilterProxyModel::PresencesFilterProxyModel(QObject *parent) : QSortFilterProxyModel(parent)
{
    _firstnameRegExp.setCaseSensitivity(Qt::CaseInsensitive);
    _firstnameRegExp.setPatternSyntax(QRegExp::RegExp);

    _lastnameRegExp.setCaseSensitivity(Qt::CaseInsensitive);
    _lastnameRegExp.setPatternSyntax(QRegExp::RegExp);

    _studentNumberRegExp.setCaseSensitivity(Qt::CaseInsensitive);
    _studentNumberRegExp.setPatternSyntax(QRegExp::RegExp);

    _cardReaderRegExp.setCaseSensitivity(Qt::CaseInsensitive);
    _cardReaderRegExp.setPatternSyntax(QRegExp::RegExp);

    _trainingRegExp.setCaseSensitivity(Qt::CaseInsensitive);
    _trainingRegExp.setPatternSyntax(QRegExp::RegExp);

    _optionRegExp.setCaseSensitivity(Qt::CaseInsensitive);
    _optionRegExp.setPatternSyntax(QRegExp::RegExp);

    _groupNumberRegExp.setCaseSensitivity(Qt::CaseInsensitive);
    _groupNumberRegExp.setPatternSyntax(QRegExp::RegExp);

    _promotionRegExp.setCaseSensitivity(Qt::CaseInsensitive);
    _promotionRegExp.setPatternSyntax(QRegExp::RegExp);

}
bool PresencesFilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    QModelIndex firstnameIndex = sourceModel()->index(sourceRow, PresencesModel::FIRSTNAME, sourceParent);
    QString firstname = sourceModel()->data(firstnameIndex).toString();

    QModelIndex lastnameIndex = sourceModel()->index(sourceRow, PresencesModel::LASTNAME, sourceParent);
    QString lastname = sourceModel()->data(lastnameIndex).toString();

    QModelIndex studentNumberIndex = sourceModel()->index(sourceRow, PresencesModel::STUDENTNUMBER, sourceParent);
    QString studentNumber = sourceModel()->data(studentNumberIndex).toString();

    QModelIndex cardReaderIndex = sourceModel()->index(sourceRow, PresencesModel::CARDREADER, sourceParent);
    QString cardReader = sourceModel()->data(cardReaderIndex).toString();

    QModelIndex trainingIndex = sourceModel()->index(sourceRow, PresencesModel::TRAINING, sourceParent);
    QString training = sourceModel()->data(trainingIndex).toString();

    QModelIndex optionIndex = sourceModel()->index(sourceRow, PresencesModel::OPTION, sourceParent);
    QString option = sourceModel()->data(optionIndex).toString();

    QModelIndex groupNumberIndex = sourceModel()->index(sourceRow, PresencesModel::GROUPNUMBER, sourceParent);
    QString groupNumber = sourceModel()->data(groupNumberIndex).toString();

    QModelIndex promotionIndex = sourceModel()->index(sourceRow, PresencesModel::PROMOTION, sourceParent);
    QString promotion = sourceModel()->data(promotionIndex).toString();

    QModelIndex entryIndex = sourceModel()->index(sourceRow, PresencesModel::ENTRY, sourceParent);
    QDateTime entry = sourceModel()->data(entryIndex).toDateTime();

    QModelIndex exitIndex = sourceModel()->index(sourceRow, PresencesModel::EXIT, sourceParent);
    QDateTime exit = sourceModel()->data(exitIndex).toDateTime();

    return (firstname.contains(_firstnameRegExp)
            && lastname.contains(_lastnameRegExp)
            && studentNumber.contains(_studentNumberRegExp)
            && cardReader.contains(_cardReaderRegExp)
            && training.contains(_trainingRegExp)
            && option.contains(_optionRegExp)
            && groupNumber.contains(_groupNumberRegExp)
            && promotion.contains(_promotionRegExp)
            && ((_period) ? (entry >= _beginDate) && (entry <= _endDate) : true)
            );
}

void PresencesFilterProxyModel::setFirstnameFilter(const QString& regExp){
    _firstnameRegExp.setPattern(regExp);
    invalidateFilter();
}
void PresencesFilterProxyModel::setLastnameFilter(const QString& regExp){
    _lastnameRegExp.setPattern(regExp);
    invalidateFilter();
}
void PresencesFilterProxyModel::setStudentNumberFilter(const QString& regExp){
    _studentNumberRegExp.setPattern(regExp);
    invalidateFilter();
}
void PresencesFilterProxyModel::setCardReaderFilter(const QString& regExp) {
    _cardReaderRegExp.setPattern(regExp);
    invalidateFilter();
}
void PresencesFilterProxyModel::setTrainingFilter(const QString& regExp) {
    _trainingRegExp.setPattern(regExp);
    invalidateFilter();
}
void PresencesFilterProxyModel::setOptionFilter(const QString& regExp) {
    _optionRegExp.setPattern(regExp);
    invalidateFilter();
}
void PresencesFilterProxyModel::setGroupNumberFilter(const QString& regExp) {
    _groupNumberRegExp.setPattern(regExp);
    invalidateFilter();
}
void PresencesFilterProxyModel::setPromotionFilter(const QString& regExp) {
    _promotionRegExp.setPattern(regExp);
    invalidateFilter();
}
void PresencesFilterProxyModel::setBeginFilter(const QDateTime& regExp) {
    _beginDate = regExp;
    QTime n(0, 0, 0);
    _beginDate.setTime(n);
    invalidateFilter();
}
void PresencesFilterProxyModel::setEndFilter(const QDateTime& regExp) {
    _endDate = regExp;
    QTime n(23, 59, 59);
    _endDate.setTime(n);
    invalidateFilter();
}
void PresencesFilterProxyModel::setPeriodFilter(const bool& regExp) {
    _period = regExp;
    invalidateFilter();
}
