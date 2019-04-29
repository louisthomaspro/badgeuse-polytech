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
#include "presencesfilterproxymodel.h"
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


public:
    QString getTvSelectedUuid(QTableView *tv);


private slots:

    void dbSaveAndConnect();

    void openDialog();

    void deleteStudent();
    void deletePresence();
    void deleteOption();
    void deleteTraining();

    void reload();



private:
    Ui::MainWindow *ui;

    BadgeuseModel *_badgeuseModel;

    StudentsDialog *_studentsDialog;
    PresencesDialog *_presencesDialog;
    TrainingDialog *_trainingDialog;
    OptionsDialog *_optionsDialog;

    PresencesFilterProxyModel *_presencesFilterProxyModel;
//    StudentsFilterProxyModel *_studentsFilterProxyModel;


    QSettings *_dbSettings;





protected:
};

#endif // MAINWINDOW_H
