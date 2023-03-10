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

#include "buttonwidget.h"
#include <QMouseEvent>
#include <QSvgRenderer>
#include <QPixmap>
#include <QPainter>
#include <QVBoxLayout>
#include <QSvgWidget>
#include <QDebug>

ButtonWidget::ButtonWidget(QString strIcon, QString strHoverIcon, QString strPressIcon,QSize normalIconSize,QSize pressIconSize)
{
    m_strIcon = strIcon;
    m_strHoverIcon = strHoverIcon;
    m_strPressIcon = strPressIcon;

    this->setFixedWidth(24);
    this->setFixedHeight(24);
    QVBoxLayout* pVBoxLayout = new QVBoxLayout;
    pVBoxLayout->setContentsMargins(0,0,0,0);
    pVBoxLayout->setSpacing(0);

    m_ToolButton = new QLabel;
    m_pTakeinSvgRender = new QSvgRenderer(m_ToolButton);
    m_pTakeinSvgRender->load(m_strIcon);
    m_ToolButton->setAttribute(Qt::WA_TranslucentBackground);
    m_pTakeinPixmap = new QPixmap(normalIconSize);
    m_pTakeinPressPixmap = new QPixmap(pressIconSize);
    m_pTakeinPixmap->fill(Qt::transparent);
    QPainter takeinPainter(m_pTakeinPixmap);
    m_pTakeinSvgRender->render(&takeinPainter);
    m_ToolButton->setPixmap(*m_pTakeinPixmap);

    pVBoxLayout->addWidget(m_ToolButton, 0, Qt::AlignHCenter | Qt::AlignVCenter);
    this->setLayout(pVBoxLayout);

    return;
}

void ButtonWidget::enterEvent(QEvent *event)
{
    Q_UNUSED(event);
    m_pTakeinSvgRender->load(m_strHoverIcon);
    m_pTakeinPixmap->fill(Qt::transparent);
    QPainter takeinPainter(m_pTakeinPixmap);
    m_pTakeinSvgRender->render(&takeinPainter);
    m_ToolButton->setPixmap(*m_pTakeinPixmap);

    return;
}

void ButtonWidget::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
    m_pTakeinSvgRender->load(m_strIcon);
    m_pTakeinPixmap->fill(Qt::transparent);
    QPainter takeinPainter(m_pTakeinPixmap);
    m_pTakeinSvgRender->render(&takeinPainter);
    m_ToolButton->setPixmap(*m_pTakeinPixmap);

    return;
}

//??????????????????
void ButtonWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->buttons() == Qt::LeftButton)
    {
        m_pTakeinSvgRender->load(m_strPressIcon);
        m_pTakeinPressPixmap->fill(Qt::transparent);
        QPainter takeinPainter(m_pTakeinPressPixmap);
        m_pTakeinSvgRender->render(&takeinPainter);
        m_ToolButton->setPixmap(*m_pTakeinPressPixmap);
    }

    return;
}

void ButtonWidget::mouseReleaseEvent(QMouseEvent *event)
{
    int x = event->x();
    int y = event->y();
    qDebug()<<"ButtonWidget::mouseReleaseEvent" <<x << y;

    //?????????QRect(0, 0, 24, 24));?????????????????????????????????
    if (x >= 0 && x <= 24 && y >= 0 && y<=24)
    {
        emit Sig_clicked();
    }

    return;
}
