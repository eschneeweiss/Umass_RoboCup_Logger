#-------------------------------------------------
#
# Project created by QtCreator 2016-01-27T10:46:26
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Umass_RoboCup_Logger
TEMPLATE = app

MOC_DIR     = src/moc
OBJECTS_DIR = src/obj

LIBS     += -L/usr/lib/i386-linux-gnu -lprotobuf -lGLU
LIBS     += -L $$PWD/libs -lqwt

INCLUDEPATH += src
INCLUDEPATH += include/qwt

SOURCES += \
    src/main.cpp\
    src/mainwindow.cpp \
    src/log_viewer.cpp \
    src/graph_viewer.cpp \
    src/timestep_viewer.cpp \
    src/proto/cpp/messages_robocup_ssl_wrapper_legacy.pb.cc \
    src/proto/cpp/messages_robocup_ssl_wrapper.pb.cc \
    src/proto/cpp/messages_robocup_ssl_refbox_log.pb.cc \
    src/proto/cpp/messages_robocup_ssl_geometry_legacy.pb.cc \
    src/proto/cpp/messages_robocup_ssl_geometry.pb.cc \
    src/proto/cpp/messages_robocup_ssl_detection.pb.cc \
    src/protobuf_reader.cpp \
    src/net/robocup_ssl_server.cpp \
    src/net/robocup_ssl_client.cpp \
    src/net/netraw.cpp \
    src/protobuf_writer.cpp \
    src/threads/playbackthread.cpp \
    src/threads/clientthread.cpp \
    src/soccerview.cpp \
    src/gltext.cpp \
    src/util/field_default_constants.cpp \
    src/util/affinity_manager.cpp \
    src/util/field.cpp \
    src/vartypes/VarTypes.cpp \
    src/util/helpers.cpp \
    src/vartypes/VarTypesInstance.cpp \
    src/vartypes/VarTypesFactory.cpp \
    src/vartypes/VarXML.cpp \
    src/vartypes/VarNotifier.cpp \
    src/vartypes/VarBase64.cpp \
    src/vartypes/primitives/VarVal.cpp \
    src/vartypes/primitives/VarType.cpp \
    src/vartypes/primitives/VarTrigger.cpp \
    src/vartypes/primitives/VarStringVal.cpp \
    src/vartypes/primitives/VarStringEnum.cpp \
    src/vartypes/primitives/VarString.cpp \
    src/vartypes/primitives/VarSelection.cpp \
    src/vartypes/primitives/VarQWidget.cpp \
    src/vartypes/primitives/VarProtoBufferVal.cpp \
    src/vartypes/primitives/VarProtoBuffer.cpp \
    src/vartypes/primitives/VarList.cpp \
    src/vartypes/primitives/VarIntVal.cpp \
    src/vartypes/primitives/VarInt.cpp \
    src/vartypes/primitives/VarExternal.cpp \
    src/vartypes/primitives/VarDoubleVal.cpp \
    src/vartypes/primitives/VarDouble.cpp \
    src/vartypes/primitives/VarBoolVal.cpp \
    src/vartypes/primitives/VarBool.cpp \
    src/vartypes/primitives/VarBlob.cpp \
    src/vartypes/xml/xmlParser.cpp \
    src/textdata_viewer.cpp \
    src/robotplot.cpp \
    src/robotcurve.cpp \
    src/fspinbox.cpp \
    src/fslider.cpp \
    src/trashcan.cpp

HEADERS  += \
    src/mainwindow.h \
    src/log_viewer.h \
    src/graph_viewer.h \
    src/timestep_viewer.h \
    src/proto/cpp/messages_robocup_ssl_wrapper_legacy.pb.h \
    src/proto/cpp/messages_robocup_ssl_wrapper.pb.h \
    src/proto/cpp/messages_robocup_ssl_refbox_log.pb.h \
    src/proto/cpp/messages_robocup_ssl_geometry_legacy.pb.h \
    src/proto/cpp/messages_robocup_ssl_geometry.pb.h \
    src/proto/cpp/messages_robocup_ssl_detection.pb.h \
    src/protobuf_reader.h \
    src/net/robocup_ssl_server.h \
    src/net/robocup_ssl_client.h \
    src/net/netraw.h \
    src/protobuf_writer.h \
    src/threads/playbackthread.h \
    src/threads/clientthread.h \
    src/util/util.h \
    src/soccerview.h \
    src/gltext.h \
    src/util/timer.h \
    src/util/geometry.h \
    src/util/field_default_constants.h \
    src/util/field.h \
    src/vartypes/VarTypes.h \
    src/util/helpers.h \
    src/util/gvector.h \
    src/util/geomalgo.h \
    src/vartypes/VarTypesInstance.h \
    src/vartypes/VarTypesFactory.h \
    src/vartypes/VarXML.h \
    src/vartypes/VarNotifier.h \
    src/vartypes/VarBase64.h \
    src/vartypes/primitives/VarVal.h \
    src/vartypes/primitives/VarType.h \
    src/vartypes/primitives/VarTrigger.h \
    src/vartypes/primitives/VarStringVal.h \
    src/vartypes/primitives/VarStringEnum.h \
    src/vartypes/primitives/VarString.h \
    src/vartypes/primitives/VarSelection.h \
    src/vartypes/primitives/VarQWidget.h \
    src/vartypes/primitives/VarProtoBufferVal.h \
    src/vartypes/primitives/VarProtoBuffer.h \
    src/vartypes/primitives/VarList.h \
    src/vartypes/primitives/VarIntVal.h \
    src/vartypes/primitives/VarInt.h \
    src/vartypes/primitives/VarExternal.h \
    src/vartypes/primitives/VarDoubleVal.h \
    src/vartypes/primitives/VarDouble.h \
    src/vartypes/primitives/VarBoolVal.h \
    src/vartypes/primitives/VarBool.h \
    src/vartypes/primitives/VarBlob.h \
    src/vartypes/xml/xmlParser.h \
    src/textdata_viewer.h \
    src/robotplot.h \
    src/robotcurve.h \
    src/fspinbox.h \
    src/fslider.h \
    src/trashcan.h
