/********************************************************************************
** Form generated from reading UI file 'menu.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MENU_H
#define UI_MENU_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_menu
{
public:
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLineEdit *list;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *copyright;
    QPushButton *convert;
    QGroupBox *groupBox;
    QRadioButton *data;
    QRadioButton *scandata;
    QGroupBox *groupBox_2;
    QRadioButton *CdC;
    QRadioButton *ImageMagick;

    void setupUi(QDialog *menu)
    {
        if (menu->objectName().isEmpty())
            menu->setObjectName(QString::fromUtf8("menu"));
        menu->resize(399, 224);
        gridLayoutWidget = new QWidget(menu);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 20, 381, 80));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        list = new QLineEdit(gridLayoutWidget);
        list->setObjectName(QString::fromUtf8("list"));
        QFont font;
        font.setPointSize(11);
        list->setFont(font);

        gridLayout->addWidget(list, 0, 1, 1, 1);

        label = new QLabel(gridLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setFont(font);
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(gridLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font);

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        copyright = new QLineEdit(gridLayoutWidget);
        copyright->setObjectName(QString::fromUtf8("copyright"));
        copyright->setFont(font);

        gridLayout->addWidget(copyright, 1, 1, 1, 1);

        convert = new QPushButton(menu);
        convert->setObjectName(QString::fromUtf8("convert"));
        convert->setGeometry(QRect(10, 190, 381, 23));
        convert->setFont(font);
        groupBox = new QGroupBox(menu);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 100, 120, 80));
        data = new QRadioButton(groupBox);
        data->setObjectName(QString::fromUtf8("data"));
        data->setGeometry(QRect(10, 30, 82, 18));
        data->setFont(font);
        scandata = new QRadioButton(groupBox);
        scandata->setObjectName(QString::fromUtf8("scandata"));
        scandata->setGeometry(QRect(10, 50, 177, 18));
        scandata->setFont(font);
        scandata->setChecked(true);
        groupBox_2 = new QGroupBox(menu);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(230, 100, 161, 80));
        CdC = new QRadioButton(groupBox_2);
        CdC->setObjectName(QString::fromUtf8("CdC"));
        CdC->setGeometry(QRect(10, 30, 102, 20));
        ImageMagick = new QRadioButton(groupBox_2);
        ImageMagick->setObjectName(QString::fromUtf8("ImageMagick"));
        ImageMagick->setGeometry(QRect(10, 50, 111, 20));
        ImageMagick->setChecked(true);

        retranslateUi(menu);

        QMetaObject::connectSlotsByName(menu);
    } // setupUi

    void retranslateUi(QDialog *menu)
    {
        menu->setWindowTitle(QApplication::translate("menu", "UpdateFitsHdr", 0, QApplication::UnicodeUTF8));
        list->setText(QApplication::translate("menu", "list.txt", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("menu", "List file name:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("menu", "Copyright file name:", 0, QApplication::UnicodeUTF8));
        copyright->setText(QApplication::translate("menu", "project_CdC.txt", 0, QApplication::UnicodeUTF8));
        convert->setText(QApplication::translate("menu", "Convert", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("menu", "GroupBox", 0, QApplication::UnicodeUTF8));
        data->setText(QApplication::translate("menu", "DATA", 0, QApplication::UnicodeUTF8));
        scandata->setText(QApplication::translate("menu", "SCANDATA", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("menu", "From", 0, QApplication::UnicodeUTF8));
        CdC->setText(QApplication::translate("menu", "CdC", 0, QApplication::UnicodeUTF8));
        ImageMagick->setText(QApplication::translate("menu", "ImageMagick", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class menu: public Ui_menu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MENU_H
