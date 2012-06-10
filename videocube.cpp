#include "videocube.h"
#include "videocubemodel.h"

/**
 *
 */
VideoCube::VideoCube(QWidget *parent) :
    QWidget(parent)
{
    QGridLayout *layout = new QGridLayout( this );

    //
    // Buttons
    //
    QPushButton *btnLeft = new QPushButton( "Left", this );
    QPushButton *btnRight = new QPushButton( "Right", this );
    QPushButton *btnUp = new QPushButton( "Up", this );
    QPushButton *btnDown = new QPushButton( "Down", this );
    QPushButton *btnHome = new QPushButton( "Home", this );

    connect( btnLeft, SIGNAL(clicked()), this, SLOT(goLeft()) );
    connect( btnRight, SIGNAL(clicked()), this, SLOT(goRight()) );
    connect( btnUp, SIGNAL(clicked()), this, SLOT(goUp()) );
    connect( btnDown, SIGNAL(clicked()), this, SLOT(goDown()) );
    connect( btnHome, SIGNAL(clicked()), this, SLOT(goHome()) );

    layout->addWidget( btnLeft, 3, 1 );
    layout->addWidget( btnRight, 3, 3 );
    layout->addWidget( btnUp, 2, 2 );
    layout->addWidget( btnDown, 4, 2 );
    layout->addWidget( btnHome, 3, 2 );


    //
    // Scene
    //
    QGraphicsScene *scene = new QGraphicsScene();
    //layout->addWidget( );

    int dimension = 3;
    QFileInfoList files;
    QDir dir;
    dir = QDir(".");
    files = dir.entryInfoList(QStringList() << "*.wmv" << "*.mov" << "*.avi" << "*.mp4" );

    // Degug
    qDebug() << "List of files:";
    for(int k=0; k<files.size(); ++k) {
        qDebug() << "\t" << k << ":" << files.at(k).fileName();
    }

    if (files.isEmpty())
        dimension = 0;

    int index = 0;
    for (int y = 0; y < dimension && index < files.size(); ++y) {
        for (int x = 0; x < dimension && index < files.size(); ++x) {
            Phonon::MediaObject *media = new Phonon::MediaObject();
            media->setCurrentSource(files.at(index).absoluteFilePath());

            for(int k=0; k<100; k++) {
                media->enqueue( Phonon::MediaSource(files.at(index).absoluteFilePath()) );
            }

            Phonon::VideoWidget *video = new Phonon::VideoWidget();
            Phonon::createPath(media, video);

            Phonon::AudioOutput *audio = new Phonon::AudioOutput();
            Phonon::createPath(media, audio);
            audio->setMuted( true );

            // Video rectangle
            ///CustomProxy *proxy = new CustomProxy(0, Qt::Window);
            CustomProxy *proxy = new CustomProxy();
            proxy->setTitle( files.at(index).baseName() );
            proxy->setWidget(video);
            QObject::connect(proxy, SIGNAL(focusChanged(bool)), audio, SLOT(setMuted(bool)));

            QRectF rect = proxy->boundingRect();
            //qDebug() << rect;
            proxy->setPos(x * rect.width() * 1.05, y * rect.height() * 1.05);
            //proxy->show();
            scene->addItem(proxy);

            // Add signal to the CustomVideoWidget
            connect( btnLeft, SIGNAL(clicked()), proxy, SLOT(goLeft()) );
            connect( btnRight, SIGNAL(clicked()), proxy, SLOT(goRight()) );
            connect( btnUp, SIGNAL(clicked()), proxy, SLOT(goUp()) );
            connect( btnDown, SIGNAL(clicked()), proxy, SLOT(goDown()) );
            connect( btnHome, SIGNAL(clicked()), proxy, SLOT(goHome()) );

            // Play video
            media->play();

            ////index = (index + 1) % files.size();
            index++;
        }
    }

    scene->setSceneRect( scene->itemsBoundingRect() );

    QGraphicsView *view = new QGraphicsView( scene );
    view->setViewport( new QGLWidget() );
    view->scale(1. / qreal(dimension), 1. / qreal(dimension));
    view->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    view->setBackgroundBrush( Qt::darkGray );
    view->setCacheMode(QGraphicsView::CacheBackground);
    view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    view->show();

    VideoCubeModel *vcm = new VideoCubeModel();
    vcm->getVideoAt(0, 0);
    vcm->getVideoAt(1, 1);
}
