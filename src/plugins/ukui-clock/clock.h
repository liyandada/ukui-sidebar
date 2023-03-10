/*
* Copyright (C) 2019 Tianjin KYLIN Information Technology Co., Ltd.
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 3, or (at your option)
* any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, see <http://www.gnu.org/licenses/&gt;.
*
*/
#ifndef CLOCK_H
#define CLOCK_H
#include <QPainterPath>
#include <QWidget>
#include <QTimer>
#include <QTime>
#include <QQueue>
#include <QSlider>
#include <QVBoxLayout>
#include <QPushButton>
#include <QPainter>
#include <QMouseEvent>
#include <QLCDNumber>
#include <QMediaPlayer>
#include <QFrame>
#include <itemNew.h>
#include <QListWidgetItem>
#include <QPaintEvent>
#include <QPointF>
#include <QLineEdit>
#include <QPropertyAnimation>
#include <QCloseEvent>
#include <QMenu>
#include <QFontDatabase>
#include <math.h>
#include <QTimerEvent>
#include <QDialog>
#include <QSpinBox>
#include <QComboBox>
#include <QLabel>
#include <QPixmap>
#include <QMatrix>
#include <QFont>
#include <QMediaPlaylist>
#include <QUrl>
#include <QMessageBox>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QModelIndex>
#include <QSqlQuery>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QDebug>
#include <unistd.h>
#include <QMessageBox>
#include <QBitmap>
#include <QProcess>
#include <QScreen>
#include <QScroller>
#include <QTranslator>
#include <QDesktopWidget>
#include <QGraphicsOpacityEffect>
#include "stopwatchItem.h"
#include "verticalScroll24.h"
#include "verticalScroll60.h"
#include "verticalScroll99.h"
#include "dotlineDemo.h"
#include "setAlarmRepeatDialog.h"
#include "setupPage.h"
#include "adaptscreeninfo.h"
#include "about.h"
#include "debug.h"
#include "connection.h"
#include "set_clock.h"
#include "noticeDialog.h"
#include "noticeAlarm.h"
#include "ui_noticeAlarm.h"
#include "deleteMsg.h"
#include "ui_deleteMsg.h"
#include "btnNew.h"
#include "closeOrHide.h"
#include "ui_setupPage.h"

class QDialog;
class QSpinBox;
class QComboBox;
class QLabel;
class QFont;
class QPushButton;
class QMediaPlaylist;
class QSqlTableModel;
class Btn_new;
class close_or_hide;


#define ORG_UKUI_STYLE            "org.ukui.style"
#define STYLE_NAME                "styleName"
#define STYLE_NAME_KEY_DARK       "ukui-dark"
#define STYLE_NAME_KEY_DEFAULT    "ukui-default"
#define STYLE_NAME_KEY_BLACK      "ukui-black"
#define STYLE_NAME_KEY_LIGHT      "ukui-light"
#define STYLE_NAME_KEY_WHITE      "ukui-white"
#define STYLE_ICON                "icon-theme-name"
#define STYLE_ICON_NAME           "iconThemeName"

namespace Ui {
class Clock;
}

class Clock : public QWidget
{
    Q_OBJECT

public:

    explicit Clock(QWidget *parent = nullptr);
    ~Clock();

    void paintEvent(QPaintEvent *event);
    bool eventFilter(QObject *watched, QEvent *event);
    void showPaint();
    void showPaint1();
    void showPaint7();
    void showPaint8();

    Ui::Clock *ui;
    QSqlTableModel *model_setup;

protected:
    void paintEvent1(QPaintEvent *);
    QPixmap ChangeImageColor(QPixmap sourcePixmap, QColor origColor, QColor destColor);
    void closeEvent(QCloseEvent *event);

public slots:
    void  CountdownPageSwitch ();                                                        //???????????????
                                                                                         // Countdown switch
    void  AlarmPageSwitch ();                                                            //??????????????????
                                                                                         // Alarm window switching
    void  StopwatchPageSwitch ();                                                        //??????????????????
                                                                                         // Stopwatch window switc
    void  settingsStyle();                                                               //????????????

