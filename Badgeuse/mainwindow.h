#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QMenu>
#include <string>
#include <iostream>
#include <QSortFilterProxyModel>

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
    void refresh();
    void customHeaderMenuRequested(QPoint pos);
    void toggleColumn(QVariant v);
    void textFilterFamilyNameChanged();
    void textFilterNameChanged();


private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    QSqlTableModel *model2;
    QSqlQueryModel *model;
    QSortFilterProxyModel *sort_filter;
    QRegExp nameRegExp;
    QRegExp familyNameRegExp;
    QSortFilterProxyModel *nmFilter;
    QSortFilterProxyModel *fnFilter;


    Col absencesHeaderTitles[6] = { {"Prénom", 1},{"Nom", 1}, {"Promotion", 1}, {"Numéro étudiant", 1}, {"Mail", 0}, {"Numéro RFID", 0}};

protected:
};

#endif // MAINWINDOW_H
