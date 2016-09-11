#-------------------------------------------------
#
# Project created by QtCreator 2016-01-27T10:46:26
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Umass_Robocup_log
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    log_viewer.cpp \
    graph_viewer.cpp \
    timestep_viewer.cpp \
    proto/cpp/messages_robocup_ssl_wrapper_legacy.pb.cc \
    proto/cpp/messages_robocup_ssl_wrapper.pb.cc \
    proto/cpp/messages_robocup_ssl_refbox_log.pb.cc \
    proto/cpp/messages_robocup_ssl_geometry_legacy.pb.cc \
    proto/cpp/messages_robocup_ssl_geometry.pb.cc \
    proto/cpp/messages_robocup_ssl_detection.pb.cc \
    protobuf_reader.cpp \
    net/robocup_ssl_server.cpp \
    net/robocup_ssl_client.cpp \
    net/netraw.cpp \
    protobuf_writer.cpp \
    threads/playbackthread.cpp \
    threads/clientthread.cpp \
    soccerview.cpp \
    gltext.cpp \
    util/field_default_constants.cpp \
    util/affinity_manager.cpp \
    util/field.cpp \
    vartypes/VarTypes.cpp \
    util/helpers.cpp \
    vartypes/VarTypesInstance.cpp \
    vartypes/VarTypesFactory.cpp \
    vartypes/VarXML.cpp \
    vartypes/VarNotifier.cpp \
    vartypes/VarBase64.cpp \
    vartypes/primitives/VarVal.cpp \
    vartypes/primitives/VarType.cpp \
    vartypes/primitives/VarTrigger.cpp \
    vartypes/primitives/VarStringVal.cpp \
    vartypes/primitives/VarStringEnum.cpp \
    vartypes/primitives/VarString.cpp \
    vartypes/primitives/VarSelection.cpp \
    vartypes/primitives/VarQWidget.cpp \
    vartypes/primitives/VarProtoBufferVal.cpp \
    vartypes/primitives/VarProtoBuffer.cpp \
    vartypes/primitives/VarList.cpp \
    vartypes/primitives/VarIntVal.cpp \
    vartypes/primitives/VarInt.cpp \
    vartypes/primitives/VarExternal.cpp \
    vartypes/primitives/VarDoubleVal.cpp \
    vartypes/primitives/VarDouble.cpp \
    vartypes/primitives/VarBoolVal.cpp \
    vartypes/primitives/VarBool.cpp \
    vartypes/primitives/VarBlob.cpp \
    vartypes/xml/xmlParser.cpp \
    textdata_viewer.cpp \
    robotplot.cpp \
    robotcurve.cpp \
    fspinbox.cpp \
    fslider.cpp

HEADERS  += mainwindow.h \
    log_viewer.h \
    graph_viewer.h \
    timestep_viewer.h \
    proto/cpp/messages_robocup_ssl_wrapper_legacy.pb.h \
    proto/cpp/messages_robocup_ssl_wrapper.pb.h \
    proto/cpp/messages_robocup_ssl_refbox_log.pb.h \
    proto/cpp/messages_robocup_ssl_geometry_legacy.pb.h \
    proto/cpp/messages_robocup_ssl_geometry.pb.h \
    proto/cpp/messages_robocup_ssl_detection.pb.h \
    protobuf_reader.h \
    net/robocup_ssl_server.h \
    net/robocup_ssl_client.h \
    net/netraw.h \
    protobuf_writer.h \
    threads/playbackthread.h \
    threads/clientthread.h \
    util/util.h \
    soccerview.h \
    gltext.h \
    util/timer.h \
    util/geometry.h \
    util/field_default_constants.h \
    util/field.h \
    vartypes/VarTypes.h \
    util/helpers.h \
    util/gvector.h \
    util/geomalgo.h \
    vartypes/VarTypesInstance.h \
    vartypes/VarTypesFactory.h \
    vartypes/VarXML.h \
    vartypes/VarNotifier.h \
    vartypes/VarBase64.h \
    vartypes/primitives/VarVal.h \
    vartypes/primitives/VarType.h \
    vartypes/primitives/VarTrigger.h \
    vartypes/primitives/VarStringVal.h \
    vartypes/primitives/VarStringEnum.h \
    vartypes/primitives/VarString.h \
    vartypes/primitives/VarSelection.h \
    vartypes/primitives/VarQWidget.h \
    vartypes/primitives/VarProtoBufferVal.h \
    vartypes/primitives/VarProtoBuffer.h \
    vartypes/primitives/VarList.h \
    vartypes/primitives/VarIntVal.h \
    vartypes/primitives/VarInt.h \
    vartypes/primitives/VarExternal.h \
    vartypes/primitives/VarDoubleVal.h \
    vartypes/primitives/VarDouble.h \
    vartypes/primitives/VarBoolVal.h \
    vartypes/primitives/VarBool.h \
    vartypes/primitives/VarBlob.h \
    vartypes/xml/xmlParser.h \
    textdata_viewer.h \
    robotplot.h \
    robotcurve.h \
    fspinbox.h \
    fslider.h

#FORMS    += mainwindow.ui

LIBS     += -L/usr/lib/i386-linux-gnu -lprotobuf -lGLU

#INCLUDEPATH += /home/eddy/qwt-6.1.2/src
#LIBS += -L/home/eddy/qwt-6.1.2/lib -lqwt

INCLUDEPATH += /usr/local/qwt-6.1.2/include
LIBS += -L/usr/local/qwt-6.1.2/lib -lqwt