    void  blackStyle();                                                                  //????????????

    void  whiteStyle();                                                                  //????????????

    void  drawNoAlarmPrompt();                                                           //?????????????????????
                                                                                         //Draw no alarm prompt
    QString loadFontFamilyFromTTF();                                                     //????????????


private slots:
    void buttonImageInit();                                                              //???????????????????????????
                                                                                         // Alarm button picture initialization
    void CountdownInit();                                                                //?????????????????????
                                                                                         // Countdown page initialization
    void stopwatchInit();                                                                //??????????????????
                                                                                         // Stopwatch page initialization
    void clockInit();                                                                    //??????????????????
                                                                                         // Alarm page initialization
    void setupInit();                                                                    //??????????????????
                                                                                         // Default initial settings
    void noticeDialogShow(int,int);                                                      //????????????
                                                                                         // Notification Popup
    void modelSetupSet();                                                                //????????????????????????????????????
                                                                                         // Default setting database data initialization
    void CountDown();                                                                    //????????????
                                                                                         // Stopwatch execution
    void onPushbuttonStartClicked();                                                     //????????????????????????
                                                                                         // Stopwatch start pause continue
    void onPushbuttonRingClicked();                                                      //??????
                                                                                         // times count
    void onPushbuttonTimeselectClicked();                                                //??????
                                                                                         // reset
    void windowClosingClicked();                                                         //????????????
                                                                                         // window closing
    void windowMinimizingClicked();                                                      //???????????????
                                                                                         // window minimizing
    void timerUpdate();                                                                  //?????????????????????????????????
                                                                                         // Dynamic monitoring alarm clock and local time
    void textTimerupdate();                                                              //?????????????????????
                                                                                         // Electronic watch above alarm clock
    void setAlarmClock();                                                                //????????????????????????
                                                                                         // New alarm button callback
    void cancelAlarmClock();                                                             //????????????dialog??????
                                                                                         // Add alarm dialogclose
    void updateAlarmClock();                                                             //???????????????????????????
                                                                                         // Redraw window, update alarm clock
    void OnOffAlarm();                                                                   //????????????
                                                                                         // Alarm switch
    void deleteAlarm();                                                                  //???????????????????????????????????????
                                                                                         // Alarm re edit page delete alarm callback
    void stopPlayMusic();                                                                //????????????
                                                                                         // Stop music
    void ChooseAlarmMusic();                                                             //????????????
                                                                                         //Choose music
    void rePlayMusic();                                                                  //????????????
                                                                                         // Play music
    void aitemNew();                                                                     //??????item
                                                                                         // Add item
    void listdoubleClickslot();                                                          //?????????????????????????????????
                                                                                         // Double click the alarm clock to open the re edit page
    void listClickslot();                                                                //????????????????????????????????????
                                                                                         // Click the alarm to display the remaining time
    void alarmReEditClicked();                                                           //???????????????????????????
                                                                                         // Alarm re edit save callback
    void stopwatchStartAnimation();                                                      //???????????????????????????
                                                                                         // Countdown start animation move
    void stopwatchStopAnimation();                                                       //???????????????????????????
                                                                                         // Countdown start animation move
    void statCountdown();                                                                //???????????????
                                                                                         // Countdown execution
    void setcoutdownNumber(int h, int m, int s);                                         //???????????????????????????
                                                                                         // Set the initial countdown time
    void startbtnCountdown();                                                            //???????????????-????????????
                                                                                         // Countdown start end callback
    void onMin_5btnClicked();                                                            //?????????5??????????????????
                                                                                         // Countdown 5 minutes set callback
    void onMin_10btnClicked();                                                           //?????????10??????????????????
                                                                                         // Countdown 10 minutes set callback
    void onMin_20btnClicked();                                                           //?????????20??????????????????
                                                                                         // Countdown 20 minutes set callback
    void onMin_30btnClicked();                                                           //?????????30??????????????????
                                                                                         // Countdown 30 minutes set callback
    void onMin_60btnClicked();                                                           //?????????60??????????????????
                                                                                         // Countdown 60 minutes set callback
    void getCountdownOverTime();                                                         //???????????????????????????
                                                                                         // Get countdown end time
    void onCountPushClicked();                                                           //?????????-??????????????????
                                                                                         // Countdown - pause resume callback
    void stopwatchJg();                                                                  //??????????????????????????????
                                                                                         // Interval calculation execution callback
    void changeTimeNum(int Hour,int Minute);                                             //?????????????????? ????????????
                                                                                         // Modify time singular to two digits
    void countdownSetStartTime();                                                        //???????????????????????????
                                                                                         // Countdown initial digital dial
    void alarmSetStartTime();                                                            //?????????????????????????????????
                                                                                         // Alarm clock initialization digital turntable drawing
    void alarmCancelSave();                                                              //??????????????????????????????
                                                                                         // Cancel callback in alarm new interface
    void setAlarmSave();                                                                 //??????????????????????????????
                                                                                         // Alarm new interface save callback
    void verticalscrollRingTime();                                                       //????????????????????????????????????????????????????????????
                                                                                         // Alarm clock new and re edit interface remaining time real-time display callback
    void alarmRepeat();                                                                  //????????????????????????????????????????????????
                                                                                         // Alarm clock initialization workday selection interface drawing callback
    void repeatListclickslot();                                                          //????????????????????????
                                                                                         // Repeat option click callback
    void selectAlarmMusic();                                                             //???????????????????????????????????????
                                                                                         // Alarm clock initialization music selection interface callback
    void musicListclickslot();                                                           //?????????????????????????????????
                                                                                         // Alarm initialization Click to select music
    void timeMusic();                                                                    //?????????????????????????????????????????????
                                                                                         // Alarm clock initialization music time selection interface callback
    void timeMusicListclickslot();                                                       //??????????????????????????????
                                                                                         // Click to select music duration callback
    void setUpPage();                                                                    //????????????????????????
                                                                                         // Set page draw callback
    void alarmClcokSelfStarting();                                                       //???????????????????????????
                                                                                         // Power on self start switch callback
    void MuteStarting();                                                                 //??????????????????
                                                                                         // Mute switch callback
    void setVolumeValue(int value);                                                      //??????????????????
                                                                                         // Set volume callback
    void countdownMusicSellect();                                                        //?????????????????????
                                                                                         // Countdown music selection
    void countMusicListclickslot();                                                      //?????????????????????????????????
                                                                                         // Countdown music selection single callback
    void countdownNoticeDialogShow();                                                    //?????????????????????
                                                                                         // Countdown notification pop-up
    void offAlarm(int );                                                                 //??????????????????????????????
                                                                                         // Turn off the alarm separately if it is not repeated
    int getAlarmClockWillRingDays(int num);                                              //????????????????????????????????????
                                                                                         // Calculate the next alarm ring interval
    int getAlarmClockWillRingDays_2(int num);                                            //????????????????????????????????????
                                                                                         // Calculate the next alarm ring interval
    QString changeNumToStr(int alarmHour);                                               //???????????????
                                                                                         // Integer to character
    void onCustomContextMenuRequested(const QPoint &pos);                                //????????????????????????????????????

