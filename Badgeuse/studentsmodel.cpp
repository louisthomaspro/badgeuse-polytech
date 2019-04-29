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
        else if (index.column() == 1)
            return value.toByteArray().toHex(':');
//        else if (index.column() == 4)
//            return value.toByteArray().toHex();
    }
    if (role == Qt::TextColorRole && index.column() == 1)
        return QVariant::fromValue(QColor(Qt::red));
    return value;
}

void StudentsModel::initModel()
{
    QSqlQuery querySelect("select "
                    "stu.uuid,"
                    "stu.rfidNumber as 'Numéro Rfid',"
                    "stu.studentNumber as 'Numéro Étudiant',"
                    "stu.firstname as Prénom,"
                    "stu.lastname as Nom,"
                    "stu.degreeYear as Promotion,"
                    "stu.mail as Mail,"
                    "t.name as Formation,"
                    "stu.groupNumber as Groupe,"
                    "GROUP_CONCAT(DISTINCT o.name SEPARATOR ', ') as Options "
                "from badgeuse.students stu "
                "left join badgeuse.training t on stu.trainingUuid = t.uuid "
                "left join badgeuse.rlToptionsStudents ostu on ostu.studentsUuid = stu.uuid "
                "left join badgeuse.toptions o on o.uuid = ostu.toptionsUuid "
                "group by stu.uuid;");
    setQuery(querySelect);
}

void StudentsModel::reload() {
    initModel();
}

void StudentsModel::setQuery(const QSqlQuery &query)
{
    QSqlQueryModel::setQuery(query);
}

void StudentsModel::remove(QString uuid)
{
    // Delete in database
    // Delete cascade on toptions table : delete relations
    // Delete cascade on scans table : update cascade, set NULL
    QSqlQuery queryStudentDelete("delete from badgeuse.students where uuid = UNHEX(?)");
    queryStudentDelete.addBindValue(uuid);

    if(!queryStudentDelete.exec()) {
        qDebug() << "SqlError: " << queryStudentDelete.lastError().text();
        return;
    } else {
        qDebug() << "Student " << uuid << " deleted.";
        reload();
    }
}

void StudentsModel::add(QString studentNumber, QString firstname, QString lastname, QString mail, int degreeYear, QString trainingUuid, int groupNumber, QString rfidNumber, QMap<QString, QVariant> options)
{
    QSqlQuery queryStudentInsert("insert into badgeuse.students VALUES("
                               "UNHEX(REPLACE(uuid(),'-','')), ?, ?, ?, ?, ?, UNHEX(?), ?, UNHEX(?));");
    queryStudentInsert.addBindValue(firstname);
    queryStudentInsert.addBindValue(lastname);
    queryStudentInsert.addBindValue(degreeYear);
    queryStudentInsert.addBindValue(studentNumber);
    queryStudentInsert.addBindValue(mail);
    queryStudentInsert.addBindValue(trainingUuid);
    queryStudentInsert.addBindValue(groupNumber);
    queryStudentInsert.addBindValue(rfidNumber);

    if(!queryStudentInsert.exec()) {
        qDebug() << "SqlError: " << queryStudentInsert.lastError().text();
        return;
    } else {
//        qDebug() << firstname << " " << lastname << " inserted.";
    }

    QString lastUuid = QString();
    QSqlQuery queryLastUuid("SELECT @last_uuid");
    if (queryLastUuid.next()) {
        lastUuid = queryLastUuid.value(0).toByteArray().toHex();
//        qDebug() << "Last uuid: " + lastUuid;
    } else {
        qDebug() << "No last uuid found...";
        return;
    }

    addOptions(lastUuid, options["itemsData"].toStringList());


    // Associate scans with the student
    QSqlQuery queryStudentUpdateScans("update badgeuse.scans set studentUuid = UNHEX(?) where rfidNumber = UNHEX(?)");
    queryStudentUpdateScans.addBindValue(lastUuid);
    queryStudentUpdateScans.addBindValue(rfidNumber);

    if(!queryStudentUpdateScans.exec()) {
        qDebug() << "SqlError: " << queryStudentUpdateScans.lastError().text();
        return;
    } else {
//        qDebug() << "Scans updated.";
    }



    qDebug() << "Succefully inserted";
}


void StudentsModel::addOptions(QString uuid, QStringList options) {
    QSqlQuery queryStudentInsertOptions("insert into badgeuse.rlToptionsStudents VALUES(UNHEX(?), UNHEX(?))");

    QStringList uuids;
    QStringList optionsUuids;
    for( int a = 0; a < options.length(); a++) {
      uuids << uuid;
      optionsUuids << options[a];
   }

    queryStudentInsertOptions.addBindValue(uuids);
    queryStudentInsertOptions.addBindValue(optionsUuids);
    if (!queryStudentInsertOptions.execBatch()) {
        qDebug() << "Error:" << queryStudentInsertOptions.lastError().text();
        return;
    } else {
//        qDebug() << options << " option inserted.";
    }
}

