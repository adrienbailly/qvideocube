#ifndef BEATWIDGET_H
#define BEATWIDGET_H

#include <QtGui>

#define BEATWIDGET_BEAT_PERIOD  3000
#define BEATWIDGET_COLOR_PERIOD 23000

//
// Show a beating halo, with color chanching at a lower rate
//
class BeatWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BeatWidget(QWidget *parent = 0);
    
signals:
    
public slots:
    void paintEvent(QPaintEvent *);

private slots:
    void setBeat(qreal step);
    void setColor(qreal step);

private:
    double mBeat;
    double mColor;
    
};

#endif // BEATWIDGET_H
