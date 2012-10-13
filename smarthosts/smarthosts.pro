TEMPLATE = app

QT += declarative gui network

TARGET = "smarthosts"
DEPENDPATH += .
INCLUDEPATH += .

HEADERS += dataobject.h \
	utilengine.h
SOURCES += dataobject.cpp \
	utilengine.cpp \
	main.cpp


target.path = /opt/smarthosts/bin/

desktopfiles.files =  smarthosts.desktop
desktopfiles.path = /usr/share/applications

icons.files = icons/smarthosts_128x128.png
icons.path = /opt/smarthosts/icons/

qml.files = qml/*qml
qml.path = /opt/smarthosts/qml

i18n.files = i18n/smarthosts_zh.qm
i18n.path = /opt/smarthosts/qml/i18n

INSTALLS+= target \
	desktopfiles \
	icons \
	qml \
	i18n

