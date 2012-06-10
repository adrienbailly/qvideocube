#include "customproxy.h"

#include <QtGui>

CustomProxy::CustomProxy(QGraphicsItem *parent, Qt::WindowFlags wFlags)
    : QGraphicsProxyWidget(parent, wFlags),
      mXAxis(0),
      mYAxis(0),
      mScale(1),
      mPos(0,0)
{
    timeLine = new QTimeLine(250, this);
    connect(timeLine, SIGNAL(valueChanged(qreal)), this, SLOT(updateStep(qreal)));
    connect(timeLine, SIGNAL(finished()), this, SLOT(resetZValue()));

    //we never cache the video
    setCacheMode(NoCache);
}

QRectF CustomProxy::boundingRect() const
{
    return QGraphicsProxyWidget::boundingRect().adjusted(-40, -40, 40, 40);
}

void CustomProxy::paintWindowFrame(QPainter *painter, const QStyleOptionGraphicsItem *option,
                                   QWidget *widget)
{
    /*QRectF br = boundingRect();
    painter->setPen(Qt::NoPen);
    painter->setBrush(QColor(0, 0, 0, 128));
    painter->drawPolygon(QPolygonF(br.adjusted(10, 10, 10, 10)).intersected(br));

    painter->setPen( Qt::white );
    painter->drawRect( boundingRect() );

    QFont font("Courier New");
    font.setWeight( QFont::DemiBold );
    font.setPixelSize( 30 );
    painter->setFont( font );

    QRectF text( br );
    text.setTop( text.bottom()-40.0 );
    painter->drawText( text, mTitle, QTextOption(Qt::AlignCenter) );
    painter->drawRect( text );

    QGraphicsProxyWidget::paintWindowFrame(painter, option, widget);*/
}

void CustomProxy::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    QGraphicsProxyWidget::hoverEnterEvent(event);
    scene()->setActiveWindow(this);
    setZValue(1);
    if (timeLine->direction() != QTimeLine::Forward)
        timeLine->setDirection(QTimeLine::Forward);
    if (timeLine->state() == QTimeLine::NotRunning) 
        timeLine->start();

    emit focusChanged( false );
    //qDebug() << mTitle << "focusChanged( true )";
}
        
void CustomProxy::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    QGraphicsProxyWidget::hoverLeaveEvent(event);
    if (timeLine->direction() != QTimeLine::Backward)
        timeLine->setDirection(QTimeLine::Backward);
    if (timeLine->state() == QTimeLine::NotRunning) 
        timeLine->start();

    emit focusChanged( true );
    //qDebug() << mTitle << "focusChanged( false )";
}

void CustomProxy::updateStep(qreal step)
{

    QRectF r = boundingRect();

    /*setTransform(QTransform()
                 .translate(r.width() / 2, r.height() / 2)
                 .translate(-900 * qSin(step * M_PI_4), 0.0)
                 .rotate(step * 45, Qt::YAxis)
                 .scale(1.0/(1.0 + qCos((1.-step)*M_PI_4)*0.2), 1.0/(1.0 + qCos((1.-step)*M_PI_4)*0.2))
                 .translate(-r.width() / 2, -r.height() / 2));*/

    setTransform(QTransform()
                    .translate( r.width() / 2, r.height() / 2 )
                    .translate( step * mPos.x(), step * mPos.y() )
                    .rotate( step * mYAxis, Qt::YAxis )
                    .rotate( step * mXAxis, Qt::XAxis )
                    .translate(-r.width() / 2, -r.height() / 2)
                 );

}

void CustomProxy::resetZValue()
{
    if (timeLine->direction() == QTimeLine::Backward)
        setZValue(0);
}
