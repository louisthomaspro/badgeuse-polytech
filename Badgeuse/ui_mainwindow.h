/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout_2;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout;
    QPushButton *pb_addpresence;
    QPushButton *pb_modifypresence;
    QPushButton *pb_deletepresence;
    QTableView *tv_presences;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBox;
    QFormLayout *formLayout;
    QLabel *label_6;
    QLineEdit *le_pf_firstname;
    QLabel *label_5;
    QLineEdit *le_pf_lastname;
    QLabel *label_25;
    QLineEdit *le_pf_studentnumber;
    QLabel *label;
    QComboBox *cb_pf_training;
    QLabel *label_3;
    QComboBox *cb_pf_option;
    QLabel *label_2;
    QLineEdit *le_pf_groupnumber;
    QLabel *label_11;
    QLineEdit *le_pf_promotion;
    QLabel *label_10;
    QComboBox *cb_pf_cardreader;
    QGroupBox *gb_pf_period;
    QVBoxLayout *verticalLayout_18;
    QLabel *label_4;
    QDateEdit *de_pf_begindate;
    QLabel *label_7;
    QDateEdit *de_pf_enddate;
    QSpacerItem *verticalSpacer_6;
    QCheckBox *cb_pf_displaynull;
    QSpacerItem *verticalSpacer;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_15;
    QGridLayout *gridLayout_2;
    QScrollArea *scrollArea_2;
    QWidget *scrollAreaWidgetContents_2;
    QVBoxLayout *verticalLayout_4;
    QGroupBox *groupBox_2;
    QFormLayout *formLayout_3;
    QLabel *label_12;
    QLineEdit *le_sf_firstname;
    QLabel *label_13;
    QLineEdit *le_sf_lastname;
    QLabel *label_26;
    QLineEdit *le_sf_studentnumber;
    QLabel *label_14;
    QComboBox *cb_sf_training;
    QLabel *label_30;
    QComboBox *cb_sf_option;
    QLabel *label_27;
    QLineEdit *le_sf_groupnumber;
    QLabel *label_32;
    QLineEdit *le_sf_promotion;
    QLabel *label_28;
    QLineEdit *le_sf_mail;
    QSpacerItem *verticalSpacer_2;
    QVBoxLayout *verticalLayout_14;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pb_addstudent;
    QPushButton *pb_modifystudent;
    QPushButton *pb_deletestudent;
    QTableView *tv_students;
    QWidget *tab_3;
    QVBoxLayout *verticalLayout_25;
    QTabWidget *tabWidget_2;
    QWidget *tab_4;
    QVBoxLayout *verticalLayout_26;
    QGridLayout *gridLayout_5;
    QHBoxLayout *horizontalLayout_8;
    QTabWidget *tabWidget_3;
    QWidget *tab_6;
    QVBoxLayout *verticalLayout_5;
    QTableView *tv_training;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pb_addtraining;
    QPushButton *pb_modifytraining;
    QPushButton *pb_deletetraining;
    QWidget *tab_7;
    QVBoxLayout *verticalLayout_8;
    QTableView *tv_options;
    QHBoxLayout *horizontalLayout_9;
    QPushButton *pb_addoption;
    QPushButton *pb_modifyoption;
    QPushButton *pb_deleteoption;
    QSpacerItem *verticalSpacer_4;
    QHBoxLayout *horizontalLayout_5;
    QGroupBox *groupBox_5;
    QVBoxLayout *verticalLayout_27;
    QPushButton *pushButton_10;
    QLabel *label_19;
    QGroupBox *groupBox_6;
    QVBoxLayout *verticalLayout_28;
    QLabel *label_20;
    QLabel *label_23;
    QComboBox *cb_export_student;
    QSpacerItem *verticalSpacer_5;
    QGroupBox *gb_export_period;
    QVBoxLayout *verticalLayout_24;
    QLabel *label_21;
    QDateEdit *de_export_begin;
    QLabel *label_22;
    QDateEdit *de_export_end;
    QPushButton *pb_exportpresences;
    QWidget *tab_5;
    QFormLayout *formLayout_2;
    QLabel *label_8;
    QLineEdit *le_host;
    QLabel *label_18;
    QLabel *label_24;
    QLineEdit *le_dbname;
    QLabel *label_9;
    QLineEdit *le_user;
    QLabel *label_16;
    QLineEdit *le_password;
    QSpacerItem *verticalSpacer_3;
    QPushButton *pb_dbconnect;
    QSpinBox *sb_port;
    QPushButton *pb_refresh;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->setEnabled(true);
        MainWindow->resize(1166, 691);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        verticalLayout_2 = new QVBoxLayout(tab);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pb_addpresence = new QPushButton(tab);
        pb_addpresence->setObjectName(QString::fromUtf8("pb_addpresence"));

        horizontalLayout->addWidget(pb_addpresence);

        pb_modifypresence = new QPushButton(tab);
        pb_modifypresence->setObjectName(QString::fromUtf8("pb_modifypresence"));

        horizontalLayout->addWidget(pb_modifypresence);

        pb_deletepresence = new QPushButton(tab);
        pb_deletepresence->setObjectName(QString::fromUtf8("pb_deletepresence"));

        horizontalLayout->addWidget(pb_deletepresence);


        verticalLayout_7->addLayout(horizontalLayout);

        tv_presences = new QTableView(tab);
        tv_presences->setObjectName(QString::fromUtf8("tv_presences"));
        tv_presences->setStyleSheet(QString::fromUtf8(""));
        tv_presences->setSelectionMode(QAbstractItemView::SingleSelection);
        tv_presences->setSelectionBehavior(QAbstractItemView::SelectRows);
        tv_presences->setSortingEnabled(true);
        tv_presences->verticalHeader()->setVisible(false);

        verticalLayout_7->addWidget(tv_presences);


        gridLayout->addLayout(verticalLayout_7, 0, 1, 1, 1);

        scrollArea = new QScrollArea(tab);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setMaximumSize(QSize(315, 16777215));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 313, 571));
        verticalLayout_3 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        groupBox = new QGroupBox(scrollAreaWidgetContents);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        formLayout = new QFormLayout(groupBox);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_6);

        le_pf_firstname = new QLineEdit(groupBox);
        le_pf_firstname->setObjectName(QString::fromUtf8("le_pf_firstname"));

        formLayout->setWidget(0, QFormLayout::FieldRole, le_pf_firstname);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_5);

        le_pf_lastname = new QLineEdit(groupBox);
        le_pf_lastname->setObjectName(QString::fromUtf8("le_pf_lastname"));

        formLayout->setWidget(1, QFormLayout::FieldRole, le_pf_lastname);

        label_25 = new QLabel(groupBox);
        label_25->setObjectName(QString::fromUtf8("label_25"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_25);

        le_pf_studentnumber = new QLineEdit(groupBox);
        le_pf_studentnumber->setObjectName(QString::fromUtf8("le_pf_studentnumber"));

        formLayout->setWidget(2, QFormLayout::FieldRole, le_pf_studentnumber);

        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        formLayout->setWidget(3, QFormLayout::LabelRole, label);

        cb_pf_training = new QComboBox(groupBox);
        cb_pf_training->setObjectName(QString::fromUtf8("cb_pf_training"));

        formLayout->setWidget(3, QFormLayout::FieldRole, cb_pf_training);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_3);

        cb_pf_option = new QComboBox(groupBox);
        cb_pf_option->setObjectName(QString::fromUtf8("cb_pf_option"));

        formLayout->setWidget(4, QFormLayout::FieldRole, cb_pf_option);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(5, QFormLayout::LabelRole, label_2);

        le_pf_groupnumber = new QLineEdit(groupBox);
        le_pf_groupnumber->setObjectName(QString::fromUtf8("le_pf_groupnumber"));

        formLayout->setWidget(5, QFormLayout::FieldRole, le_pf_groupnumber);

        label_11 = new QLabel(groupBox);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        formLayout->setWidget(6, QFormLayout::LabelRole, label_11);

        le_pf_promotion = new QLineEdit(groupBox);
        le_pf_promotion->setObjectName(QString::fromUtf8("le_pf_promotion"));

        formLayout->setWidget(6, QFormLayout::FieldRole, le_pf_promotion);

        label_10 = new QLabel(groupBox);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        formLayout->setWidget(7, QFormLayout::LabelRole, label_10);

        cb_pf_cardreader = new QComboBox(groupBox);
        cb_pf_cardreader->setObjectName(QString::fromUtf8("cb_pf_cardreader"));

        formLayout->setWidget(7, QFormLayout::FieldRole, cb_pf_cardreader);

        gb_pf_period = new QGroupBox(groupBox);
        gb_pf_period->setObjectName(QString::fromUtf8("gb_pf_period"));
        gb_pf_period->setCheckable(true);
        gb_pf_period->setChecked(true);
        verticalLayout_18 = new QVBoxLayout(gb_pf_period);
        verticalLayout_18->setSpacing(6);
        verticalLayout_18->setContentsMargins(11, 11, 11, 11);
        verticalLayout_18->setObjectName(QString::fromUtf8("verticalLayout_18"));
        label_4 = new QLabel(gb_pf_period);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        verticalLayout_18->addWidget(label_4);

        de_pf_begindate = new QDateEdit(gb_pf_period);
        de_pf_begindate->setObjectName(QString::fromUtf8("de_pf_begindate"));
        de_pf_begindate->setCalendarPopup(true);

        verticalLayout_18->addWidget(de_pf_begindate);

        label_7 = new QLabel(gb_pf_period);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        verticalLayout_18->addWidget(label_7);

        de_pf_enddate = new QDateEdit(gb_pf_period);
        de_pf_enddate->setObjectName(QString::fromUtf8("de_pf_enddate"));
        de_pf_enddate->setCalendarPopup(true);

        verticalLayout_18->addWidget(de_pf_enddate);


        formLayout->setWidget(10, QFormLayout::SpanningRole, gb_pf_period);

        verticalSpacer_6 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        formLayout->setItem(9, QFormLayout::FieldRole, verticalSpacer_6);

        cb_pf_displaynull = new QCheckBox(groupBox);
        cb_pf_displaynull->setObjectName(QString::fromUtf8("cb_pf_displaynull"));

        formLayout->setWidget(11, QFormLayout::SpanningRole, cb_pf_displaynull);


        verticalLayout_3->addWidget(groupBox);

        verticalSpacer = new QSpacerItem(277, 328, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        scrollArea->setWidget(scrollAreaWidgetContents);

        gridLayout->addWidget(scrollArea, 0, 0, 1, 1);

        gridLayout->setColumnStretch(0, 1);

        verticalLayout_2->addLayout(gridLayout);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        verticalLayout_15 = new QVBoxLayout(tab_2);
        verticalLayout_15->setSpacing(6);
        verticalLayout_15->setContentsMargins(11, 11, 11, 11);
        verticalLayout_15->setObjectName(QString::fromUtf8("verticalLayout_15"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        scrollArea_2 = new QScrollArea(tab_2);
        scrollArea_2->setObjectName(QString::fromUtf8("scrollArea_2"));
        scrollArea_2->setMaximumSize(QSize(315, 16777215));
        scrollArea_2->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 313, 571));
        verticalLayout_4 = new QVBoxLayout(scrollAreaWidgetContents_2);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        groupBox_2 = new QGroupBox(scrollAreaWidgetContents_2);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        formLayout_3 = new QFormLayout(groupBox_2);
        formLayout_3->setSpacing(6);
        formLayout_3->setContentsMargins(11, 11, 11, 11);
        formLayout_3->setObjectName(QString::fromUtf8("formLayout_3"));
        label_12 = new QLabel(groupBox_2);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        formLayout_3->setWidget(0, QFormLayout::LabelRole, label_12);

        le_sf_firstname = new QLineEdit(groupBox_2);
        le_sf_firstname->setObjectName(QString::fromUtf8("le_sf_firstname"));

        formLayout_3->setWidget(0, QFormLayout::FieldRole, le_sf_firstname);

        label_13 = new QLabel(groupBox_2);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        formLayout_3->setWidget(1, QFormLayout::LabelRole, label_13);

        le_sf_lastname = new QLineEdit(groupBox_2);
        le_sf_lastname->setObjectName(QString::fromUtf8("le_sf_lastname"));

        formLayout_3->setWidget(1, QFormLayout::FieldRole, le_sf_lastname);

        label_26 = new QLabel(groupBox_2);
        label_26->setObjectName(QString::fromUtf8("label_26"));

        formLayout_3->setWidget(2, QFormLayout::LabelRole, label_26);

        le_sf_studentnumber = new QLineEdit(groupBox_2);
        le_sf_studentnumber->setObjectName(QString::fromUtf8("le_sf_studentnumber"));

        formLayout_3->setWidget(2, QFormLayout::FieldRole, le_sf_studentnumber);

        label_14 = new QLabel(groupBox_2);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        sizePolicy.setHeightForWidth(label_14->sizePolicy().hasHeightForWidth());
        label_14->setSizePolicy(sizePolicy);

        formLayout_3->setWidget(3, QFormLayout::LabelRole, label_14);

        cb_sf_training = new QComboBox(groupBox_2);
        cb_sf_training->setObjectName(QString::fromUtf8("cb_sf_training"));

        formLayout_3->setWidget(3, QFormLayout::FieldRole, cb_sf_training);

        label_30 = new QLabel(groupBox_2);
        label_30->setObjectName(QString::fromUtf8("label_30"));

        formLayout_3->setWidget(4, QFormLayout::LabelRole, label_30);

        cb_sf_option = new QComboBox(groupBox_2);
        cb_sf_option->setObjectName(QString::fromUtf8("cb_sf_option"));

        formLayout_3->setWidget(4, QFormLayout::FieldRole, cb_sf_option);

        label_27 = new QLabel(groupBox_2);
        label_27->setObjectName(QString::fromUtf8("label_27"));

        formLayout_3->setWidget(5, QFormLayout::LabelRole, label_27);

        le_sf_groupnumber = new QLineEdit(groupBox_2);
        le_sf_groupnumber->setObjectName(QString::fromUtf8("le_sf_groupnumber"));

        formLayout_3->setWidget(5, QFormLayout::FieldRole, le_sf_groupnumber);

        label_32 = new QLabel(groupBox_2);
        label_32->setObjectName(QString::fromUtf8("label_32"));

        formLayout_3->setWidget(6, QFormLayout::LabelRole, label_32);

        le_sf_promotion = new QLineEdit(groupBox_2);
        le_sf_promotion->setObjectName(QString::fromUtf8("le_sf_promotion"));

        formLayout_3->setWidget(6, QFormLayout::FieldRole, le_sf_promotion);

        label_28 = new QLabel(groupBox_2);
        label_28->setObjectName(QString::fromUtf8("label_28"));

        formLayout_3->setWidget(7, QFormLayout::LabelRole, label_28);

        le_sf_mail = new QLineEdit(groupBox_2);
        le_sf_mail->setObjectName(QString::fromUtf8("le_sf_mail"));

        formLayout_3->setWidget(7, QFormLayout::FieldRole, le_sf_mail);


        verticalLayout_4->addWidget(groupBox_2);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_2);

        scrollArea_2->setWidget(scrollAreaWidgetContents_2);

        gridLayout_2->addWidget(scrollArea_2, 0, 0, 1, 1);

        verticalLayout_14 = new QVBoxLayout();
        verticalLayout_14->setSpacing(6);
        verticalLayout_14->setObjectName(QString::fromUtf8("verticalLayout_14"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        pb_addstudent = new QPushButton(tab_2);
        pb_addstudent->setObjectName(QString::fromUtf8("pb_addstudent"));

        horizontalLayout_2->addWidget(pb_addstudent);

        pb_modifystudent = new QPushButton(tab_2);
        pb_modifystudent->setObjectName(QString::fromUtf8("pb_modifystudent"));

        horizontalLayout_2->addWidget(pb_modifystudent);

        pb_deletestudent = new QPushButton(tab_2);
        pb_deletestudent->setObjectName(QString::fromUtf8("pb_deletestudent"));

        horizontalLayout_2->addWidget(pb_deletestudent);


        verticalLayout_14->addLayout(horizontalLayout_2);

        tv_students = new QTableView(tab_2);
        tv_students->setObjectName(QString::fromUtf8("tv_students"));
        tv_students->setProperty("showDropIndicator", QVariant(true));
        tv_students->setAlternatingRowColors(true);
        tv_students->setSelectionMode(QAbstractItemView::SingleSelection);
        tv_students->setSelectionBehavior(QAbstractItemView::SelectRows);
        tv_students->setGridStyle(Qt::DashLine);
        tv_students->setSortingEnabled(true);
        tv_students->horizontalHeader()->setCascadingSectionResizes(false);
        tv_students->horizontalHeader()->setProperty("showSortIndicator", QVariant(true));
        tv_students->horizontalHeader()->setStretchLastSection(false);
        tv_students->verticalHeader()->setVisible(false);
        tv_students->verticalHeader()->setCascadingSectionResizes(false);
        tv_students->verticalHeader()->setProperty("showSortIndicator", QVariant(false));

        verticalLayout_14->addWidget(tv_students);


        gridLayout_2->addLayout(verticalLayout_14, 0, 1, 1, 1);

        gridLayout_2->setColumnStretch(0, 1);

        verticalLayout_15->addLayout(gridLayout_2);

        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        verticalLayout_25 = new QVBoxLayout(tab_3);
        verticalLayout_25->setSpacing(6);
        verticalLayout_25->setContentsMargins(11, 11, 11, 11);
        verticalLayout_25->setObjectName(QString::fromUtf8("verticalLayout_25"));
        tabWidget_2 = new QTabWidget(tab_3);
        tabWidget_2->setObjectName(QString::fromUtf8("tabWidget_2"));
        tabWidget_2->setTabPosition(QTabWidget::North);
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        verticalLayout_26 = new QVBoxLayout(tab_4);
        verticalLayout_26->setSpacing(6);
        verticalLayout_26->setContentsMargins(11, 11, 11, 11);
        verticalLayout_26->setObjectName(QString::fromUtf8("verticalLayout_26"));
        gridLayout_5 = new QGridLayout();
        gridLayout_5->setSpacing(6);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));

        gridLayout_5->addLayout(horizontalLayout_8, 2, 1, 1, 1);

        tabWidget_3 = new QTabWidget(tab_4);
        tabWidget_3->setObjectName(QString::fromUtf8("tabWidget_3"));
        tab_6 = new QWidget();
        tab_6->setObjectName(QString::fromUtf8("tab_6"));
        verticalLayout_5 = new QVBoxLayout(tab_6);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        tv_training = new QTableView(tab_6);
        tv_training->setObjectName(QString::fromUtf8("tv_training"));
        tv_training->setSelectionMode(QAbstractItemView::SingleSelection);
        tv_training->setSelectionBehavior(QAbstractItemView::SelectRows);
        tv_training->setSortingEnabled(true);
        tv_training->verticalHeader()->setVisible(false);

        verticalLayout_5->addWidget(tv_training);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        pb_addtraining = new QPushButton(tab_6);
        pb_addtraining->setObjectName(QString::fromUtf8("pb_addtraining"));

        horizontalLayout_3->addWidget(pb_addtraining);

        pb_modifytraining = new QPushButton(tab_6);
        pb_modifytraining->setObjectName(QString::fromUtf8("pb_modifytraining"));

        horizontalLayout_3->addWidget(pb_modifytraining);

        pb_deletetraining = new QPushButton(tab_6);
        pb_deletetraining->setObjectName(QString::fromUtf8("pb_deletetraining"));

        horizontalLayout_3->addWidget(pb_deletetraining);


        verticalLayout_5->addLayout(horizontalLayout_3);

        tabWidget_3->addTab(tab_6, QString());
        tab_7 = new QWidget();
        tab_7->setObjectName(QString::fromUtf8("tab_7"));
        verticalLayout_8 = new QVBoxLayout(tab_7);
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setContentsMargins(11, 11, 11, 11);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        tv_options = new QTableView(tab_7);
        tv_options->setObjectName(QString::fromUtf8("tv_options"));
        tv_options->setSelectionMode(QAbstractItemView::SingleSelection);
        tv_options->setSelectionBehavior(QAbstractItemView::SelectRows);
        tv_options->setSortingEnabled(true);
        tv_options->verticalHeader()->setVisible(false);

        verticalLayout_8->addWidget(tv_options);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        pb_addoption = new QPushButton(tab_7);
        pb_addoption->setObjectName(QString::fromUtf8("pb_addoption"));

        horizontalLayout_9->addWidget(pb_addoption);

        pb_modifyoption = new QPushButton(tab_7);
        pb_modifyoption->setObjectName(QString::fromUtf8("pb_modifyoption"));

        horizontalLayout_9->addWidget(pb_modifyoption);

        pb_deleteoption = new QPushButton(tab_7);
        pb_deleteoption->setObjectName(QString::fromUtf8("pb_deleteoption"));

        horizontalLayout_9->addWidget(pb_deleteoption);


        verticalLayout_8->addLayout(horizontalLayout_9);

        tabWidget_3->addTab(tab_7, QString());

        gridLayout_5->addWidget(tabWidget_3, 0, 0, 2, 1);


        verticalLayout_26->addLayout(gridLayout_5);

        verticalSpacer_4 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_26->addItem(verticalSpacer_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        groupBox_5 = new QGroupBox(tab_4);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        groupBox_5->setEnabled(false);
        verticalLayout_27 = new QVBoxLayout(groupBox_5);
        verticalLayout_27->setSpacing(6);
        verticalLayout_27->setContentsMargins(11, 11, 11, 11);
        verticalLayout_27->setObjectName(QString::fromUtf8("verticalLayout_27"));
        pushButton_10 = new QPushButton(groupBox_5);
        pushButton_10->setObjectName(QString::fromUtf8("pushButton_10"));

        verticalLayout_27->addWidget(pushButton_10);

        label_19 = new QLabel(groupBox_5);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setScaledContents(false);
        label_19->setWordWrap(true);

        verticalLayout_27->addWidget(label_19);


        horizontalLayout_5->addWidget(groupBox_5);

        groupBox_6 = new QGroupBox(tab_4);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        groupBox_6->setEnabled(true);
        verticalLayout_28 = new QVBoxLayout(groupBox_6);
        verticalLayout_28->setSpacing(6);
        verticalLayout_28->setContentsMargins(11, 11, 11, 11);
        verticalLayout_28->setObjectName(QString::fromUtf8("verticalLayout_28"));
        label_20 = new QLabel(groupBox_6);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setWordWrap(true);

        verticalLayout_28->addWidget(label_20);

        label_23 = new QLabel(groupBox_6);
        label_23->setObjectName(QString::fromUtf8("label_23"));

        verticalLayout_28->addWidget(label_23);

        cb_export_student = new QComboBox(groupBox_6);
        cb_export_student->setObjectName(QString::fromUtf8("cb_export_student"));

        verticalLayout_28->addWidget(cb_export_student);

        verticalSpacer_5 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_28->addItem(verticalSpacer_5);

        gb_export_period = new QGroupBox(groupBox_6);
        gb_export_period->setObjectName(QString::fromUtf8("gb_export_period"));
        gb_export_period->setEnabled(true);
        gb_export_period->setCheckable(true);
        gb_export_period->setChecked(false);
        verticalLayout_24 = new QVBoxLayout(gb_export_period);
        verticalLayout_24->setSpacing(6);
        verticalLayout_24->setContentsMargins(11, 11, 11, 11);
        verticalLayout_24->setObjectName(QString::fromUtf8("verticalLayout_24"));
        label_21 = new QLabel(gb_export_period);
        label_21->setObjectName(QString::fromUtf8("label_21"));

        verticalLayout_24->addWidget(label_21);

        de_export_begin = new QDateEdit(gb_export_period);
        de_export_begin->setObjectName(QString::fromUtf8("de_export_begin"));
        de_export_begin->setCalendarPopup(true);

        verticalLayout_24->addWidget(de_export_begin);

        label_22 = new QLabel(gb_export_period);
        label_22->setObjectName(QString::fromUtf8("label_22"));

        verticalLayout_24->addWidget(label_22);

        de_export_end = new QDateEdit(gb_export_period);
        de_export_end->setObjectName(QString::fromUtf8("de_export_end"));
        de_export_end->setCalendarPopup(true);

        verticalLayout_24->addWidget(de_export_end);


        verticalLayout_28->addWidget(gb_export_period);

        pb_exportpresences = new QPushButton(groupBox_6);
        pb_exportpresences->setObjectName(QString::fromUtf8("pb_exportpresences"));

        verticalLayout_28->addWidget(pb_exportpresences, 0, Qt::AlignRight);


        horizontalLayout_5->addWidget(groupBox_6);


        verticalLayout_26->addLayout(horizontalLayout_5);

        tabWidget_2->addTab(tab_4, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName(QString::fromUtf8("tab_5"));
        formLayout_2 = new QFormLayout(tab_5);
        formLayout_2->setSpacing(6);
        formLayout_2->setContentsMargins(11, 11, 11, 11);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        label_8 = new QLabel(tab_5);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_8);

        le_host = new QLineEdit(tab_5);
        le_host->setObjectName(QString::fromUtf8("le_host"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, le_host);

        label_18 = new QLabel(tab_5);
        label_18->setObjectName(QString::fromUtf8("label_18"));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, label_18);

        label_24 = new QLabel(tab_5);
        label_24->setObjectName(QString::fromUtf8("label_24"));

        formLayout_2->setWidget(4, QFormLayout::LabelRole, label_24);

        le_dbname = new QLineEdit(tab_5);
        le_dbname->setObjectName(QString::fromUtf8("le_dbname"));

        formLayout_2->setWidget(5, QFormLayout::LabelRole, le_dbname);

        label_9 = new QLabel(tab_5);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        formLayout_2->setWidget(6, QFormLayout::LabelRole, label_9);

        le_user = new QLineEdit(tab_5);
        le_user->setObjectName(QString::fromUtf8("le_user"));

        formLayout_2->setWidget(7, QFormLayout::LabelRole, le_user);

        label_16 = new QLabel(tab_5);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        formLayout_2->setWidget(8, QFormLayout::LabelRole, label_16);

        le_password = new QLineEdit(tab_5);
        le_password->setObjectName(QString::fromUtf8("le_password"));
        le_password->setEchoMode(QLineEdit::Password);

        formLayout_2->setWidget(9, QFormLayout::LabelRole, le_password);

        verticalSpacer_3 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        formLayout_2->setItem(10, QFormLayout::LabelRole, verticalSpacer_3);

        pb_dbconnect = new QPushButton(tab_5);
        pb_dbconnect->setObjectName(QString::fromUtf8("pb_dbconnect"));

        formLayout_2->setWidget(11, QFormLayout::LabelRole, pb_dbconnect);

        sb_port = new QSpinBox(tab_5);
        sb_port->setObjectName(QString::fromUtf8("sb_port"));
        sb_port->setMaximum(10000);
        sb_port->setValue(3306);

        formLayout_2->setWidget(3, QFormLayout::LabelRole, sb_port);

        tabWidget_2->addTab(tab_5, QString());

        verticalLayout_25->addWidget(tabWidget_2);

        tabWidget->addTab(tab_3, QString());

        verticalLayout->addWidget(tabWidget);

        pb_refresh = new QPushButton(centralWidget);
        pb_refresh->setObjectName(QString::fromUtf8("pb_refresh"));

        verticalLayout->addWidget(pb_refresh, 0, Qt::AlignRight);

        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);
        tabWidget_2->setCurrentIndex(0);
        tabWidget_3->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Badgeuse Polytech", nullptr));
        pb_addpresence->setText(QApplication::translate("MainWindow", "Ajouter", nullptr));
        pb_modifypresence->setText(QApplication::translate("MainWindow", "Modifier", nullptr));
        pb_deletepresence->setText(QApplication::translate("MainWindow", "Supprimer", nullptr));
        groupBox->setTitle(QApplication::translate("MainWindow", "Filtres", nullptr));
        label_6->setText(QApplication::translate("MainWindow", "Pr\303\251nom", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "Nom", nullptr));
        label_25->setText(QApplication::translate("MainWindow", "N\302\260 \303\211tudiant", nullptr));
        label->setText(QApplication::translate("MainWindow", "Formation", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "Option", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "Groupe", nullptr));
        label_11->setText(QApplication::translate("MainWindow", "Promotion", nullptr));
        label_10->setText(QApplication::translate("MainWindow", "Badgeuse", nullptr));
        gb_pf_period->setTitle(QApplication::translate("MainWindow", "P\303\251riode", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "Date d\303\251but", nullptr));
        label_7->setText(QApplication::translate("MainWindow", "Date fin", nullptr));
        cb_pf_displaynull->setText(QApplication::translate("MainWindow", "Afficher les pr\303\251sences non associ\303\251es", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Pr\303\251sences", nullptr));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Filtres", nullptr));
        label_12->setText(QApplication::translate("MainWindow", "Pr\303\251nom", nullptr));
        label_13->setText(QApplication::translate("MainWindow", "Nom", nullptr));
        label_26->setText(QApplication::translate("MainWindow", "N\302\260 \303\211tudiant", nullptr));
        label_14->setText(QApplication::translate("MainWindow", "Formation", nullptr));
        label_30->setText(QApplication::translate("MainWindow", "Option", nullptr));
        label_27->setText(QApplication::translate("MainWindow", "Groupe", nullptr));
        label_32->setText(QApplication::translate("MainWindow", "Promotion", nullptr));
        label_28->setText(QApplication::translate("MainWindow", "Mail", nullptr));
        pb_addstudent->setText(QApplication::translate("MainWindow", "Ajouter", nullptr));
        pb_modifystudent->setText(QApplication::translate("MainWindow", "Modifier", nullptr));
        pb_deletestudent->setText(QApplication::translate("MainWindow", "Supprimer", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Etudiants", nullptr));
        pb_addtraining->setText(QApplication::translate("MainWindow", "Ajouter", nullptr));
        pb_modifytraining->setText(QApplication::translate("MainWindow", "Modifier", nullptr));
        pb_deletetraining->setText(QApplication::translate("MainWindow", "Supprimer", nullptr));
        tabWidget_3->setTabText(tabWidget_3->indexOf(tab_6), QApplication::translate("MainWindow", "Formations", nullptr));
        pb_addoption->setText(QApplication::translate("MainWindow", "Ajouter", nullptr));
        pb_modifyoption->setText(QApplication::translate("MainWindow", "Modifier", nullptr));
        pb_deleteoption->setText(QApplication::translate("MainWindow", "Supprimer", nullptr));
        tabWidget_3->setTabText(tabWidget_3->indexOf(tab_7), QApplication::translate("MainWindow", "Options", nullptr));
        groupBox_5->setTitle(QApplication::translate("MainWindow", "Importer les \303\251tudiants", nullptr));
        pushButton_10->setText(QApplication::translate("MainWindow", "Selectionner le fichier \303\240 importer", nullptr));
        label_19->setText(QApplication::translate("MainWindow", "Action \303\240 faire en d\303\251but d'ann\303\251e.\n"
"S\303\251lectionner le fichier excel (.csv) contenant tous les \303\251tudiants de l'ann\303\251e actuel.", nullptr));
        groupBox_6->setTitle(QApplication::translate("MainWindow", "Exporter les pr\303\251sences", nullptr));
        label_20->setText(QApplication::translate("MainWindow", "Exporte les pr\303\251sences p\303\251riode sous format CSV.", nullptr));
        label_23->setText(QApplication::translate("MainWindow", "Etudiant :", nullptr));
        gb_export_period->setTitle(QApplication::translate("MainWindow", "P\303\251riode", nullptr));
        label_21->setText(QApplication::translate("MainWindow", "Date d\303\251but", nullptr));
        label_22->setText(QApplication::translate("MainWindow", "Date fin", nullptr));
        pb_exportpresences->setText(QApplication::translate("MainWindow", "Exporter", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_4), QApplication::translate("MainWindow", "Gestion", nullptr));
        label_8->setText(QApplication::translate("MainWindow", "Adresse", nullptr));
        le_host->setPlaceholderText(QApplication::translate("MainWindow", "0.0.0.0", nullptr));
        label_18->setText(QApplication::translate("MainWindow", "Port", nullptr));
        label_24->setText(QApplication::translate("MainWindow", "Base de donn\303\251es", nullptr));
        label_9->setText(QApplication::translate("MainWindow", "Utilisateur", nullptr));
        label_16->setText(QApplication::translate("MainWindow", "Password", nullptr));
        pb_dbconnect->setText(QApplication::translate("MainWindow", "Sauvegarder et se connecter", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_5), QApplication::translate("MainWindow", "Base de donn\303\251es", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("MainWindow", "Param\303\250tres", nullptr));
        pb_refresh->setText(QApplication::translate("MainWindow", "Rafra\303\256chir", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
