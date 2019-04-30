#include "studentsmodel.h"

StudentsModel::StudentsModel(OptionsModel &optionsModel, QObject* parent) : QSqlQueryModel(parent)
{
    _optionsModel = &optionsModel;
}

QVariant StudentsModel::data(const QModelIndex &index, int role) const
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

void StudentsModel::reload()
{
    initModel();
}

void StudentsModel::setQuery(const QSqlQuery &query)
{
    QSqlQueryModel::setQuery(query);
}

bool StudentsModel::remove(QString uuid)
{
    // Delete cascade on toptions table : delete relations
    // Delete cascade on scans table : update cascade, set NULL
    QSqlQuery remove;
    remove.prepare("delete from badgeuse.students where uuid = UNHEX(?)");
    remove.addBindValue(uuid);

    return Utilities::exec(remove);
}

bool StudentsModel::add(QString studentNumber, QString firstname, QString lastname, QString mail, int degreeYear, QString trainingUuid, int groupNumber, QString rfidNumber, QMap<QString, QVariant> options)
{
    QSqlQuery insert;
    insert.prepare("insert into badgeuse.students VALUES("
                               "UNHEX(REPLACE(uuid(),'-','')), ?, ?, ?, ?, ?, UNHEX(?), ?, UNHEX(?));");
    insert.addBindValue(firstname);
    insert.addBindValue(lastname);
    insert.addBindValue(degreeYear);
    insert.addBindValue(studentNumber);
    insert.addBindValue(mail);
    insert.addBindValue(trainingUuid);
    insert.addBindValue(groupNumber);
    insert.addBindValue(rfidNumber);

    if(!Utilities::exec(insert)) return false;

    QString lastUuid = Utilities::getLastUuid();
    if (lastUuid.isEmpty()) return false;

    if (!addOptions(lastUuid, options["itemData"].toStringList())) return false;

    // Associate presences with the student
    QSqlQuery updatePresences;
    updatePresences.prepare("update badgeuse.scans set studentUuid = UNHEX(?) where rfidNumber = UNHEX(?)");
    updatePresences.addBindValue(lastUuid);
    updatePresences.addBindValue(rfidNumber);

    return Utilities::exec(updatePresences);
}


bool StudentsModel::addOptions(QString uuid, QStringList options)
{
    QSqlQuery insertBatch;
    insertBatch.prepare("insert into badgeuse.rlToptionsStudents VALUES(UNHEX(?), UNHEX(?))");

    QStringList uuids;
    QStringList optionsUuids;
    for( int a = 0; a < options.length(); a++) {
      uuids << uuid;
      optionsUuids << options[a];
   }

    insertBatch.addBindValue(uuids);
    insertBatch.addBindValue(optionsUuids);
    if (!insertBatch.execBatch()) {
        qDebug() << "Error:" << insertBatch.lastError().text();
        return false;
    }
    return true;
}

bool StudentsModel::modify(QString uuid, QString studentNumber, QString firstname, QString lastname, QString mail, int degreeYear, QString trainingUuid, int groupNumber, QString rfidNumber, QMap<QString, QVariant> options)
{
    QSqlQuery modify;
    modify.prepare("update badgeuse.students set "
                               "firstname = ?,"
                               "lastname = ?,"
                               "degreeYear = ?,"
                               "studentNumber = ?,"
                               "mail = ?,"
                               "trainingUuid = UNHEX(?),"
                               "groupNumber = ?,"
                               "rfidNumber = UNHEX(?) "
                               "where uuid = UNHEX(?);");
    modify.addBindValue(firstname);
    modify.addBindValue(lastname);
    modify.addBindValue(degreeYear);
    modify.addBindValue(studentNumber);
    modify.addBindValue(mail);
    modify.addBindValue(trainingUuid);
    modify.addBindValue(groupNumber);
    modify.addBindValue(rfidNumber);
    modify.addBindValue(uuid);

    if(!Utilities::exec(modify)) return false;

    // Remove all options
    QSqlQuery removeOptions;
    removeOptions.prepare("delete from badgeuse.rlToptionsStudents where studentsUuid = UNHEX(?);");
    removeOptions.addBindValue(uuid);
    if (!Utilities::exec(removeOptions)) return false;


    // Update presence studentUuid
    QSqlQuery updateScans;
    updateScans.prepare("update badgeuse.scans set "
                                          "studentUuid = UNHEX(?) "
                                            "where rfidNumber = UNHEX(?);");
    updateScans.addBindValue(uuid);
    updateScans.addBindValue(rfidNumber);

    if(!Utilities::exec(updateScans)) return false;

    return addOptions(uuid, options["itemData"].toStringList());


}

QMap<QString, QVariant> StudentsModel::getStudent(QString uuid)
{
    QSqlQuery select;
    select.prepare("select stu.uuid, stu.studentNumber, stu.firstname, stu.lastname, stu.mail, stu.degreeYear, t.name as trainingName, t.uuid as trainingUuid, stu.groupNumber, stu.rfidNumber from badgeuse.students stu "
                  "left join badgeuse.training t on stu.trainingUuid = t.uuid "
                  "where stu.uuid = UNHEX(?);");

    select.addBindValue(uuid);

    //// STRUCTURE
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


    QMap<QString, QVariant> studentInfo = Utilities::generateQListFromSql(select).first();
    if (studentInfo.size() <=0) return studentInfo;


    QList<QMap<QString, QVariant>> options = _optionsModel->getFromStudent(uuid);

    QList<QVariant> variantList = QList<QVariant>();
    for (QMap<QString, QVariant> item : options) {
        variantList.append(QVariant(item));
    }
    studentInfo["options"] = variantList;
    return studentInfo;
}


QList<QMap<QString, QVariant>> StudentsModel::get()
{
    QSqlQuery select;
    select.prepare("select stu.uuid, CONCAT(stu.studentNumber, ' - ', stu.firstname, ' ', stu.lastname) as text from badgeuse.students stu;");
    return Utilities::generateQListFromSql(select);

}
