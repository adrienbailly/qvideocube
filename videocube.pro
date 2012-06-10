SOURCES += main.cpp \
    beatwidget.cpp \
    videocube.cpp \
    videocubemodel.cpp
SOURCES += customproxy.cpp
HEADERS += customproxy.h \
    beatwidget.h \
    videocube.h \
    videocubemodel.h

QT += phonon opengl

#build_all:!build_pass {
#    CONFIG -= build_all
#    CONFIG += release
#}

# install
#target.path = $$[QT_INSTALL_DEMOS]/videocube
#sources.files = $$SOURCES $$HEADERS $$RESOURCES *.png *.pro *.html *.doc images
#sources.path = $$[QT_INSTALL_DEMOS]/videocube
#INSTALLS += target sources
