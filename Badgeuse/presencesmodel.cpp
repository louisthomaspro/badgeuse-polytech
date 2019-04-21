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
        else if (index.column() == 1)
            return value.toByteArray().toHex(':');
//        else if (index.column() == 4)
//            return value.toByteArray().toHex();
    }
    if (role == Qt::TextColorRole && index.column() == 1)
        return QVariant::fromValue(QColor(Qt::red));
    return value;
}

void PresencesModel::initModel()
{
    QSqlQuery query("select "
                    "s.uuid, "
                    "s.rfidNumber, "
                    "s.dateTimeEntry, "
                    "s.DateTimeExit, "
                    "stu.studentNumber as numero_etudiant, "
                    "stu.firstname as prenom, "
                    "stu.lastname as nom, "
                    "stu.degreeYear as promotion, "
                    "stu.mail, "
                    "t.name as formation, "
                    "stu.groupNumber as groupe, "
                    "GROUP_CONCAT(DISTINCT o.name SEPARATOR ', ') as options "
                    "from badgeuse.scans s "
                    "left join badgeuse.students stu on stu.rfidNumber = s.rfidNumber "
                    "left join badgeuse.training t on stu.trainingUuid = t.uuid "
                    "left join badgeuse.rlToptionsStudents ostu on ostu.studentsUuid = stu.uuid "
                    "left join badgeuse.toptions o on o.uuid = ostu.toptionsUuid "
                    "group by stu.uuid;");
    setQuery(query);
}

void PresencesModel::reload() {
    initModel();
}

void PresencesModel::setQuery(const QSqlQuery &query) {
    QSqlQueryModel::setQuery(query);
}


void PresencesModel::remove(QString uuid) {
    QSqlQuery queryPresenceDelete("delete from badgeuse.scans where uuid = UNHEX(?)");
    queryPresenceDelete.addBindValue(uuid);

    if(!queryPresenceDelete.exec()) {
        qDebug() << "SqlError: " << queryPresenceDelete.lastError().text();
        return;
    } else {
        qDebug() << "Presence " << uuid << " deleted.";
        reload();
    }
}


void PresencesModel::add(QString rfidNumber, QDateTime DateTimeEntry, QDateTime DateTimeExit, QString cardReaderUuid, QString studentUuid) {
    QSqlQuery queryPresenceInsert("insert into badgeuse.scans VALUES("
                               "UNHEX(REPLACE(uuid(),'-','')), ?, ?, ?, ?, ?, ?, ?, UNHEX(?));");
    queryPresenceInsert.addBindValue(rfidNumber);
    queryPresenceInsert.addBindValue(DateTimeEntry);
    queryPresenceInsert.addBindValue(DateTimeExit);
    queryPresenceInsert.addBindValue(cardReaderUuid);
    queryPresenceInsert.addBindValue(studentUuid);

    if(!queryPresenceInsert.exec()) {
        qDebug() << "SqlError: " << queryPresenceInsert.lastError().text();
        return;
    } else {
//        qDebug() << firstname << " " << lastname << " inserted.";
    }
}


void PresencesModel::modify(QString uuid, QString rfidNumber, QDateTime DateTimeEntry, QDateTime DateTimeExit, QString cardReaderUuid, QString studentUuid) {

}


QMap<QString, QVariant> PresencesModel::getPresence(QString uuid) {

}

