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
    }
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

void PresencesModel::reload()
{
    initModel();
}

void PresencesModel::setQuery(const QSqlQuery &query)
{
    QSqlQueryModel::setQuery(query);
}


bool PresencesModel::remove(QString uuid)
{
    QSqlQuery remove("delete from badgeuse.scans where uuid = UNHEX(?)");
    remove.addBindValue(uuid);

    return Utilities::exec(remove);
}


bool PresencesModel::add(uint DateTimeEntry, uint DateTimeExit, QString cardReaderUuid, QString studentUuid) {
    QSqlQuery insert("insert into badgeuse.scans VALUES("
                               "UNHEX(REPLACE(uuid(),'-','')), (select rfidNumber from students where uuid = UNHEX(?)), FROM_UNIXTIME(?), FROM_UNIXTIME(?), UNHEX(?), UNHEX(?));");
    insert.addBindValue(studentUuid);
    insert.addBindValue(DateTimeEntry);
    insert.addBindValue(DateTimeExit);
    insert.addBindValue(cardReaderUuid);
    insert.addBindValue(studentUuid);

    return Utilities::exec(insert);
}


bool PresencesModel::modify(QString uuid, uint DateTimeEntry, uint DateTimeExit, QString cardReaderUuid, QString studentUuid) {
    QSqlQuery modify("update badgeuse.scans set "
                               "rfidNumber = (select rfidNumber from students where uuid = UNHEX(?)),"
                               "dateTimeEntry = FROM_UNIXTIME(?),"
                               "dateTimeExit = FROM_UNIXTIME(?),"
                               "cardReaderUuid = UNHEX(?),"
                               "studentUuid = UNHEX(?) "
                               "where uuid = UNHEX(?);");
    modify.addBindValue(studentUuid);
    modify.addBindValue(DateTimeEntry);
    modify.addBindValue(DateTimeExit);
    modify.addBindValue(cardReaderUuid);
    modify.addBindValue(studentUuid);
    modify.addBindValue(uuid);

    return Utilities::exec(modify);
}




QMap<QString, QVariant> PresencesModel::getPresence(QString uuid) {
    QSqlQuery select;
    select.prepare("select "
                    "s.uuid, "
                    "s.rfidNumber, "
                    "UNIX_TIMESTAMP(s.dateTimeEntry) as dateTimeEntry, "
                    "UNIX_TIMESTAMP(s.dateTimeExit) as dateTimeExit, "
                    "s.studentUuid, "
                    "s.cardreaderUuid "
                    "from badgeuse.scans s "
                    "left join badgeuse.cardreaders cr on cr.uuid = s.cardreaderUuid "
                  "where s.uuid = UNHEX(?);");

    select.addBindValue(uuid);

    return Utilities::generateQListFromSql(select).first();
}



QList<QMap<QString, QVariant>> PresencesModel::getExport(QString studentUuid, QDateTime QDateTimeBegin, QDateTime QDateTimeEnd) {

    QTime beginTime(0, 0, 0);
    QTime endTime(23, 59, 59);

    QDateTimeBegin.setTime(beginTime);
    QDateTimeEnd.setTime(endTime);

    QString sql = QString(
        "with studentsInformation as ("
        "select "
        "stu.uuid, "
        "stu.rfidNumber, "
        "stu.studentNumber, "
        "stu.firstname, "
        "stu.lastname, "
        "stu.degreeYear, "
        "stu.mail, "
        "t.name as training, "
        "stu.groupNumber, "
        "GROUP_CONCAT(DISTINCT o.name SEPARATOR ' | ') as options "
        "from badgeuse.students stu "
        "left join badgeuse.training t on stu.trainingUuid = t.uuid "
        "left join badgeuse.rlToptionsStudents ostu on ostu.studentsUuid = stu.uuid "
        "left join badgeuse.toptions o on o.uuid = ostu.toptionsUuid "
        "group by stu.uuid "
        ") "
        "select "
        "DATE_FORMAT(s.dateTimeEntry, '%d/%m/%Y %H:%i:%s') as 'Date dentrée', "
        "DATE_FORMAT(s.dateTimeExit, '%d/%m/%Y %H:%i:%s') as 'Date de sortie', "
        "cr.information as Badgeuse, "
        "stu.studentNumber as 'Numéro Étudiant', "
        "stu.firstname as Prénom, "
        "stu.lastname as Nom, "
        "stu.degreeYear as Promotion, "
        "stu.training as Formation, "
        "stu.groupNumber as Groupe, "
        "stu.options as 'Options' "
        "from badgeuse.scans s "
        "left join studentsInformation stu on stu.uuid = s.studentUuid "
        "left join badgeuse.cardreaders cr on cr.uuid = s.cardReaderUuid "
        "where 1=1 ");

    if (!studentUuid.isEmpty()) {
        sql += "and stu.uuid = UNHEX(:studentUuid) ";
    }

    if (QDateTimeEnd.isValid() && QDateTimeEnd.isValid()) {
        sql += "and UNIX_TIMESTAMP(s.dateTimeEntry) BETWEEN :dateBegin and :dateEnd ";
    }

    sql += ";";

    QSqlQuery query;
    query.prepare(sql);
    query.bindValue(":studentUuid", studentUuid);
    query.bindValue(":dateBegin", QDateTimeBegin.toTime_t());
    query.bindValue(":dateEnd", QDateTimeEnd.toTime_t());

    return Utilities::generateQListFromSql(query);
}