    void countStatBtnGray();

private:
    QPoint m_startPoint;
    QTimer *timer = nullptr;
    QTimer *countdown_timer = nullptr;
    QTimer *timer_2 = nullptr;
    int hour, minute, second, pushflag ;
    int stopwatch_hour, stopwatch_minute, stopwatch_second ;
    int countdown_hour, countdown_minute, countdown_second, countdown_pushflag ;
    int alarmHour;
    int alarmMinute;
    int cPauseTime;
    bool isStarted;
    bool countdown_isStarted;
    bool countdown_isStarted_2;
    bool stopwatch_isStarted;

    QMediaPlayer *player;
    QString ring;//????????????
                 // Ring name
    QPixmap pixmap1;
    QPixmap pixmap2;
    QPixmap pixmap3;
    QPixmap pixmap4;
    QPixmap pixmap5;
    QPixmap pixmap6;
    QPixmap pixmap7;
    QPixmap pixmap8;
    QPixmap pixmap9;
    QPixmap pixmap10;
    QPixmap pixmap11;
    QPixmap bgPixmap;
    QPixmap repeat_on_Pixmap;
    QPixmap repeat_off_Pixmap;
    QPixmap hourPixmap;
    QPixmap minutePixmap;
    QPixmap secondPixmap;
    QPixmap delBtnPixmap;
    QPixmap on_pixmap;
    QPixmap off_pixmap;
    QPixmap clock_icon;

