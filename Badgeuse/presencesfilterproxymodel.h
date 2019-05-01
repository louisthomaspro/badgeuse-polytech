#ifndef PRESENCESFILTERPROXYMODEL_H
#define PRESENCESFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>
#include <QTime>
#include "presencesmodel.h"


class PresencesFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit PresencesFilterProxyModel(QObject *parent = nullptr);
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const  override;
public slots:
    void setFirstnameFilter(const QString& regExp);
    void setLastnameFilter(const QString& regExp);
    void setStudentNumberFilter(const QString& regExp);
    void setCardReaderFilter(const QString& regExp);
    void setTrainingFilter(const QString& regExp);
    void setOptionFilter(const QString& regExp);
    void setGroupNumberFilter(const QString& regExp);
    void setPromotionFilter(const QString& regExp);
    void setBeginFilter(const QDateTime& regExp);
    void setEndFilter(const QDateTime& regExp);
    void setPeriodFilter(const bool& regExp);
    void setDisplayNullFilter(const bool& regExp);

private:
    QRegExp _firstnameRegExp;
    QRegExp _lastnameRegExp;
    QRegExp _studentNumberRegExp;
    QRegExp _cardReaderRegExp;
    QRegExp _trainingRegExp;
    QRegExp _optionRegExp;
    QRegExp _groupNumberRegExp;
    QRegExp _promotionRegExp;
    QDateTime _beginDate;
    QDateTime _endDate;
    bool _period;
    bool _displayNull = false;
};

#endif // PRESENCEFILTERPROXYMODEL_H
