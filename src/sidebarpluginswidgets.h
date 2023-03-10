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
#ifndef SIDEBARPLUGINSWIDGETS_H
#define SIDEBARPLUGINSWIDGETS_H

#define  KYLIN_ALARM_CLACK_ICON      ":/data/images/kylin-alarm-clock.svg"
#define  KYLIN_NOTEBOOK              ":/data/images/kylin-notebook.svg"
#define  KYLIN_FEEDBACK              ":/data/images/kylin-feedback.png"
#define  KYLIN_SIDEBAR_SMALL_PLUGINS ":/data/qss/SidebarSmallPlugins.css"
#define  KYLIN_STATE_CLIPBOARD       1
#define  KYLIN_STATE_SMALL_PLUGINS   2
#define  KYLIN_PLUGINS_NUM           8
#include <QtWidgets>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <glib.h>
#include <QToolButton>
#include <QStyle>
#include <QStackedWidget>
#include <QGSettings>
#include "smallpluginsbutton.h"
#include "smallpluginsmanage.h"
#include "mostgrandwidget.h"
#include "pluginstoolbutton.h"
#include "customstyleCleanPushbutton.h"
#include "customstyle.h"


class m_ToolButton : public QToolButton
{

public:
    explicit m_ToolButton();
    QString pluginname;
    void enterEvent(QEvent *event);
signals:

};


class sidebarPluginsWidgets : public QWidget
{
    Q_OBJECT
public:
    explicit sidebarPluginsWidgets(QWidget *parent = nullptr);
    ~sidebarPluginsWidgets();
    static sidebarPluginsWidgets* getInstancePluinsWidgets();
    static void initPluginsWidgets();
    void AddPluginWidgetInterface();
    void initUpGroupBoxButton();                                  //???????????? ????????? ????????? ????????? groupBox???????????????
    void initUnGroupBox();                                        //???????????? ??????????????????  ??????????????????????????? ?????????
    void initLableBackgroundAnimation();                          //???????????????
    void initCliboardAnimation();                                 //???????????????????????????
    void initSmallPluginsAnimation();                             //???????????????????????????
    void setClipboardButtonBackgroundIsBlue();                    //???????????????????????????????????????
    void setSmallPluginsButtonBackgroudIsBlue();                  //???????????????????????????????????????
    void setClipboardButtonBackgroundIsBlank();                   //???????????????????????????????????????
    void setSmallPluginsButtonBackgroudIsBlank();                 //???????????????????????????????????????
    void setClipboardWidgetSize(int ClipHight);                   //????????????????????????
    void loadSmallPlugins();                                      //???????????????????????????sidebar??????
    void setButtonFont();

    QString getAppIcon(QString desktopfp);                        //??????desktop???????????????????????????
    QString getAppName(QString desktopfp);                        //??????????????????
    QString getAppExec(QString desktopfp);                        //?????????????????????????????????
    void    addDesktopFileName();                                 //????????????desktop?????????????????????desktopfpList???

    void    parsingDesktopFile();                                 //??????desktop??????
    m_ToolButton* StructToolButtol(QString icon, QString name);    //??????QToolButton
    QStringList m_desktopfpList;                                  //?????????????????????desktop????????????

    QString SetFormatBody(QString text, QLabel *label);           //??????...
    QString judgeBlankLine(QStringList list);
    bool    substringSposition(QString formatBody, QStringList list);

    QVBoxLayout *m_pWidgetOutVLayout;                             //???????????????
    QHBoxLayout *m_pGrouBoxUpButtonHLayout;                       //GroupBox???Button????????????
    QGridLayout *m_pGroupBoxUnSmallPluginsGLayout;                //????????????????????????

    QStackedWidget  *m_pstackWidget;                              //??????????????????????????????????????????
    QWidget     *m_pButtonWidget;                                 //????????????Box
    QWidget     *m_pClipboardWidget;                              //??????????????????Box
    QWidget     *m_pPluginsButtonWidget;                          //?????????????????????Box

    QPushButton     *m_pFoldButton;                               //????????????
    QPushButton     *m_pSpreadButton;                             //????????????
    QPushButton     *m_pBlueBackgroundButton;                     //???????????????
    SmallPluginsButton *m_pClipboardButton;                       //????????? ??????????????????
    SmallPluginsButton *m_pSidebarPluginButton;                   //?????? ??????????????????
    QToolButton *m_pNotebookButton;                               //????????? ??????
    QToolButton *m_pAlarmClockButton;                             //??????  ??????
    QToolButton *m_pFeedbackButtom;                               //??????????????????

    QPropertyAnimation *m_pAnimationLeftRight;
    QPropertyAnimation *m_pAnimationRightLeft;
    QPropertyAnimation *m_pAnimationClipbarod;
    QPropertyAnimation *m_pAnimationSmallWidget;

    QGSettings      *m_pTransparency = nullptr;                   // ?????????gsetting???

    //?????????
    bool    ClipBoardBool = false;                                // ??????????????????????????????bool???
    bool    SmallPluginsBool = false;                             // ?????????????????????????????????bool???

    int     m_add_x = 0;
    int     m_add_y = 1;
    int     m_cliboardHight;                                      // ??????????????????????????????
    QMap<QLabel*, QString> m_LabelTextMap;                        // ??????label??????????????????Map???


signals:
    void FontModifyComplete();

private slots:
    void m_pClipBoardStateSlots();
    void m_pSmallPluginsStateSlots();

    void m_ClipboardButtonSlots();
    void m_SidebarPluginButtonSlots();

    void m_pFoldButtonSlots();
    void m_pSpreadButtonSlots();

    void m_AnimationClipbarodEndSlots();
    void m_AnimationSmallWidgetEndSlots();
    void getTransparencyValue(const QString key);                                                //?????????gsetting???
protected:
    void paintEvent(QPaintEvent *e);

};

#endif // SIDEBARPLUGINSWIDGETS_H
