/*
 * smarthosts
 * 2012 by lovewilliam <lovewilliam@gmail.com>
 */
#include <QtCore/QtGlobal>
#include <QApplication>
#include <QtCore/QTranslator>
#include <QMainWindow>
#include <QDeclarativeView>
#include <QDesktopWidget>
#include <QObject>
#include <QVariant>
#include <QDir>
#include <QtDeclarative>
#include <QDeclarativeEngine>
//#include <QSparqlQueryModel>

#include "utilengine.h"

#define _APP_VERSION_ "0.1.0"


int main(int argc,char** argv)
{
	QApplication::setOrganizationName("bss");
	QApplication::setOrganizationDomain("");
	QApplication::setApplicationName("smarthosts");

	QApplication app(argc,argv);
	
	app.setApplicationName("smarthosts");
	app.setApplicationVersion(_APP_VERSION_);

	QString locale = QLocale::system().name();
	QTranslator translator;
	translator.load( QString("smarthosts_") + locale,"/opt/smarthosts/qml/i18n");
	app.installTranslator(&translator);

	app.setProperty("NoMStyle",QVariant(true));
	
	QDir::setCurrent(app.applicationDirPath());

	UtilEngine util_engine;
	
	QDeclarativeView view;

	util_engine.setQMLContext(((QDeclarativeContext*)view.rootContext()));

	((QDeclarativeContext*)view.rootContext())->setContextProperty("util_engine", &util_engine);
//	((QDeclarativeContext*)view.rootContext())->setContextProperty("itemModel", QVariant::fromValue(util_engine.getCheckBoxItems()));
	util_engine.slot_resetUIItems();
	view.setSource(QUrl("/opt/smarthosts/qml/main.qml"));

	QObject *rootObject = dynamic_cast<QObject*>(view.rootObject());

	QObject::connect(&util_engine, SIGNAL(signal_error(QVariant,QVariant)),
			rootObject, SLOT(ui_error(QVariant,QVariant)));
	QObject::connect(&util_engine, SIGNAL(signal_writeHosts_done()),
			rootObject, SLOT(doneWriteToHosts()));
	QObject::connect(&util_engine, SIGNAL(signal_updateHosts_done()),
			rootObject, SLOT(hostsFileUpdated()));
	QObject::connect(&util_engine, SIGNAL(signal_downloadProgress(QVariant,QVariant)),
			rootObject, SLOT(ui_process_update(QVariant,QVariant)));


	view.showFullScreen();
	
	QObject::connect((QObject*)view.engine(), SIGNAL(quit())
				,&view, SLOT(close()));
	return app.exec();
}


