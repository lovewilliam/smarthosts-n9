/*
 * 2012 by lovewilliam <lovewilliam@gmail.com>
 */

#include "utilengine.h"

#include <unistd.h>
#include <sys/types.h>


#include <QDateTime>
#include <QDate>
#include <QString>
#include <QStringList>
#include <QDataStream>
#include <QSettings>
#include <QNetworkRequest>
#include <QFile>

#include <QDebug>

//TODO! test if run as root!

UtilEngine::UtilEngine()
{
	ctx = NULL;
	networkManager = new QNetworkAccessManager(this);
	connect(networkManager, SIGNAL(finished(QNetworkReply*)),
		this, SLOT(slot_replyFinished(QNetworkReply*)));
	settings = new QSettings(QSettings::SystemScope,"bss","smarthosts",this);
	items = new QVector<QStringList*>;
	if(QFile::exists(SAVED_HOSTS_FILE))
	{
		slot_parseHostsFile(SAVED_HOSTS_FILE);
	}else
	{
		slot_updateSavedHostFile();
	}
	//FOR DEBUG!
//	qDebug()<<getTitles();
//	qDebug()<<*(QStringList*)(getItems()->at(0));
//	slot_writeHosts();
}

UtilEngine::~UtilEngine()
{
}

bool UtilEngine::isRoot()
{
	if(getuid()==0)
	{
		return true;
	}
	return false;
}

void UtilEngine::setQMLContext(QDeclarativeContext* _ctx)
{
	ctx = _ctx;
}

QList<QObject*> UtilEngine::getCheckBoxItems()
{
	ui_itemList.clear();
	for(int i = 0;i<titles.count();i++)
	{
		QString temp = titles.at(i);
		bool checked = settings->value(QString("hosts/")+temp).toBool();
		ui_itemList.append(new DataObject(temp, checked));
		connect(ui_itemList.last(),SIGNAL(tickChanged(QString,bool)),
			this,SLOT(slot_tickChanged(QString,bool)));
	}
	return ui_itemList;
}

QStringList UtilEngine::getTitles()
{
//	qDebug()<<"BG:Get titles:"<<titles;
	return titles;
}

QVector<QStringList*>* UtilEngine::getItems()
{
	return items;
}

QString UtilEngine::getLastUpdateTime()
{
	lastUpdate = settings->value("lastUpdate").toDateTime();
//	qDebug()<<"lastUpdate:"<<lastUpdate;
	return lastUpdate.toString("yy-MM-dd HH:mm");
}

QString UtilEngine::getHostsDate()
{
	hostsDate = settings->value("hostsDate").toDateTime();
	return hostsDate.toString("yy-MM-dd HH:mm");
}

void UtilEngine::slot_updateSavedHostFile()
{
	//Download hosts file and store in SAVED_HOSTS_FILE
	QUrl targetUrl;
	if(settings->value("hosts_url","PC").toString()=="PC")
	{
		targetUrl = HOSTS_URL;
	}else if(settings->value("hosts_url").toString()=="ANDROID")
	{
		targetUrl = HOSTS_ANDROID;
	}else if(settings->value("hosts_url").toString()=="IOS")
	{
		targetUrl = HOSTS_IOS;
	}else
	{
		targetUrl = settings->value("hosts_url").toString();
	}

	slot_downloadProgress(0,100);
	QNetworkReply* reply = networkManager->get(QNetworkRequest(QUrl(HOSTS_URL)));
	connect(reply,SIGNAL(downloadProgress(qint64,qint64)),
		this,SLOT(slot_downloadProgress(qint64,qint64)));
}

void UtilEngine::slot_writeHosts()
{
	QStringList list;
	for(int i = 0;i<titles.count();i++)
	{
		QString temp = titles.at(i);
		if(settings->value(QString("hosts/")+temp).toBool())
		{
			list.append(temp);
		}
	}
	slot_writeHosts(list);
}

void UtilEngine::slot_writeCleanHosts()
{
	for(int i = 0;i<titles.count();i++)
	{
		QString temp = titles.at(i);
		settings->setValue(QString("hosts/")+temp,false);
	}
	settings->sync();
	slot_writeHosts(QStringList());
	slot_resetUIItems();
}

