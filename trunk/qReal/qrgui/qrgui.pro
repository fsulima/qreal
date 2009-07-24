QT		+=	svg xml

INCLUDEPATH	+=	../qrxml/editors \
			../qrxml \
			mainwindow

RESOURCES	=	qrgui.qrc
SOURCES		=	main.cpp

# Graphical elements
include (umllib/umllib.pri)

# Dialogs
include (dialogs/dialogs.pri)

# Main window
include (mainwindow/mainwindow.pri)

# Client
include (client/client.pri)

# Model
include (model/model.pri)

# View
include (view/view.pri)

# Stuff used in all places
include (kernel/kernel.pri)