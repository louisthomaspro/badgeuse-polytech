#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QMenu>
#include <string>
#include <iostream>
#include <QSortFilterProxyModel>
#include <QDebug>
#include "badgeusemodel.h"
#include "studentsdialog.h"
#include "presencesdialog.h"
#include "trainingdialog.h"
#include "optionsdialog.h"
#include "presencefilterproxymodel.h"
#include <QSettings>

using namespace std;

namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    //void applyFilter(int index, QString ntext);

private slots:
//    void refresh();
//    void customHeaderMenuRequested(QPoint pos);
//    void toggleColumn(QVariant v);
//    void textFilterFamilyNameChanged();
    //void onPresenceFilterChanged();

    void dbSaveAndConnect();

    void openDialog();
    void deleteStudent();
    void deletePresence();
    void deleteOption();
    void deleteTraining();
    void reload();



private:
    Ui::MainWindow *ui;
    QSqlDatabase _db;
    PresencesModel *model2;
    QSqlQueryModel *model;

    QRegExp nameRegExp;
    QRegExp familyNameRegExp;
    QSortFilterProxyModel *nmFilter;
    QSortFilterProxyModel *fnFilter;

    BadgeuseModel *_badgeuseModel;

    StudentsDialog *_studentsDialog;
    PresencesDialog *_presencesDialog;
    TrainingDialog *_trainingDialog;
    OptionsDialog *_optionsDialog;

    PresenceFilterProxyModel *_presenceFilterProxyModel;


//    QSortFilterProxyModel *_studentProxy;
//    QSortFilterProxyModel *_presencesProxy;
//    QSortFilterProxyModel *_trainingProxy;
//    QSortFilterProxyModel *_optionsProxy;

    QSettings *_dbSettings;

//    QSortFilterProxyModel *_pfFirstname;
//    QSortFilterProxyModel *_pfLastname;




protected:
};

#endif // MAINWINDOW_H
