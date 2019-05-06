/********************************************************************************
** Form generated from reading UI file 'trainingdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRAININGDIALOG_H
#define UI_TRAININGDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_TrainingDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QLabel *l_title;
    QSpacerItem *verticalSpacer;
    QFormLayout *formLayout;
    QLabel *label_3;
    QLineEdit *le_name;
    QSpacerItem *verticalSpacer_2;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *TrainingDialog)
    {
        if (TrainingDialog->objectName().isEmpty())
            TrainingDialog->setObjectName(QString::fromUtf8("TrainingDialog"));
        TrainingDialog->resize(364, 140);
        TrainingDialog->setMaximumSize(QSize(364, 319));
        TrainingDialog->setSizeGripEnabled(false);
        TrainingDialog->setModal(true);
        verticalLayout_2 = new QVBoxLayout(TrainingDialog);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setSizeConstraint(QLayout::SetDefaultConstraint);
        l_title = new QLabel(TrainingDialog);
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
        label_3 = new QLabel(TrainingDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_3);

        le_name = new QLineEdit(TrainingDialog);
        le_name->setObjectName(QString::fromUtf8("le_name"));

        formLayout->setWidget(0, QFormLayout::FieldRole, le_name);


        verticalLayout_2->addLayout(formLayout);

        verticalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalSpacer_2);

        buttonBox = new QDialogButtonBox(TrainingDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::SaveAll);

        verticalLayout_2->addWidget(buttonBox);


        retranslateUi(TrainingDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), TrainingDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), TrainingDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(TrainingDialog);
    } // setupUi

    void retranslateUi(QDialog *TrainingDialog)
    {
        TrainingDialog->setWindowTitle(QApplication::translate("TrainingDialog", "Etudiant", nullptr));
        l_title->setText(QApplication::translate("TrainingDialog", "Formation", nullptr));
        label_3->setText(QApplication::translate("TrainingDialog", "Nom", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TrainingDialog: public Ui_TrainingDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRAININGDIALOG_H