void StudentsModel::modify(QString uuid, QString studentNumber, QString firstname, QString lastname, QString mail, int degreeYear, QString trainingUuid, int groupNumber, QString rfidNumber, QMap<QString, QVariant> options)
{
    QSqlQuery queryStudentModify("update badgeuse.students set "
                               "firstname = ?,"
                               "lastname = ?,"
                               "degreeYear = ?,"
                               "studentNumber = ?,"
                               "mail = ?,"
                               "trainingUuid = UNHEX(?),"
                               "groupNumber = ?,"
                               "rfidNumber = UNHEX(?) "
                               "where uuid = UNHEX(?);");
    queryStudentModify.addBindValue(firstname);
    queryStudentModify.addBindValue(lastname);
    queryStudentModify.addBindValue(degreeYear);
    queryStudentModify.addBindValue(studentNumber);
    queryStudentModify.addBindValue(mail);
    queryStudentModify.addBindValue(trainingUuid);
    queryStudentModify.addBindValue(groupNumber);
    queryStudentModify.addBindValue(rfidNumber);
    queryStudentModify.addBindValue(uuid);


    if(!queryStudentModify.exec()) {
        qDebug() << "SqlError: " << queryStudentModify.lastError().text();
        return;
    } else {
//        qDebug() << "Student updated.";
    }

    QSqlQuery queryStudentDeleteOptions("delete from badgeuse.rlToptionsStudents "
                               "where studentsUuid = UNHEX(?);");
    queryStudentDeleteOptions.addBindValue(uuid);

    if(!queryStudentDeleteOptions.exec()) {
        qDebug() << "SqlError: " << queryStudentDeleteOptions.lastError().text();
        return;
    } else {
//        qDebug() << "Options removed.";
    }


    // Update presence studentUuid
    QSqlQuery queryStudentUpdatePresences("update badgeuse.scans set "
                                          "studentUuid = UNHEX(?) "
                                            "where rfidNumber = UNHEX(?);");
    queryStudentUpdatePresences.addBindValue(uuid);
    queryStudentUpdatePresences.addBindValue(rfidNumber);

    if(!queryStudentUpdatePresences.exec()) {
        qDebug() << "SqlError: " << queryStudentUpdatePresences.lastError().text();
        return;
    } else {
//        qDebug() << "Options removed.";
    }

    addOptions(uuid, options["itemsData"].toStringList());





    qDebug() << "Update successful";
}

QMap<QString, QVariant> StudentsModel::getStudent(QString uuid)
{
    QSqlQuery queryStudent("select stu.uuid, stu.studentNumber, stu.firstname, stu.lastname, stu.mail, stu.degreeYear, t.name as trainingName, t.uuid as trainingUuid, stu.groupNumber, stu.rfidNumber from badgeuse.students stu "
                  "left join badgeuse.training t on stu.trainingUuid = t.uuid "
                  "left join badgeuse.rlToptionsStudents ostu on ostu.studentsUuid = stu.uuid "
                  "left join badgeuse.toptions o on o.uuid = ostu.toptionsUuid "
                  "where stu.uuid = UNHEX(?);");

    queryStudent.addBindValue(uuid);
    queryStudent.exec();

    QMap<QString, QVariant> studentInfo;

    // studentNumber
    // firstname
    // lastname
    // mail
    // degreeYear
    // trainingName
    // trainingUuid
    // groupNumber
    // rfidNumber
    // options -> optionsUuid, optionsName

    if (queryStudent.next()) {
        for (int col = 0; col < queryStudent.record().count(); col++) { // foreach colmns
            studentInfo[queryStudent.record().fieldName(col)] = queryStudent.value(col);
        }
    } else {
        qDebug() << "Error queryStudent of uuid " << uuid << ".";
        return  QMap<QString, QVariant>();
    }


    QSqlQuery queryStudentOptions("select o.uuid, o.name "
                                "from badgeuse.toptions o "
                                "inner join badgeuse.rlToptionsStudents rl on o.uuid = rl.toptionsUuid "
                                "where rl.studentsUuid = UNHEX(?);");

    queryStudentOptions.addBindValue(uuid);
    queryStudentOptions.exec();

    QMap<QString, QVariant> options;

    if (queryStudentOptions.isSelect()) {
        QVariantList itemUuids;
        QVariantList itemOptions;
        while (queryStudentOptions.next()) {
            itemUuids.append(queryStudentOptions.value(0).toByteArray().toHex());
            itemOptions.append(queryStudentOptions.value(1).toString());
        }
        options["optionsUuid"] = itemUuids;
        options["optionsName"] = itemOptions;

    } else {
        qDebug() << "Error queryStudentOptions of uuid " << uuid << ".";
        return  QMap<QString, QVariant>();
    }
    studentInfo["options"] = options;

    qDebug() << "getStudent: " << studentInfo["uuid"].toByteArray().toHex();

    return studentInfo;
}
