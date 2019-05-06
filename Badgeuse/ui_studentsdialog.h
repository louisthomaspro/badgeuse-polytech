/********************************************************************************
** Form generated from reading UI file 'studentsdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STUDENTSDIALOG_H
#define UI_STUDENTSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_StudentsDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QLabel *l_title;
    QSpacerItem *verticalSpacer;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *le_studentNumber;
    QLabel *label_3;
    QLineEdit *le_firstname;
    QLabel *label_2;
    QLineEdit *le_lastname;
    QLabel *label_10;
    QLineEdit *le_mail;
    QLabel *label_5;
    QSpinBox *sb_degreeYear;
    QLabel *label_4;
    QComboBox *cb_trainingName;
    QLabel *label_6;
    QSpinBox *sb_group;
    QLabel *label_7;
    QLabel *l_optionsList;
    QLabel *label_8;
    QComboBox *cb_rfidNumber;
    QLabel *label_11;
    QSpacerItem *verticalSpacer_2;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *StudentsDialog)
    {
        if (StudentsDialog->objectName().isEmpty())
            StudentsDialog->setObjectName(QString::fromUtf8("StudentsDialog"));
        StudentsDialog->resize(510, 377);
        StudentsDialog->setMaximumSize(QSize(510, 377));
        StudentsDialog->setSizeGripEnabled(false);
        StudentsDialog->setModal(true);
        verticalLayout_2 = new QVBoxLayout(StudentsDialog);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setSizeConstraint(QLayout::SetDefaultConstraint);
        l_title = new QLabel(StudentsDialog);
        l_title->setObjectName(QString::fromUtf8("l_title"));
        QFont font;
        font.setPointSize(12);
        l_title->setFont(font);
        l_title->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(l_title);

        verticalSpacer = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalSpacer);

        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label = new QLabel(StudentsDialog);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        le_studentNumber = new QLineEdit(StudentsDialog);
        le_studentNumber->setObjectName(QString::fromUtf8("le_studentNumber"));
        le_studentNumber->setMaxLength(8);

        formLayout->setWidget(0, QFormLayout::FieldRole, le_studentNumber);

        label_3 = new QLabel(StudentsDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_3);

        le_firstname = new QLineEdit(StudentsDialog);
        le_firstname->setObjectName(QString::fromUtf8("le_firstname"));

        formLayout->setWidget(1, QFormLayout::FieldRole, le_firstname);

        label_2 = new QLabel(StudentsDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_2);

        le_lastname = new QLineEdit(StudentsDialog);
        le_lastname->setObjectName(QString::fromUtf8("le_lastname"));

        formLayout->setWidget(2, QFormLayout::FieldRole, le_lastname);

        label_10 = new QLabel(StudentsDialog);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_10);

        le_mail = new QLineEdit(StudentsDialog);
        le_mail->setObjectName(QString::fromUtf8("le_mail"));

        formLayout->setWidget(3, QFormLayout::FieldRole, le_mail);

        label_5 = new QLabel(StudentsDialog);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_5);

        sb_degreeYear = new QSpinBox(StudentsDialog);
        sb_degreeYear->setObjectName(QString::fromUtf8("sb_degreeYear"));
        sb_degreeYear->setMinimum(2000);
        sb_degreeYear->setMaximum(9999);

        formLayout->setWidget(4, QFormLayout::FieldRole, sb_degreeYear);

        label_4 = new QLabel(StudentsDialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        formLayout->setWidget(5, QFormLayout::LabelRole, label_4);

        cb_trainingName = new QComboBox(StudentsDialog);
        cb_trainingName->setObjectName(QString::fromUtf8("cb_trainingName"));

        formLayout->setWidget(5, QFormLayout::FieldRole, cb_trainingName);

        label_6 = new QLabel(StudentsDialog);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        formLayout->setWidget(6, QFormLayout::LabelRole, label_6);

        sb_group = new QSpinBox(StudentsDialog);
        sb_group->setObjectName(QString::fromUtf8("sb_group"));
        sb_group->setMinimum(1);

        formLayout->setWidget(6, QFormLayout::FieldRole, sb_group);

        label_7 = new QLabel(StudentsDialog);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        formLayout->setWidget(7, QFormLayout::LabelRole, label_7);

        l_optionsList = new QLabel(StudentsDialog);
        l_optionsList->setObjectName(QString::fromUtf8("l_optionsList"));

        formLayout->setWidget(7, QFormLayout::FieldRole, l_optionsList);

        label_8 = new QLabel(StudentsDialog);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        formLayout->setWidget(8, QFormLayout::LabelRole, label_8);

        cb_rfidNumber = new QComboBox(StudentsDialog);
        cb_rfidNumber->setObjectName(QString::fromUtf8("cb_rfidNumber"));

        formLayout->setWidget(8, QFormLayout::FieldRole, cb_rfidNumber);

        label_11 = new QLabel(StudentsDialog);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        formLayout->setWidget(9, QFormLayout::FieldRole, label_11);


        verticalLayout_2->addLayout(formLayout);

        verticalSpacer_2 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalSpacer_2);

        buttonBox = new QDialogButtonBox(StudentsDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::SaveAll);

        verticalLayout_2->addWidget(buttonBox);

        QWidget::setTabOrder(le_studentNumber, le_firstname);
        QWidget::setTabOrder(le_firstname, le_lastname);
        QWidget::setTabOrder(le_lastname, le_mail);
        QWidget::setTabOrder(le_mail, sb_degreeYear);
        QWidget::setTabOrder(sb_degreeYear, cb_trainingName);
        QWidget::setTabOrder(cb_trainingName, sb_group);
        QWidget::setTabOrder(sb_group, cb_rfidNumber);

        retranslateUi(StudentsDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), StudentsDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), StudentsDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(StudentsDialog);
    } // setupUi

    void retranslateUi(QDialog *StudentsDialog)
    {
        StudentsDialog->setWindowTitle(QApplication::translate("StudentsDialog", "Etudiant", nullptr));
        l_title->setText(QApplication::translate("StudentsDialog", "Etudiant", nullptr));
        label->setText(QApplication::translate("StudentsDialog", "Num\303\251ro \303\251tudiant", nullptr));
        le_studentNumber->setInputMask(QString());
        le_studentNumber->setPlaceholderText(QApplication::translate("StudentsDialog", "21708111", nullptr));
        label_3->setText(QApplication::translate("StudentsDialog", "Pr\303\251nom", nullptr));
        label_2->setText(QApplication::translate("StudentsDialog", "Nom", nullptr));
        label_10->setText(QApplication::translate("StudentsDialog", "Mail", nullptr));
        label_5->setText(QApplication::translate("StudentsDialog", "Ann\303\251e dipl\303\264me", nullptr));
        label_4->setText(QApplication::translate("StudentsDialog", "Promotion", nullptr));
        label_6->setText(QApplication::translate("StudentsDialog", "Groupe", nullptr));
        label_7->setText(QApplication::translate("StudentsDialog", "Option", nullptr));
        l_optionsList->setText(QApplication::translate("StudentsDialog", "optionsList", nullptr));
        label_8->setText(QApplication::translate("StudentsDialog", "Num\303\251ro Rfid*", nullptr));
        label_11->setText(QApplication::translate("StudentsDialog", "* Les pr\303\251sences li\303\251es \303\240 cette carte seront affect\303\251 \303\240 l'utilisateur.", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StudentsDialog: public Ui_StudentsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STUDENTSDIALOG_H
