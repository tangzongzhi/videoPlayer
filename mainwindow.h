#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<highgui.h>
#include <QtCore>

using namespace cv;
using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_clicked(bool checked);
    void on_horizontalSlider_sliderMoved(int position);

private:
    Ui::MainWindow *ui;
    QString path;
    bool isPlay;
    bool isPause;
    bool stop;
    cv::Mat frame;
    long totalFrameNumber;
    long frameToStart;
    long frameToStop;
    long currentFrame;
    int delay;
     double rate;
     QElapsedTimer t;
     int framecounter;
     bool sliderMove=false;
     QTime playTime;
     QString playTimeText;
};

#endif // MAINWINDOW_H
