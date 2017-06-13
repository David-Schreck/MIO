#include "videowidget.h"

#include <QLabel>
#include <QVideoWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>

VideoWidget::VideoWidget():QWidget()
{
    QLabel *Titre = new QLabel("Video Widget", this);

    QMediaPlayer *player = new QMediaPlayer(this);

    QMediaPlaylist *playlist = new QMediaPlaylist(player);
    playlist->addMedia(QUrl("http://troisquartsdepouce.com/test_ISIS.MOV"));

    QVideoWidget *videoWidget = new QVideoWidget;
    player->setVideoOutput(videoWidget);

    videoWidget->show();
    playlist->setCurrentIndex(1);
    player->play();


}



VideoWidget::~VideoWidget()
{

}
