#include "studentsmodel.h"

StudentsModel::StudentsModel(QObject* parent) : QSqlQueryModel(parent)
{

}

QVariant StudentsModel::data(const QModelIndex &index, int role) const
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

void StudentsModel::init()
{
    QSqlQuery query("select \
                    stu.uuid,\
                    stu.studentNumber,\
                    stu.firstname,\
                    stu.lastname,\
                    stu.degreeYear,\
                    stu.mail,\
                    t.name,\
                    stu.`group`,\
                    o.name\
                from badgeuse.students stu\
                left join badgeuse.training t on stu.trainingUuid = t.uuid\
                left join badgeuse.rlToptionsStudents ostu on ostu.studentsUuid = stu.uuid\
                left join badgeuse.toptions o on o.uuid = ostu.toptionsUuid;");
    setQuery(query);
}


void StudentsModel::setQuery(const QSqlQuery &query) {
    QSqlQueryModel::setQuery(query);
}
