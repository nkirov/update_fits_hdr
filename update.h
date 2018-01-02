#ifndef UPDATE_H
#define UPDATE_H

#include <QString>
#include <QDateTime>
#include <QStringList>
#include <QDebug>
#include <QFile>

#include "menu.h"

class Update 
{
	public:
		typedef short uint; 
		Update(QString, const Menu*);
		~Update();

		bool readFits();
		bool readHdrFile();
		bool changeHdr();
        bool changeHdrIM();
		bool writeHdr();
		bool writeFits();
	private:
		QString typef;
		char * image;
		qint64 imageSize; // in bytes

		char * hdr;
		qint64 hdrSize;   // in bytes
		QStringList hdrlist; // from file + correction + to FITS & file
		qint64 fdr2size;
		QStringList hdr2list; // from FITS

		void convertHdr();
		bool copyright();
		QString value(QString);

		QString fname;
		QString nameCo;
		bool scandata;
		QTime t;
};
#endif
