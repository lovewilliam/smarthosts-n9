/*
 * UtilEngine
 * 2012 by lovewilliam <lovewilliam@gmail.com>
 */

#ifndef ENCODEENGINE_H
#define ENCODEENGINE_H

#include <QtCore/QObject>
#include <QByteArray>
#include <QVariant>
#include <QObject>
#include <QString>
#include <QStringList>
#include <QDateTime>
#include <QVector>
#include <QSettings>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QtDeclarative>

#include "dataobject.h"

#define HOSTS_URL "https://smarthosts.googlecode.com/svn/trunk/hosts"
#define HOSTS_ANDROID "https://smarthosts.googlecode.com/svn/trunk/mobile_devices/hosts"
#define HOSTS_IOS "https://smarthosts.googlecode.com/svn/trunk/mobile_devices/iOS/hosts"

//#define SAVED_HOSTS_FILE "/home/user/.config/bss/hosts"
#define SAVED_HOSTS_FILE "/root/hosts"

class UtilEngine : public QObject
{
	enum ErrorCode{NETWORK,FILESYS};

	Q_OBJECT
	public:
		UtilEngine();
		virtual ~UtilEngine();

		QList<QObject*> getCheckBoxItems();
		
		void setQMLContext(QDeclarativeContext*);

	public slots:
		QStringList getTitles();
		QVector<QStringList*>* getItems();
		QString getLastUpdateTime();
		QString getHostsDate();
		QString getHostsFileType();
		bool isRoot();
		void setHostsFileType(QVariant);
		void slot_updateSavedHostFile();
		void slot_writeCleanHosts();
		void slot_writeHosts();
		void slot_writeHosts(QStringList);
		void slot_resetUIItems();
		void slot_tickChanged(QVariant,QVariant);

	signals:
		void signal_writeHosts_done();
		void signal_updateHosts_done();
		void signal_praseDone(QVariant);
		void signal_error(QVariant,QVariant);//type,error
		void signal_downloadProgress(QVariant,QVariant);

	private slots:
		void slot_replyFinished(QNetworkReply*);
		void slot_parseHostsFile(QString);
		void slot_tickChanged(QString,bool);
		void slot_downloadProgress(qint64,qint64);

	private:
		QNetworkAccessManager* networkManager;
		QStringList titles;
		QVector<QStringList*>* items;

		QDateTime lastUpdate;
		QDateTime hostsDate;
		
		QSettings* settings;

		QList<QObject*> ui_itemList;

		QDeclarativeContext* ctx;
};

#endif // ENCODEENGINE_H

