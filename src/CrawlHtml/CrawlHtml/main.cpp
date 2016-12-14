
#include <QtCore/QCoreApplication>
#include <QUrl>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QFile>
#include <QTextStream>
#include <QTextCodec>
#include <QString>       

//��ҳ��ַ      
const QString URLSTR = "http://wx.cclawnet.com/worldmz/%E3%80%90%E7%BE%8E%E3%80%91%E7%8E%9B%E6%A0%BC%E4%B8%BD%E7%89%B9%C2%B7%E7%B1%B3%E5%88%87%E5%B0%94%EF%BC%9A%E9%A3%98/p001.htm";
//������ҳ������ļ�      
const QString FILE_NAME = "code.txt";

int main(int argc, char *argv[])
{
	QTextCodec* gbk = QTextCodec::codecForName("GB18030");
	QTextCodec::setCodecForLocale(gbk);
	QTextCodec* code = QTextCodec::codecForLocale();

	QCoreApplication app(argc, argv);
	QUrl url(URLSTR);
	QNetworkAccessManager manager;
	QEventLoop loop;
	QTextCodec *codec;
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

	//����ȡ������ҳԴ��д���ļ�  
	//һ��Ҫע��������⣬��������׳��������  
	//codec = QTextCodec::codecForHtml(reply->readAll());
	codeContent = code->toUnicode(reply->readAll());



	out.setCodec(codec);
	out << codeContent << endl;
	file.close();
	qDebug() << "Finished, the code have written to " << FILE_NAME;
	return 0;
}
