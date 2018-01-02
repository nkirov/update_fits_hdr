#include <QFileInfo>

#include "update.h"

Update::Update(QString f, const Menu *menu)
{
qDebug() << "start Update";
	typef = 
 "biiiibiibssssssssdssdssdssdsissssssdsssddssssisdddsiddiiddssssss";
//1234567890123456789012345678901234567890123456789012345678901234567890	
	fname = f;
	nameCo = menu->copyright();
	scandata = menu->scandata();
	t.start();   		// time

	if (!readFits()) {
qDebug() << "ERROR 1";	return;	}

	if (!readHdrFile()) {
qDebug() << "ERROR 2";	return;	}

    if (menu->im())
    {
        if (!changeHdrIM()) {
qDebug() << "ERROR 3";	return;	}
    }
    else
    {
        if (!changeHdr()) {
qDebug() << "ERROR 3";	return;	}
    }
	if (!copyright()) {
qDebug() << "ERROR 4"; return; }

	if (!writeFits()) {
qDebug() << "ERROR 5";	return;	}

	if (!writeHdr()) {
qDebug() << "ERROR 6";	return;	}		

	qint64 tms = t.elapsed();  // time
qDebug() << "Time: " << tms;
	QTime t1(0,0,0);
	t1 = t1.addMSecs(tms);
qDebug() << t1.toString(Qt::TextDate);
qDebug() << "stop Update";
}

Update::~Update()
{
	delete [] image;
	delete [] hdr;
}
/*************************************************/

bool Update::readFits()
{
qDebug() << "begin readFits" <<  fname;	
	QFile f(fname + ".fits");
	if (!f.open(QFile::ReadOnly))
	{	
qDebug() << "ERROR";
		return false;
	}

	hdrSize = 2880;
/*	
	char * hdr = new char[hdrSize];
	f.read(hdr, hdrSize);
*/
	char * hdr = new char[81];
	QString s;
	int i = 0;
	while (s.left(3) != "END")
	{
		f.read(hdr, 80);
		*hdr += '\0';
		s = QString(hdr);
qDebug() << s;
		hdr2list << s;
		i++;
	}	

	int k = 80*i%2880;
qDebug() << k;	
	k = 2880 - k;
qDebug() << k << "f.pos=" << f.pos();	
	char * rem = new char[2880];
	f.read(rem, k);
qDebug() << k << "f.pos=" << f.pos() << "f.size=" << f.size();	
	imageSize = f.size() - 80*i - k; // in bytes
qDebug() << "imageSize" << imageSize;
qDebug() << "Reading...";

	image = new char[imageSize];
// qDebug() << f.read(ch, imageSize*2);
	for (int i=0; i<imageSize; i++)
		f.getChar(&image[i]);
qDebug() << "f.pos=" << f.pos();	
	f.close();
qDebug() << "end readFits";	
	return true;
}

void Update::convertHdr()
{
qDebug() << "begin Update::convertHdr";
// convert to one string and char*
	QString allhdr = hdrlist.join("");
	hdrSize = allhdr.length();
	hdr = new char[hdrSize];
	for (int i=0; i < hdrSize; i++)
		hdr[i] = allhdr[i].toAscii();
qDebug() << "end Update::convertHdr hdrSize=" << hdrSize;
}

bool Update::writeFits()
{
qDebug() << "begin Update::writeFits";
	QFile f(fname + "_0.fits");
	if (!f.open(QIODevice::WriteOnly))
	{	
qDebug() << "ERROR";	
		return false;
	}

	convertHdr();
qDebug() << "f.pos = " << f.pos();
	f.write(hdr, hdrSize);
	char space = ' ';
	int rest = (2880 - f.pos()%2880);
	for (int i = 0; i < rest; i++) f.putChar(space);

qDebug() << "f.pos = " << f.pos() << "imageSize=" << imageSize;	
qDebug() << "Writing...";
	for (int i=0; i<imageSize; i++)
		f.putChar(image[i]);
//qDebug() << f.write(ch, imageSize*2); 
qDebug() << "f.pos =" << f.pos();

	char ch0 = static_cast<char>(0);
	rest = (2880 - f.pos()%2880);
	for (int i = 0; i < rest; i++) f.putChar(ch0);
qDebug() << "f.pos = " << f.pos();
	f.close();
qDebug() << "end Update::writeFits";
	return true;
}
/**************************************************************/
// OK
bool Update::readHdrFile()
{
qDebug() << "begin Update::readHdrFile";
	QFile f(fname + ".hdr");
qDebug() << fname + ".hdr";	
	if (!f.open(QFile::ReadOnly))
	{	
qDebug() << "ERROR file -- missing!";
		return false;
	}
	hdrlist.clear();
	QTextStream text(&f);
	while (!text.atEnd())
	{
		QString line = text.readLine();
		while (line.length() < 80) line.append(" ");
qDebug() << line.length() << line;
		hdrlist << line; 
	}
	f.close();
// remove DIR and END
	hdrlist.removeLast(); 	hdrlist.removeLast(); 
qDebug() << "end Update::readHdrFile hdrlist.size()=" << hdrlist.size();
	return true;
}
/****************************************************************/
QString Update::value(QString s)
{
	foreach(QString ss, hdr2list)
	{
		if(s == ss.left(8)) return ss;		
	}
	return QString();
}

