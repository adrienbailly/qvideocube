#include "videocubemodel.h"

VideoCubeModel::VideoCubeModel()
{
    mGridWidth = VIDEOCUBEMODEL_DEFAULT_GRIDWIDTH;
    loadVideos();
}

void VideoCubeModel::loadVideos( const QString &dirName )
{
    // List all files with right extension
    QFileInfoList files;
    QDir dir;
    dir = QDir( dirName );
    files = dir.entryInfoList( QStringList() << "*.wmv" << "*.mov" << "*.avi" << "*.mp4" );

    for(int k=0; k<files.size(); ++k) {
        qDebug() << "\t" << k << ":" << files.at(k).fileName();

        Phonon::MediaObject *media = new Phonon::MediaObject();
        media->setCurrentSource( files.at(k).absoluteFilePath() );

        // Enqueue many times the same video to emulate a loop. TODO: fixme
        for(int q=0; q<10; q++) {
            media->enqueue( Phonon::MediaSource(files.at(k).absoluteFilePath()) );
        }

        mVideos.push_front( media );
    }
}

Phonon::MediaObject* VideoCubeModel::getVideoAt( int row, int col )
{
    while(col < 0) {
        col += mGridWidth;
    }
    col = col % mGridWidth;

    int index = ((row*mGridWidth) + col) % mVideos.size();

    qDebug() << "Getting video at" << row << col << ":" << mVideos.at( index )->currentSource().fileName();
    return mVideos.at( index );
}
