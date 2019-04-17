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

using namespace std;

namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

    struct Col {
        string name;
        bool show;
    };

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
//    void refresh();
//    void customHeaderMenuRequested(QPoint pos);
//    void toggleColumn(QVariant v);
//    void textFilterFamilyNameChanged();
//    void textFilterNameChanged();
    void openStudentsDialog();
    void deleteStudent();


private:
    Ui::MainWindow *ui;
    QSqlDatabase _db;
    PresencesModel *model2;
    QSqlQueryModel *model;
    QSortFilterProxyModel *sort_filter;
    QRegExp nameRegExp;
    QRegExp familyNameRegExp;
    QSortFilterProxyModel *nmFilter;
    QSortFilterProxyModel *fnFilter;

    BadgeuseModel *_badgeuseModel;
    StudentsDialog *_studentsDialog;


    Col absencesHeaderTitles[6] = { {"Prénom", 1},{"Nom", 1}, {"Promotion", 1}, {"Numéro étudiant", 1}, {"Mail", 0}, {"Numéro RFID", 0}};




protected:
};

#endif // MAINWINDOW_H
