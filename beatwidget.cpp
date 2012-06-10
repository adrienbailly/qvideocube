#include "beatwidget.h"

BeatWidget::BeatWidget(QWidget *parent) :
    QWidget(parent)
{

    QTimeLine *beatTimeLine = new QTimeLine( BEATWIDGET_BEAT_PERIOD, this );
    QTimeLine *colorTimeLine = new QTimeLine( BEATWIDGET_COLOR_PERIOD, this );

    beatTimeLine->setLoopCount( 0 );
    colorTimeLine->setLoopCount( 0 );

    connect(beatTimeLine, SIGNAL(valueChanged(qreal)), this, SLOT(setBeat(qreal)));
    connect(colorTimeLine, SIGNAL(valueChanged(qreal)), this, SLOT(setColor(qreal)));

    beatTimeLine->start();
    colorTimeLine->start();
}

void BeatWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    //painter.fillRect( rect(), Qt::transparent );

    QColor c;
    c.setHsvF( mColor, 1.0, 1.0, 1.0 );

    QRadialGradient gradient( rect().center(), rect().width()/2 );
    gradient.setColorAt(0, c);
    gradient.setColorAt(.5+.5*mBeat, Qt::transparent);
    painter.fillRect( rect(), gradient );
}

void BeatWidget::setBeat(qreal step)
{
    //mBeat = 0.5 * ( 1.0 + qCos( step * M_PI * 2.0 ) );
    mBeat = qMax(0.0, qCos( step * M_PI * 2.0 )) * qCos( step * M_PI * 2.0 );
    //qDebug() << "Beat =" << mBeat;
}

void BeatWidget::setColor(qreal step)
{
    mColor = step;
    //qDebug() << "Color =" << mColor;
    update();

}
