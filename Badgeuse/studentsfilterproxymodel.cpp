#include "studentsfilterproxymodel.h"

StudentsFilterProxyModel::StudentsFilterProxyModel(QObject *parent) : QSortFilterProxyModel(parent)
{
    _firstnameRegExp.setCaseSensitivity(Qt::CaseInsensitive);
    _firstnameRegExp.setPatternSyntax(QRegExp::RegExp);

    _lastnameRegExp.setCaseSensitivity(Qt::CaseInsensitive);
    _lastnameRegExp.setPatternSyntax(QRegExp::RegExp);

    _studentNumberRegExp.setCaseSensitivity(Qt::CaseInsensitive);
    _studentNumberRegExp.setPatternSyntax(QRegExp::RegExp);

    _trainingRegExp.setCaseSensitivity(Qt::CaseInsensitive);
    _trainingRegExp.setPatternSyntax(QRegExp::RegExp);

    _optionRegExp.setCaseSensitivity(Qt::CaseInsensitive);
    _optionRegExp.setPatternSyntax(QRegExp::RegExp);

    _groupNumberRegExp.setCaseSensitivity(Qt::CaseInsensitive);
    _groupNumberRegExp.setPatternSyntax(QRegExp::RegExp);

    _promotionRegExp.setCaseSensitivity(Qt::CaseInsensitive);
    _promotionRegExp.setPatternSyntax(QRegExp::RegExp);

    _mailRegExp.setCaseSensitivity(Qt::CaseInsensitive);
    _mailRegExp.setPatternSyntax(QRegExp::RegExp);

}
bool StudentsFilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    QModelIndex firstnameIndex = sourceModel()->index(sourceRow, StudentsModel::FIRSTNAME, sourceParent);
    QString firstname = sourceModel()->data(firstnameIndex).toString();

    QModelIndex lastnameIndex = sourceModel()->index(sourceRow, StudentsModel::LASTNAME, sourceParent);
    QString lastname = sourceModel()->data(lastnameIndex).toString();

    QModelIndex studentNumberIndex = sourceModel()->index(sourceRow, StudentsModel::STUDENTNUMBER, sourceParent);
    QString studentNumber = sourceModel()->data(studentNumberIndex).toString();

    QModelIndex trainingIndex = sourceModel()->index(sourceRow, StudentsModel::TRAINING, sourceParent);
    QString training = sourceModel()->data(trainingIndex).toString();

    QModelIndex optionIndex = sourceModel()->index(sourceRow, StudentsModel::OPTION, sourceParent);
    QString option = sourceModel()->data(optionIndex).toString();

    QModelIndex groupNumberIndex = sourceModel()->index(sourceRow, StudentsModel::GROUPNUMBER, sourceParent);
    QString groupNumber = sourceModel()->data(groupNumberIndex).toString();

    QModelIndex promotionIndex = sourceModel()->index(sourceRow, StudentsModel::PROMOTION, sourceParent);
    QString promotion = sourceModel()->data(promotionIndex).toString();

    QModelIndex mailIndex = sourceModel()->index(sourceRow, StudentsModel::MAIL, sourceParent);
    QString mail = sourceModel()->data(mailIndex).toString();


    return (firstname.contains(_firstnameRegExp)
            && lastname.contains(_lastnameRegExp)
            && studentNumber.contains(_studentNumberRegExp)
            && training.contains(_trainingRegExp)
            && option.contains(_optionRegExp)
            && groupNumber.contains(_groupNumberRegExp)
            && promotion.contains(_promotionRegExp)
            && mail.contains(_mailRegExp)
            );
}

void StudentsFilterProxyModel::setFirstnameFilter(const QString& regExp){
    _firstnameRegExp.setPattern(regExp);
    invalidateFilter();
}
void StudentsFilterProxyModel::setLastnameFilter(const QString& regExp){
    _lastnameRegExp.setPattern(regExp);
    invalidateFilter();
}
void StudentsFilterProxyModel::setStudentNumberFilter(const QString& regExp){
    _studentNumberRegExp.setPattern(regExp);
    invalidateFilter();
}
void StudentsFilterProxyModel::setTrainingFilter(const QString& regExp) {
    _trainingRegExp.setPattern(regExp);
    invalidateFilter();
}
void StudentsFilterProxyModel::setOptionFilter(const QString& regExp) {
    _optionRegExp.setPattern(regExp);
    invalidateFilter();
}
void StudentsFilterProxyModel::setGroupNumberFilter(const QString& regExp) {
    _groupNumberRegExp.setPattern(regExp);
    invalidateFilter();
}
void StudentsFilterProxyModel::setPromotionFilter(const QString& regExp) {
    _promotionRegExp.setPattern(regExp);
    invalidateFilter();
}
void StudentsFilterProxyModel::setMailFilter(const QString& regExp) {
    _mailRegExp.setPattern(regExp);
    invalidateFilter();
}
