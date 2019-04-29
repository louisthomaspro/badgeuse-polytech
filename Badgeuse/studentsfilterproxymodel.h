#ifndef STUDENTSFILTERPROXYMODEL_H
#define STUDENTSFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>
#include "studentsmodel.h"


class StudentsFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit StudentsFilterProxyModel(QObject *parent = nullptr);
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const  override;
public slots:
    void setFirstnameFilter(const QString& regExp);
    void setLastnameFilter(const QString& regExp);
    void setStudentNumberFilter(const QString& regExp);
    void setTrainingFilter(const QString& regExp);
    void setOptionFilter(const QString& regExp);
    void setGroupNumberFilter(const QString& regExp);
    void setPromotionFilter(const QString& regExp);
    void setMailFilter(const QString& regExp);

private:
    QRegExp _firstnameRegExp;
    QRegExp _lastnameRegExp;
    QRegExp _studentNumberRegExp;
    QRegExp _trainingRegExp;
    QRegExp _optionRegExp;
    QRegExp _groupNumberRegExp;
    QRegExp _promotionRegExp;
    QRegExp _mailRegExp;
};

#endif // PRESENCEFILTERPROXYMODEL_H
