
#include <QtWidgets/QApplication>
#include <QtCore/QTextCodec>
#include <QtCore/QDebug>
#include <QString>


int main(int argc, char *argv[])
{
	QTextCodec* gbk = QTextCodec::codecForName("GB18030");

	QTextCodec* code = QTextCodec::codecForLocale();
	QString exeDir = code->toUnicode(QByteArray(argv[0]));
	qDebug() << "==================================================================";
	qDebug() << "";
	qDebug() << QString::fromLocal8Bit(" Æô¶¯³É¹¦£¡");
	qDebug() << exeDir;
	qDebug() << "";
	qDebug() << "==================================================================";


	QApplication a(argc, argv);

	return a.exec();
}
