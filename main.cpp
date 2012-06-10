#include "videocube.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName( "Video Cube DEMO" );

    VideoCube *videocube = new VideoCube();
    videocube->show();

    return app.exec();
}
