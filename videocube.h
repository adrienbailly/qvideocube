#ifndef VIDEOCUBE_H
#define VIDEOCUBE_H

#include <QtGui>
#include <QtCore>
#include <QtOpenGL>
#include <Phonon>

#include "customproxy.h"
#include "beatwidget.h"

/**
 *
 */
class VideoCube : public QWidget
{
    Q_OBJECT

public:

    VideoCube(QWidget *parent = 0);
    
signals:
    
public slots:
    void goLeft() {
        qDebug() << "GO LEFT";
    }

    void goRight() {
        qDebug() << "GO RIGHT";
    }

    void goUp() {
        qDebug() << "GO UP";
    }

    void goDown() {
        qDebug() << "GO DOWN";
    }

    void goHome() {
        qDebug() << "HOME";
    }
};

#endif // VIDEOCUBE_H
