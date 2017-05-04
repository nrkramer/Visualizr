#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QMimeData>
#include <QDragLeaveEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    player = new QMediaPlayer();

    connect(player, SIGNAL(stateChanged(QMediaPlayer::State)), this, SLOT(stateChanged(QMediaPlayer::State)));
    connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(scrubberUpdate(qint64)));
    connect(player, SIGNAL(durationChanged(qint64)), this, SLOT(durationChanged(qint64)));

    connect(ui->playButton, SIGNAL(toggled(bool)), this, SLOT(playPauseClicked(bool)));
    connect(ui->rewindButton, SIGNAL(clicked(bool)), this, SLOT(rewindFile()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    if(event->mimeData()->hasUrls()) {
        QMimeType type = db.mimeTypeForUrl(event->mimeData()->urls().at(0));
        if (QMediaPlayer::hasSupport(type.name())) {
            event->acceptProposedAction();
        } else {
            event->dropAction();
        }
    } else {
        event->dropAction();
    }
}

void MainWindow::dragMoveEvent(QDragMoveEvent *event)
{
    event->acceptProposedAction();
}

void MainWindow::dragLeaveEvent(QDragLeaveEvent *event)
{
    event->accept();
}

void MainWindow::dropEvent(QDropEvent *event)
{
    qInfo() << event->mimeData()->urls().at(0);
    player->setMedia(QMediaContent(event->mimeData()->urls().at(0)));
    player->play();
    event->acceptProposedAction();
}

void MainWindow::updateScrubber()
{

}

// this one updates as a result of the media being played
void MainWindow::scrubberUpdate(qint64 tick)
{
    /*long long seconds = (long long) (tick / 1000) % 60 ;
    long long minutes = (long long) ((tick / (1000*60)) % 60);
    QString text = QString("%1").arg(minutes, 2, 10, QChar('0')) + ":" + QString("%1").arg(seconds, 2, 10, QChar('0'));
    ui->label->setText(text);*/

    ui->scrubber->setValue(tick);
}

void MainWindow::durationChanged(qint64 duration)
{
    ui->scrubber->setMaximum(duration);
    totalDuration = duration;
}

void MainWindow::stateChanged(QMediaPlayer::State state)
{
    if (state == QMediaPlayer::PlayingState) {
        ui->scrubber->setEnabled(true);
        ui->playButton->setEnabled(true);
        ui->rewindButton->setEnabled(true);

        ui->playButton->setIcon(QIcon(":/images/pause.ico"));
    } else if (state == QMediaPlayer::PausedState) {
        ui->playButton->setIcon(QIcon(":/images/play.ico"));
    } else if (state == QMediaPlayer::StoppedState) {
        ui->playButton->setIcon(QIcon(":/images/play.ico"));
    }
}

void MainWindow::playPauseClicked(bool toggle)
{
    if (toggle)
        player->pause();
    else
        player->play();
}

void MainWindow::rewindFile()
{
    player->setPosition(0);
}