    QDialog *dialog;
    QFont alarmFont;
    QSpinBox *hourBox;
    QSpinBox *minuteBox;
    QComboBox *pauseTime;

    QMediaPlayer *player_alarm;
    QMediaPlaylist *mediaList; /*????????????
                                 playlist*/
    QSqlTableModel *model;  /*?????????
                              data base*/
    QSqlTableModel *model_Stopwatch;
    QString musicPath;

    item_new *w1[20];
    QListWidgetItem *aItem[20];
    stopwatch_item *stopwatch_w[100];
    QListWidgetItem *stopwatch_aItem[100];
    QString stopwatch_h;QString stopwatch_m;QString stopwatch_s;
    QString stopwatch_jg_h ="00";QString stopwatch_jg_m= "00";QString stopwatch_jg_s= "00";
    QString alarmHour_str; QString alarmMinute_str;

    int stopwatch_item_flag = 0;
    int clock_num = 0;
    int on_off_flag = 0;
    int add_change_flag = 0;
    int change_alarm_line = 0;
    int medel_flag = 0;
    int continu_flag = 0;
    int alarm_repeat_flag = 0;
    int repeat_day[9];   /*???????????????????????????
                           Select and save mediation for duplicate days*/
    int repeat_new_or_edit_flag;  /*??????????????? ?????????,???????????????,??????????????????????????????;
                                    Whether to create or re edit the duplicate day is determined. The database numbers obtained by the two methods are different*/
    int stopwatch_Animation = 0;
    int system_time_flag;
    int last_day_ring = 0;

    QTimer *timer_Surplus;
    QTimer *timer_set_page;
    VerticalScroll_99 * timer_ring99;
    VerticalScroll_60 * timer_ring60;
    VerticalScroll_60 * timer_ring60_2;
    VerticalScroll_24 * timer_alarm_start24;
    VerticalScroll_60 * timer_alarm_start60;

    set_alarm_repeat_Dialog *dialog_repeat = nullptr;
    set_alarm_repeat_Dialog *dialog_music = nullptr;
    set_alarm_repeat_Dialog *time_music = nullptr;
    set_alarm_repeat_Dialog *count_music_sellect = nullptr;

    close_or_hide *close_or_hide_page;
    adaptScreenInfo *m_pSreenInfo = nullptr;

    QWidget *grand = nullptr;
    setuppage  *setup_page= nullptr;
    QString repeat_str;
    QString repeat_str_model;
    QString music_str_model;
    QString time_music_str_model;
    QString clock_name;
    QLineEdit *lineEdit= nullptr ;
    QPropertyAnimation *animation1;
    QPropertyAnimation *animation2;
    QPropertyAnimation *animation3;

    QPushButton *pushcount;
    QPushButton *pushclock;
    QPushButton *pushstop;
    QPushButton *count_stat;
    QWidget *shadow;
    QWidget *shadow1;

    QPoint dragPosition;                                            /*????????????*/
    bool mousePressed;                                              /*??????????????????*/

    Btn_new *count_sel;
    Btn_new *count_sel_1;
    Btn_new *repeat_sel;
    Btn_new *time_sel;
    Btn_new *ring_sel;
    QMenu *m_menu;                                                  /*????????????*/
    QAction *m_menuAction;                                          /*????????????*/

    QMenu *popMenu_In_ListWidget_;                                  /*????????????????????????*/
    QAction *action_Delete_In_ListWidget_ ;
    QAction *action_Clear_In_ListWidget_ ;                          /*????????????????????????*/
    Natice_alarm *countdownNoticeDialog;
};


#endif // CLOCK_H