void UtilEngine::slot_writeHosts(QStringList list)
{
//	QFile file("/tmp/fakehosts");
	QFile file("/etc/hosts");
	if(file.open(QIODevice::WriteOnly | QIODevice::Truncate))
	{
		QTextStream out(&file);
		if(list.count()==0)
		{
			out<<"127.0.0.1 RM680 localhost\n";
			file.close();
			emit signal_writeHosts_done();
			return;
		}
		out<<"#UPDATE:"<<getHostsDate()<<"\n";
		out<<"#This file is generated by smarthosts\n"
			"#!!DO NOT EDIT THIS FILE!!\n"
			"#!!ALL MODIFICATION WILL BE ERASED!!\n";
		out<<"127.0.0.1 RM680 localhost\n\n";
		out<<"#SmartHosts START\n\n";
		for(int i = 0;i<list.count();i++)
		{
			int found = -1;
			for(int j = 0;j<titles.count();j++)
			{
				if(titles.at(j)==list.at(i))
				{
					found = j;
					break;
				}
			}
			if(found==-1)
			{
				continue;
			}
			//out<<"#"<<list.at(i)<<" START\n";
			QStringList* partList = items->at(found);
			for(int j = 0;j<partList->count();j++)
			{
				out<<partList->at(j);
				out<<"\n";
			}
		}
		out<<"#SmartHosts END";
		file.close();
		emit signal_writeHosts_done();
	}else
	{
		emit signal_error(FILESYS,"Can not open \n /etc/hosts \nto write!");
	}
}

void UtilEngine::slot_replyFinished(QNetworkReply* reply)
{
	if(reply->error()==QNetworkReply::NoError)
	{
		QFile file(SAVED_HOSTS_FILE);
		if(file.open(QIODevice::WriteOnly | QIODevice::Truncate))
		{
			QTextStream out(&file);
			out<<reply->readAll();
			out.flush();
			file.close();
			lastUpdate = QDateTime::currentDateTime();
			settings->setValue("lastUpdate",lastUpdate);
			settings->sync();
			slot_parseHostsFile(SAVED_HOSTS_FILE);
			emit signal_updateHosts_done();
		}else
		{
			emit signal_error(FILESYS,"Can not open temp file!");
		}
	}else
	{
		emit signal_error(NETWORK,reply->errorString());
	}
}

void UtilEngine::slot_parseHostsFile(QString filePath)
{
	//get titles and items
	QFile file(filePath);
	if(file.open(QIODevice::ReadOnly))
	{
		QTextStream in(&file);
		QString svn_hosts_updateTime = in.readLine();
		if((!svn_hosts_updateTime.isEmpty())&&(!svn_hosts_updateTime.isNull()))
		{
			//eg:#UPDATE:12-09-09 09:09
			svn_hosts_updateTime.remove(0,8);
			hostsDate = QDateTime::fromString(svn_hosts_updateTime,"yy-MM-dd HH:mm");
			settings->setValue("hostsDate",hostsDate);
			settings->sync();
		}
		//qDebug()<<"svn HOSTS date:"<<hostsDate;
		//Then titles and item segments
		bool started = false;
		QString temp;
		titles.clear();
		items->clear();
		do
		{
			temp = in.readLine();
			if(temp.startsWith("#") && temp.endsWith("SmartHosts START",Qt::CaseInsensitive))
			{
				started = true;
				continue;
			}else if(temp.startsWith("#") && temp.endsWith("START",Qt::CaseInsensitive))
			{
				//new title and new entry in items
				QString tempx = temp;
				tempx.remove(0,1);
				tempx.remove(tempx.lastIndexOf("START",Qt::CaseInsensitive)-4,tempx.length()-tempx.lastIndexOf("START",Qt::CaseInsensitive));
				tempx = tempx.simplified();
				titles.append(tempx);
				items->append(new QStringList());
			}else if(temp.startsWith("#") && temp.endsWith("SmartHosts End",Qt::CaseInsensitive))
			{
				continue;
			}
			if(started&&(items->count()==titles.count())&&(items->count()!=0))
			{
				((QStringList*)(items->last()))->append(temp);
			}
		}while(!temp.isNull());
		emit signal_praseDone(titles.count());
		//qDebug()<<"Prase Done!";
		if(ctx!=NULL)
		{
			ctx->setContextProperty("itemModel", QVariant::fromValue(getCheckBoxItems()));
		}
	}else
	{
		emit signal_error(FILESYS,"Can not open temp file!");
		//qDebug()<<"#001 Can not open temp file!";
	}
}

void UtilEngine::slot_resetUIItems()
{
	if(ctx!=NULL)
	{
		ctx->setContextProperty("itemModel", QVariant::fromValue(getCheckBoxItems()));
	}
}

void UtilEngine::slot_tickChanged(QVariant _label,QVariant isTicked)
{
	slot_tickChanged(_label.toString(),isTicked.toBool());
}

void UtilEngine::slot_tickChanged(QString _label,bool isTicked)
{
	//qDebug()<<"label:"<<_label<<" is "<<isTicked;
	settings->setValue(QString("hosts/")+_label,isTicked);
	settings->sync();
}

void UtilEngine::slot_downloadProgress(qint64 bytesReceived,qint64 bytesTotal)
{
	emit signal_downloadProgress(bytesReceived,bytesTotal);
}

QString UtilEngine::getHostsFileType()
{
	return settings->value("hosts_url").toString();
}

void UtilEngine::setHostsFileType(QVariant data)
{
	settings->setValue("hosts_url",data);
	settings->sync();
}