bool Update::changeHdr()
{
qDebug() << "begin Update::changeHdr";
// change sizes
	hdrlist[3].replace(0,31,hdr2list[3].left(31));
qDebug() << hdrlist[3];
	hdrlist[4].replace(0,31,hdr2list[4].left(31));
qDebug() << hdrlist[4];
	QString ss;
	ss = value("BZERO   ");
	hdrlist[6].replace(0,31,ss.left(31));
qDebug() << hdrlist[6];	
//	hdrlist[6].replace(0,31,hdr2list[6].left(31));

	hdrlist[50] = value("SCANNER "); 
qDebug() << hdrlist[50];	
	ss = value("SCANFOC ");
	hdrlist[57].replace(0,31,ss.left(31)); 
qDebug() << hdrlist[57];	
	ss = scandata?value("SCANDATE"):value("DATE    ");
	if (!ss.isEmpty())
	{	
		ss = ss.mid(8,23);
		hdrlist[58].replace(8,23,ss); 
	}
qDebug() << hdrlist[58];		
	ss = value("AUTHOR  ");
	ss = ss.left(ss.indexOf('/'));
	ss = ss + "/ author of scan";
    	int len = ss.size();
	for (int i=len; i < 80; i++) ss += " ";
	hdrlist[59] = ss;	
qDebug() << hdrlist[59] << "len=" << ss.size();

	hdrlist[9].replace(10, 20, "'" + QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
qDebug() << hdrlist[9];

	ss = value("CTYPE1  ");
	if (ss.isEmpty()) return true;
	int ii = hdr2list.indexOf(ss);
qDebug() << ii << ss;
	for(int i=ii; i < hdr2list.size()-1; i++)
		hdrlist << hdr2list[i];
	return true;
}

bool Update::changeHdrIM()
{
qDebug() << "begin Update::changeHdrIM";
    // change sizes
	hdrlist[3].replace(0,31,hdr2list[3].left(31));
qDebug() << hdrlist[3];
	hdrlist[4].replace(0,31,hdr2list[4].left(31));
qDebug() << hdrlist[4];
	return true;
}
/*************************************************/
bool Update::writeHdr()
{
qDebug() << "begin Update::writeHdr ";
	QFile f(fname + ".hdrf");
	if (!f.open(QFile::WriteOnly))
	{	
qDebug() << "ERROR";
		return false;
	}
	QTextStream text(&f);
	for (int i=0; i < hdrlist.size(); i++)
		text <<  hdrlist[i] << endl;
	f.close();
qDebug() << "end Update::writeHdr";	
	return true;
}
/**************************************************************/
bool Update::copyright()
{
// include 66. (copyright)
qDebug() << "begin copyright";
	QFile fc(nameCo);
	if (!fc.open(QFile::ReadOnly))
	{	
qDebug() << "ERROR 504";
		return false;
	}
	QTextStream com(&fc);
	while (!com.atEnd())
	{
		QString line = com.readLine();
		while (!line.isEmpty() && line[0] == ' ') line = line.remove(0,1);
		line = "        " + line;
		while (line.length() < 80) line.append(" ");
		hdrlist << line; 
	}
	fc.close();

	QString line = "END"; 
	if (hdrlist[hdrlist.size() - 1].left(3) != line)
	{
		while (line.length() < 80) line.append(" ");
		hdrlist << line;
	}
qDebug() << "end copyright, hdrlist.size()=" << hdrlist.size();
	return true;
}

