#include <QDebug>
#include <QFileInfo>

#include "menu.h"
#include "update.h"
 
Menu::Menu(QWidget *parent) : QDialog(parent)
{
qDebug() << "start Menu";
	ui.setupUi(this);
	connect(ui.convert, SIGNAL(clicked()), this, SLOT(convert()));
	connect(ui.list, SIGNAL(textChanged(QString)), this, SLOT(newlist(QString)));
	connect(ui.copyright, SIGNAL(textChanged(QString)), 
						this, SLOT(newcopyright(QString)));

	red.setColor(QPalette::Base,QColor(Qt::red));
	white.setColor(QPalette::Base,QColor(Qt::white));

	newlist(list());
	newcopyright(copyright());
qDebug() << "stop Menu";
}

QString Menu::list() const
{ 	return ui.list->text();		}

QString Menu::copyright() const
{ 	return ui.copyright->text();	}

bool Menu::listFiles(QStringList & listf)
{
qDebug() << "begin listFiles";
qDebug() << list();
	QFile f(list());
	if (!f.open(QFile::ReadOnly))
	{	
qDebug() << "ERROR 001";
		return false;
	}
	QString name;
	QTextStream text(&f);
	while (!text.atEnd())
	{	
		text >> name;
		if (!name.isEmpty()) listf << name;
	}
	f.close();
qDebug() << "end listFiles" << listf;	
	return true;
}

void Menu::convert()
{
	QStringList listfiles;
		if (!listFiles(listfiles))
		{
qDebug() << "ERROR 002";
		}

		int i = 0; 
		while (i<listfiles.size())
		{
			QString fullname = "../" + listfiles[i] + "/" + listfiles[i]; 
// da! ../POT080_000099/POT080_000099.tif

			ui.convert->setText(listfiles[i]);
			ui.convert->repaint();
			ui.convert->update();
			Update* c = new Update(fullname, this);
			delete c;
			++i;
		}
	ui.convert->setText("DONE!");
	ui.convert->setDisabled(true);
}

void Menu::newlist(QString s)
{
	QFileInfo f(s);
	if (f.isFile()) ui.list->setPalette(white);
	else ui.list->setPalette(red);
}
	
void Menu::newcopyright(QString s)
{
	QFileInfo f(s);
	if (f.isFile()) ui.copyright->setPalette(white);
	else ui.copyright->setPalette(red);
}

bool Menu::scandata() const
{
	return ui.scandata->isChecked();
}

bool Menu::im() const
{
	return ui.ImageMagick->isChecked();
}
