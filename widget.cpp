
#include "widget.h"           // 包含Widget类的声明。
#include "ui_widget.h"        // 包含由Qt Designer生成的UI类的声明。
#include "qdebug.h"           // 包含用于调试的qDebug类。
#include "qfiledialog.h"      // 包含用于文件对话框的QFileDialog类。
#include "qdir.h"             // 包含用于目录操作的QDir类。
#include "QMediaPlayer.h"     // 包含用于媒体播放的QMediaPlayer类。
#include "QAudioOutput.h"     // 包含用于音频输出的QAudioOutput类。hy
#include "qurl.h"             // 包含用于处理URL的QUrl类。

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // 初始化 QAudioOutput 和 QMediaPlayer 对象
    audioOutput = new QAudioOutput(this);
    mediaPlayer = new QMediaPlayer(this);

    // 设置音频输出
    mediaPlayer->setAudioOutput(audioOutput);

    // 设置媒体源文件
    // mediaPlayer->setSource(QUrl::fromLocalFile("C:/Users/20180129/Desktop/0712/test0712/assets/music/music/02-12 隐藏的爱.mp3"));

    // 播放媒体
    // mediaPlayer->play();

    // 连接媒体持续时间变化信号到相应的槽函数
    connect(mediaPlayer, &QMediaPlayer::durationChanged, this, [=](qint64 duration) {
        ui->totalLabel->setText(QString("%1:%2")
                                    .arg(duration / 1000 / 60, 2, 10, QChar('0'))
                                    .arg(duration / 1000 % 60, 2, 10, QChar('0')));
        ui->playCourseSlider->setRange(0, duration);
    });

    // 连接媒体位置变化信号到相应的槽函数
    connect(mediaPlayer, &QMediaPlayer::positionChanged, this, [=](qint64 pos) {
        ui->curLabel->setText(QString("%1:%2")
                                  .arg(pos / 1000 / 60, 2, 10, QChar('0'))
                                  .arg(pos / 1000 % 60, 2, 10, QChar('0')));
        ui->playCourseSlider->setValue(pos);
    });

    // 连接滑动条移动信号到媒体播放器的设置位置槽函数
    connect(ui->playCourseSlider, &QSlider::sliderMoved, mediaPlayer, &QMediaPlayer::setPosition);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    auto path = QFileDialog::getExistingDirectory(this, "Open", "C:\\Users\\sunal\\Desktop\\music");  // 打开目录选择对话框
    QDir dir(path);  // 创建目录对象
    auto musicList = dir.entryList(QStringList() << "*.*");  // 获取目录中所有.mp3文件的列表
    ui->listWidget->addItems(musicList);  // 将音乐列表添加到UI的listWidget中
    ui->listWidget->setCurrentRow(0);
    for(auto file :musicList)
     playList.append(QUrl::fromLocalFile(path+"/"+file));
    qInfo()<<playList;
}

void Widget::on_pushButton_3_clicked()
{
    if(playList.empty())  // 检查播放列表是否为空
    {
        return;
    }

    switch(mediaPlayer->playbackState())  // 根据当前播放状态进行处理
    {
    case QMediaPlayer::PlaybackState::StoppedState:
        curPlayIndex = ui->listWidget->currentRow();  // 获取当前选中的行号
        mediaPlayer->setSource(playList[curPlayIndex]);  // 设置媒体源
        mediaPlayer->play();  // 开始播放
        break;

    case QMediaPlayer::PlaybackState::PlayingState:
        mediaPlayer->pause();  // 如果正在播放，则暂停
        break;

    case QMediaPlayer::PlaybackState::PausedState:
        mediaPlayer->play();  // 如果暂停，则继续播放
        break;
    }
}

void Widget::on_pushButton_2_clicked()
{

}

