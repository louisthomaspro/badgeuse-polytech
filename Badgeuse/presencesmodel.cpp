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
                    "s.dateTimeExit, "
                    "cr.information, "
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
                    "inner join badgeuse.cardreaders cr on cr.uuid = s.cardReaderUuid "
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
                               "UNHEX(REPLACE(uuid(),'-','')), ?, ?, ?, ?, ?);");
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

    qDebug() << "Insert successful";
}


void PresencesModel::modify(QString uuid, QString rfidNumber, QDateTime DateTimeEntry, QDateTime DateTimeExit, QString cardReaderUuid, QString studentUuid) {
    QSqlQuery queryStudentModify("update badgeuse.scans set "
                               "rfidNumber = ?,"
                               "dateTimeEntry = ?,"
                               "dateTimeExit = ?,"
                               "cardReaderUuid = ?,"
                               "studentUuid = ? "
                               "where uuid = UNHEX(?);");
    queryStudentModify.addBindValue(rfidNumber);
    queryStudentModify.addBindValue(DateTimeEntry);
    queryStudentModify.addBindValue(DateTimeExit);
    queryStudentModify.addBindValue(cardReaderUuid);
    queryStudentModify.addBindValue(studentUuid);
    queryStudentModify.addBindValue(uuid);


    if(!queryStudentModify.exec()) {
        qDebug() << "SqlError: " << queryStudentModify.lastError().text();
        return;
    } else {
//        qDebug() << "Scan updated.";
    }

    qDebug() << "Update successful";
}


QMap<QString, QVariant> PresencesModel::getPresence(QString uuid) {
    QSqlQuery queryPresence("select "
                    "s.uuid, "
                    "s.rfidNumber, "
                    "s.dateTimeEntry, "
                    "s.dateTimeExit, "
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
                    "group by stu.uuid;"
                  "where stu.uuid = UNHEX(?);");

    queryPresence.addBindValue(uuid);
    queryPresence.exec();

    QMap<QString, QVariant> presenceInfo;

    // a definir

    if (queryPresence.next()) {
        for (int col = 0; col < queryPresence.record().count(); col++) { // foreach colmns
            presenceInfo[queryPresence.record().fieldName(col)] = queryPresence.value(col);
        }
    } else {
        qDebug() << "Error queryPrecence of uuid " << uuid << ".";
        return  QMap<QString, QVariant>();
    }

    return presenceInfo;
}

