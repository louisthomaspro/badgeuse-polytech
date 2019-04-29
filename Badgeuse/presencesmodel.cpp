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
    QSqlQuery query("with studentsInformation as ("
                    "select "
                    "stu.uuid, "
                    "stu.rfidNumber, "
                    "stu.studentNumber,"
                    "stu.firstname, "
                    "stu.lastname, "
                    "stu.degreeYear, "
                    "stu.mail, "
                    "t.name as training, "
                    "stu.groupNumber, "
                    "GROUP_CONCAT(DISTINCT o.name SEPARATOR ', ') as options "
                    "from badgeuse.students stu "
                    "left join badgeuse.training t on stu.trainingUuid = t.uuid "
                    "left join badgeuse.rlToptionsStudents ostu on ostu.studentsUuid = stu.uuid "
                    "left join badgeuse.toptions o on o.uuid = ostu.toptionsUuid "
                    "group by stu.uuid "
                ")"
                "select s.uuid, s.rfidNumber as 'Numéro Rfid', s.dateTimeEntry as \"Date d'entrée\", s.dateTimeExit as 'Date de sortie', cr.information as Badgeuse, stu.studentNumber as 'Numéro Étudiant', stu.firstname as Prénom, stu.lastname as Nom, stu.degreeYear as Promotion, stu.training as Formation, stu.groupNumber as Groupe, stu.options as Options "
                "from badgeuse.scans s "
                "left join studentsInformation stu on stu.uuid = s.studentUuid "
                "left join badgeuse.cardreaders cr on cr.uuid = s.cardReaderUuid; "
                );
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


void PresencesModel::add(uint DateTimeEntry, uint DateTimeExit, QString cardReaderUuid, QString studentUuid) {
    QSqlQuery queryPresenceInsert("insert into badgeuse.scans VALUES("
                               "UNHEX(REPLACE(uuid(),'-','')), (select rfidNumber from students where uuid = UNHEX(?)), FROM_UNIXTIME(?), FROM_UNIXTIME(?), UNHEX(?), UNHEX(?));");
    queryPresenceInsert.addBindValue(studentUuid);
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


void PresencesModel::modify(QString uuid, uint DateTimeEntry, uint DateTimeExit, QString cardReaderUuid, QString studentUuid) {
    QSqlQuery queryStudentModify("update badgeuse.scans set "
                               "rfidNumber = (select rfidNumber from students where uuid = UNHEX(?)),"
                               "dateTimeEntry = FROM_UNIXTIME(?),"
                               "dateTimeExit = FROM_UNIXTIME(?),"
                               "cardReaderUuid = UNHEX(?),"
                               "studentUuid = UNHEX(?) "
                               "where uuid = UNHEX(?);");
    queryStudentModify.addBindValue(studentUuid);
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
                    "UNIX_TIMESTAMP(s.dateTimeEntry) as dateTimeEntry, "
                    "UNIX_TIMESTAMP(s.dateTimeExit) as dateTimeExit, "
                    "s.studentUuid, "
                    "s.cardreaderUuid "
                    "from badgeuse.scans s "
                    "left join badgeuse.cardreaders cr on cr.uuid = s.cardreaderUuid "
                  "where s.uuid = UNHEX(?);");

    queryPresence.addBindValue(uuid);
    queryPresence.exec();

    QMap<QString, QVariant> presenceInfo;


    if (queryPresence.next()) {
        for (int col = 0; col < queryPresence.record().count(); col++) { // foreach colmns
            presenceInfo[queryPresence.record().fieldName(col)] = queryPresence.value(col);
        }
    } else {
        qDebug() << "Error queryPresence of uuid " << uuid << ".";
        return  QMap<QString, QVariant>();
    }

    return presenceInfo;
}

