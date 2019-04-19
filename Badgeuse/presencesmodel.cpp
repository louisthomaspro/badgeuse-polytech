#include "presencesmodel.h"

PresencesModel::PresencesModel(QObject* parent) : QSqlQueryModel(parent)
{

}

QVariant PresencesModel::data(const QModelIndex &index, int role) const
{
    QVariant value = QSqlQueryModel::data(index, role);
    if (value.isValid() && role == Qt::DisplayRole) {
        if (index.column() == 0)
            return value.toByteArray().toHex();
//        else if (index.column() == 1)
//            return value.toByteArray().toHex(':');
//        else if (index.column() == 4)
//            return value.toByteArray().toHex();
    }
    if (role == Qt::TextColorRole && index.column() == 1)
        return QVariant::fromValue(QColor(Qt::red));
    return value;
}

void PresencesModel::initModel()
{
    QSqlQuery query("select \
                    s.uuid,\
                    stu.studentNumber,\
                    stu.firstname,\
                    stu.lastname,\
                    stu.`group`,\
                    o.name as option_name,\
                    s.dateTimeEntry,\
                    s.DateTimeExit\
                from badgeuse.scans s\
                left join badgeuse.cards c on c.rfidNumber = s.rfidNumber\
                left join badgeuse.students stu on stu.uuid = c.studentUuid\
                left join badgeuse.training t on stu.trainingUuid = t.uuid\
                left join badgeuse.rlToptionsStudents ostu on ostu.studentsUuid = stu.uuid\
                left join badgeuse.toptions o on o.uuid = ostu.toptionsUuid\
                WHERE\
                stu.studentNumber is not null;");
    setQuery(query);
}


void PresencesModel::setQuery(const QSqlQuery &query) {
    QSqlQueryModel::setQuery(query);
}
