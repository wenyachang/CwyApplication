
#include <QtCore/QCoreApplication>
#include <QUrl>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QFile>
#include <QTextStream>
#include <QTextCodec>
#include <QString>       
#include <QRegExp>

//��ҳ��ַ      
const QString URLSTR = "http://cclawnet.com/shijiezpj/zw7/04/zw1/mydoc001.htm";
//������ҳ������ļ�      
const QString FILE_NAME = "code.txt";

int main(int argc, char *argv[])
{
	QCoreApplication app(argc, argv);
	QUrl url(URLSTR);
	QNetworkAccessManager manager;
	QEventLoop loop;
	QNetworkReply *reply;

	qDebug() << "Reading html code form " << URLSTR;
	reply = manager.get(QNetworkRequest(url));
	//���������������ɺ��˳����¼�ѭ��      
	QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
	//�������¼�ѭ��      
	loop.exec();

	//��ȡԴ�룬���ļ�  
	QFile file(FILE_NAME);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		qDebug() << "Cannot open the file: " << FILE_NAME;
		return 0;
	}
	QTextStream out(&file);
	QString codeContent = QString::fromLocal8Bit(reply->readAll());
	
	out << codeContent  << endl;
	file.close();

	QRegExp rx("<(.*)>");
	QRegExp rx1("\\{(.*)\\}");
	QRegExp rx2("&nbsp;");
	QRegExp rx3("body");
	rx.setMinimal(true);
	rx1.setMinimal(true);
	rx2.setMinimal(true);
	rx3.setMinimal(true);
	
	codeContent.remove(rx);
	codeContent.remove(rx1);
	codeContent.remove(rx2);
	codeContent.remove(rx3);
	codeContent.remove(" ");
	codeContent.trimmed();
	QFile file1("result.txt");
	if (!file1.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		return 0;
	}
	QTextStream oue(&file1);
	oue << codeContent << endl;
	file1.close();

	return 0;
}
