#ifndef VIDEOCUBEMODEL_H
#define VIDEOCUBEMODEL_H

#include <QtGui>
#include <Phonon>

#define VIDEOCUBEMODEL_DEFAULT_GRIDWIDTH 4

/**
 *
 */
class VideoCubeModel
{
public:
    VideoCubeModel();

    void loadVideos( const QString& dirName = "." );

    Phonon::MediaObject* getVideoAt( int row, int col );

    void setGridWidth( int width ) {
        mGridWidth = width;
    }

private:
    int mGridWidth;
    QVector< Phonon::MediaObject* > mVideos;

};

#endif // VIDEOCUBEMODEL_H
