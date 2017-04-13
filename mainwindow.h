#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtMultimedia/QMediaPlayer>
#include <QMimeDatabase>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dragLeaveEvent(QDragLeaveEvent *event);
    void dropEvent(QDropEvent *event);

private:
    Ui::MainWindow *ui;
    QMediaPlayer *player;
    QMimeDatabase db;
    qint64 totalDuration;

private slots:
    void updateScrubber();
    void scrubberUpdate(qint64 tick);
    void durationChanged(qint64 duration);
    void stateChanged(QMediaPlayer::State status);
    void playPauseClicked(bool toggle);
    void rewindFile();
};

#endif // MAINWINDOW_H
