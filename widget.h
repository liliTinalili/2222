#ifndef WIDGET_H
#define WIDGET_H
#include <QWidget>

#include "ui_widget.h"
#include <QDebug>
#include <QFileDialog>
#include <QDir>
#include <QMediaPlayer>
#include <QAudioOutput>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Widget *ui;
    QMediaPlayer *mediaPlayer;         // 声明 QMediaPlayer 成员变量
    QAudioOutput *audioOutput;         // 声明 QAudioOutput 成员变量
    QList<QUrl> playList;              // 声明播放列表
    int curPlayIndex;                  // 声明当前播放索引
};
#endif // WIDGET_H
