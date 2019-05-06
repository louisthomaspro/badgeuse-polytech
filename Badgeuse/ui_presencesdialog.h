/********************************************************************************
** Form generated from reading UI file 'presencesdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PRESENCESDIALOG_H
#define UI_PRESENCESDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_PresencesDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QLabel *l_title;
    QSpacerItem *verticalSpacer;
    QFormLayout *formLayout;
    QLabel *label_3;
    QDateTimeEdit *dte_entry;
    QLabel *label_2;
    QDateTimeEdit *dte_exit;
    QLabel *label_10;
    QComboBox *cb_cardReader;
    QLabel *label_5;
    QComboBox *cb_student;
    QSpacerItem *verticalSpacer_2;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *PresencesDialog)
    {
        if (PresencesDialog->objectName().isEmpty())
            PresencesDialog->setObjectName(QString::fromUtf8("PresencesDialog"));
        PresencesDialog->resize(364, 229);
        PresencesDialog->setMaximumSize(QSize(364, 319));
        PresencesDialog->setSizeGripEnabled(false);
        PresencesDialog->setModal(true);
        verticalLayout_2 = new QVBoxLayout(PresencesDialog);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setSizeConstraint(QLayout::SetDefaultConstraint);
        l_title = new QLabel(PresencesDialog);
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
        label_3 = new QLabel(PresencesDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_3);

        dte_entry = new QDateTimeEdit(PresencesDialog);
        dte_entry->setObjectName(QString::fromUtf8("dte_entry"));
        dte_entry->setCalendarPopup(true);

        formLayout->setWidget(0, QFormLayout::FieldRole, dte_entry);

        label_2 = new QLabel(PresencesDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        dte_exit = new QDateTimeEdit(PresencesDialog);
        dte_exit->setObjectName(QString::fromUtf8("dte_exit"));
        dte_exit->setCalendarPopup(true);

        formLayout->setWidget(1, QFormLayout::FieldRole, dte_exit);

        label_10 = new QLabel(PresencesDialog);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_10);

        cb_cardReader = new QComboBox(PresencesDialog);
        cb_cardReader->setObjectName(QString::fromUtf8("cb_cardReader"));

        formLayout->setWidget(2, QFormLayout::FieldRole, cb_cardReader);

        label_5 = new QLabel(PresencesDialog);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_5);

        cb_student = new QComboBox(PresencesDialog);
        cb_student->setObjectName(QString::fromUtf8("cb_student"));

        formLayout->setWidget(3, QFormLayout::FieldRole, cb_student);


        verticalLayout_2->addLayout(formLayout);

        verticalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalSpacer_2);

        buttonBox = new QDialogButtonBox(PresencesDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::SaveAll);

        verticalLayout_2->addWidget(buttonBox);


        retranslateUi(PresencesDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), PresencesDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), PresencesDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(PresencesDialog);
    } // setupUi

    void retranslateUi(QDialog *PresencesDialog)
    {
        PresencesDialog->setWindowTitle(QApplication::translate("PresencesDialog", "Etudiant", nullptr));
        l_title->setText(QApplication::translate("PresencesDialog", "Pr\303\251sence", nullptr));
        label_3->setText(QApplication::translate("PresencesDialog", "Date d'entr\303\251e", nullptr));
        label_2->setText(QApplication::translate("PresencesDialog", "Date de sortie", nullptr));
        label_10->setText(QApplication::translate("PresencesDialog", "Badgeuse", nullptr));
        label_5->setText(QApplication::translate("PresencesDialog", "Etudiant", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PresencesDialog: public Ui_PresencesDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRESENCESDIALOG_H
