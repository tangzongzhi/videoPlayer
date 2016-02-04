/*
 * Video Player Demo
 *
 * Version 0.1
 *
 * 2016-02-03
 *
 * Copyright by Zongzhi Tang
 */


#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qfiledialog.h"
#include <QMessageBox>
#include<cv.h>
//#include<highgui.h>
//#include<imgproc\imgproc.hpp>


using namespace cv;
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    isPlay = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{

    QString selfilter = tr("Video Files (*.avi *.mpg *.mp4)");
    path = QFileDialog::getOpenFileName(
            this,
            tr("Open Video"),
            ".",
            tr("All files (*.*);;Video Files (*.avi *.mpg *.mp4)" ),
            &selfilter
    );
    ui->label->setText(path);
    isPlay=false;
    isPause=false;
    stop=false;
    currentFrame=0;
    t.start();
}


void MainWindow::on_pushButton_clicked(bool checked)
{
    QFileInfo video(path);
    if(video.exists())//path.length() != 0
    {
        //打开视频文件：其实就是建立一个VideoCapture结构
        const std::string videoPath = path.toUtf8().constData();
        VideoCapture capture(videoPath);
        if(!isPlay&&!isPause&&!stop) //尚未开始 开始计时
        {
        isPlay = !isPlay;

           //获取整个帧数
           totalFrameNumber = capture.get(CV_CAP_PROP_FRAME_COUNT);
           //设置开始帧()
           frameToStart = 0;//300
           capture.set( CV_CAP_PROP_POS_FRAMES,frameToStart);
           framecounter = 0;//记录帧数
           //设置结束帧
           frameToStop = totalFrameNumber-1;//int=400
           if(frameToStop < frameToStart)
           {
               QMessageBox::information(NULL, tr("Path2"), tr("结束帧小于开始帧, 程序错误, 即将退出! "));
               exit;
           }
           //获取帧率
           rate = capture.get(CV_CAP_PROP_FPS);
           int b,c;
           b = (int)rate;
           c = (int)(rate-b)*100;/*保留小数点后两位*/

           int videoSecsTotal=(int)totalFrameNumber/rate;
           QTime durations = QTime(0,0,0,0).addSecs(videoSecsTotal);
           //定义一个用来控制读取视频循环结束的变量
           stop = false;
           isPause = false;
           //两帧间的间隔时间:
           delay = 1000;//1000/rate
           //currentFrame是在循环体中控制读取到指定的帧后循环结束的变量
           currentFrame = frameToStart;

           //设置滑动条控件的最小值
           ui->horizontalSlider->setMinimum(0);
           //设置滑动条控件的最大值
           ui->horizontalSlider->setMaximum(totalFrameNumber);
           //设置滑动条控件的值
           ui->horizontalSlider->setValue(currentFrame);
           //信号和槽 当滑动条的值发生改变时，即产生一个valueChanged(int)信号 设置QLineEdit控件的显示文本
           connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(currentFrame));

           playTime = QTime(0,0,0,0);
           playTimeText = playTime.toString("hh:mm:ss");
           ui->lcdNumber->setPalette(Qt::green);
           ui->lcdNumber->display(playTimeText);
           QString totalTimeText = durations.toString("hh:mm:ss");
           ui->lcdNumber_2->setPalette(Qt::green);
           ui->lcdNumber_2->display(totalTimeText);
         }
        else if(isPlay&&!stop) //已经播放，触发暂停
        {
            isPause=!isPause;
        }
        capture.set(CV_CAP_PROP_POS_FRAMES,currentFrame);
        while(isPlay&&!stop&&!isPause&&currentFrame<totalFrameNumber)
        {
            //读取下一帧
            if(sliderMove==true)
            {
                capture.set( CV_CAP_PROP_POS_FRAMES,currentFrame);
                sliderMove=false;
            }
            if(!capture.read(frame))//!capture.read(frame)
               {
                   QMessageBox::information(NULL, tr("Path"), tr("读取视频失败"));
               }
            cvtColor(frame, frame, CV_BGR2RGB);
               QImage img = QImage((const unsigned char*)(frame.data),frame.cols,frame.rows,QImage::Format_RGB888);
               ui->label_2->setPixmap(QPixmap::fromImage(img));

               ui->horizontalSlider->setValue(currentFrame);
               framecounter++;//帧数记录+1
               int videoSecsCurrent=(int)framecounter/rate;
               QTime durationsCurrent = QTime(0,0,0,0).addSecs(videoSecsCurrent);
               QString durationsCurrentText = durationsCurrent.toString("hh:mm:ss");
               ui->lcdNumber->display(durationsCurrentText);
               waitKey(delay);
               while(t.elapsed()<(int)((1.0/rate)*1000)){}//(int)(1.0/rate)*1000
               qApp->processEvents();
               t.restart();
               int c = waitKey(delay);
               //按下ESC或者到达指定的结束帧后退出读取视频
               if( (char) c == 27 ||currentFrame > frameToStop)//(char) c == 27 |||| isPlay==false
               {
                   stop = true;
               }
               //按下按键后会停留在当前帧，等待下一次按键

               if( c >= 0)
               {
                   waitKey(0);
               }

               currentFrame++;

    }
        if(stop||currentFrame>=totalFrameNumber)
    {
           //关闭视频文件
           capture.release();
           frame.release();
           isPlay =false;
           isPause=false;
           currentFrame=0;
           framecounter=0;
           waitKey(0);
    }
    }
}
void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
    currentFrame=position;
    sliderMove=true;//
    framecounter=currentFrame;
}
