QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qdbs_w
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++14

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    login_dialog.cpp \
    staff_mngr.cpp \
    database_mngr.cpp \
    medicines.cpp \
    overview.cpp \
    analysis.cpp \
    purchase_record.cpp \
    medicine_selecter.cpp \
    quality_record.cpp \
    application_record.cpp \
    in_recorder.cpp \
    out_recorder.cpp \
    pur_selecter.cpp \
    apr_selecter.cpp \
    inv_selecter.cpp \
    storage_select.cpp

HEADERS += \
        mainwindow.h \
    login_dialog.h \
    staff_mngr.h \
    database_mngr.h \
    medicines.h \
    overview.h \
    analysis.h \
    purchase_record.h \
    medicine_selecter.h \
    quality_record.h \
    application_record.h \
    in_recorder.h \
    out_recorder.h \
    pur_selecter.h \
    apr_selecter.h \
    inv_selecter.h \
    storage_select.h

FORMS += \
        mainwindow.ui \
    login_dialog.ui \
    overview.ui \
    analysis.ui \
    purchase_record.ui \
    medicine_selecter.ui \
    quality_record.ui \
    application_record.ui \
    in_recorder.ui \
    out_recorder.ui \
    pur_selecter.ui \
    apr_selecter.ui \
    inv_selecter.ui \
    storage_select.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
