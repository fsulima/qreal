QT		+=	svg xml
CONFIG += rpath_libdirs

INCLUDEPATH	+=	../qrmc\
			../qrmc/plugins\
			mainwindow \
			mainwindow/shapeEdit

RESOURCES	=	qrgui.qrc
SOURCES		=	main.cpp

# workaround для http://bugreports.qt.nokia.com/browse/QTBUG-8110
# как только поправят, можно будет юзать QMAKE_LFLAGS_RPATH
QMAKE_LFLAGS="-Wl,-O1,-rpath,$(PWD)"

OBJECTS_DIR = .obj
UI_DIR = .ui
MOC_DIR = .moc
RCC_DIR = .moc

if (equals(QMAKE_CXX, "g++")) {
	QMAKE_LFLAGS += -Wl,-E
}

# Путь до библиотеки с АПИ. Где-нибудь она найдётся...Path to the API library
LIBS += -Ldebug -lqrrepo -Lrelease -lqrrepo -L. -lqrrepo -lqrmc

# Graphical elements
include (umllib/umllib.pri)

# Dialogs
include (dialogs/dialogs.pri)

# Main window
include (mainwindow/mainwindow.pri)

# Model
include (model/model.pri)

# View
include (view/view.pri)

# Stuff used in all places
include (kernel/kernel.pri)

# "Встроенные" генераторы
include (generators/generators.pri)

# "Встроенные" средства реверс-инжиниринга
include (parsers/parsers.pri)

HEADERS += ../qrmc/plugins/pluginInterface.h

# .pri заведён, чтобы структура папок более круто показывалась в креаторе.
# Содержит код, общий для генератора редакторов и основной части.
include (../utils/utils.pri)

# Код, скачанный из интернета.
include (thirdparty/thirdparty.pri)

# Управление плагинами. Plugin managment
include (editorManager/editorManager.pri)
