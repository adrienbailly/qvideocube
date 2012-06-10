#ifndef CUSTOMPROXY_H
#define CUSTOMPROXY_H

#include <QtGui>
#include <QtCore/qtimeline.h>
#include <QtGui/qgraphicsproxywidget.h>

class CustomProxy : public QGraphicsProxyWidget
{
    Q_OBJECT
public:
    CustomProxy(QGraphicsItem *parent = 0, Qt::WindowFlags wFlags = 0);

    QRectF boundingRect() const;
    void paintWindowFrame(QPainter *painter, const QStyleOptionGraphicsItem *option,
                          QWidget *widget);                          

    void setTitle( const QString& title ) {
        mTitle = title;
    }

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
                                          
private slots:
    void updateStep(qreal step);
    void resetZValue();

    void goLeft() {
        mXAxis = 0;
        mYAxis = 45;
        mScale = 1.0;
        mPos = QPoint( -500, 0 );
        startTimeLine();
    }

    void goRight() {
        mXAxis = 0;
        mYAxis = -45;
        mScale = 1.0;
        mPos = QPoint( 500, 0 );
        startTimeLine();
    }

    void goUp() {
        mXAxis = 45;
        mYAxis = 0;
        mScale = 1.0;
        mPos = QPoint( 0, -500 );
        startTimeLine();
    }

    void goDown() {
        mXAxis = -45;
        mYAxis = 0;
        mScale = 1.0;
        mPos = QPoint( 0, 500 );
        startTimeLine();
    }

    void goHome() {
        mXAxis = 0;
        mYAxis = 0;
        mScale = 1.0;
        mPos = QPoint( 0, 0 );
        startTimeLine();
    }

    void startTimeLine() {
        timeLine->setDirection( QTimeLine::Forward );
        timeLine->start();
    }

signals:
    void focusChanged(bool focus);

private:
    QTimeLine *timeLine;
    QString mTitle;

    double mXAxis;
    double mYAxis;
    double mScale;
    QPoint mPos;
};

#endif
