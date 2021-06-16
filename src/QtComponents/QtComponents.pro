NAME         = QtComponents
TARGET       = $${NAME}

QT           = core
QT          += gui
QT          += network
QT          += sql
QT          += script
QT          += positioning
QT          += widgets
QT          += opengl
QT          += printsupport
QT          += multimedia
QT          += multimediawidgets
QT          += opengl
QT          += QtCUDA
QT          += QtOpenCV
QT          += Essentials
QT          += QtCalendar
QT          += QtGMP
QT          += QtGSL
QT          += QtAlgebra
QT          += QtDiscrete
QT          += QtFFT
QT          += Mathematics
QT          += QtFuzzy
QT          += QtFLP
QT          += QtFoundation
QT          += QtGeometry
QT          += QtGadgets
QT          += QtWorld
QT          += QScintilla2

load(qt_build_config)
load(qt_module)

INCLUDEPATH += $${PWD}/../../include/$${NAME}

HEADERS     += $${PWD}/../../include/$${NAME}/qtcomponents.h

include ($${PWD}/Abstract/Abstract.pri)
include ($${PWD}/Configurators/Configurators.pri)
include ($${PWD}/Plan/Plan.pri)
include ($${PWD}/Traditions/Traditions.pri)
include ($${PWD}/VcfBase/VcfBase.pri)
include ($${PWD}/Scene/Scene.pri)

OTHER_FILES += $${PWD}/../../include/$${NAME}/headers.pri

include ($${PWD}/../../doc/Qt/Qt.pri)

TRNAME       = $${NAME}
include ($${PWD}/../../Translations.pri)
