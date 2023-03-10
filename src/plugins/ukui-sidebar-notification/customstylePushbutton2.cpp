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
#include "customstylePushbutton2.h"
#include <QWidget>

#include <QStyleOption>
#include <QPainter>

#include <QDebug>

CustomStyle_pushbutton_2::CustomStyle_pushbutton_2(const QString &proxyStyleName, QObject *parent) : QProxyStyle (proxyStyleName)
{
    Q_UNUSED(parent);
}

void CustomStyle_pushbutton_2::drawComplexControl(QStyle::ComplexControl control, const QStyleOptionComplex *option, QPainter *painter, const QWidget *widget) const
{
    return QProxyStyle::drawComplexControl(control, option, painter, widget);
}

void CustomStyle_pushbutton_2::drawControl(QStyle::ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const
{
    switch (element) {
    case QStyle::CE_PushButton: {
        QStyleOptionButton button = *qstyleoption_cast<const QStyleOptionButton *>(option);
        button.palette.setColor(QPalette::HighlightedText, button.palette.buttonText().color());
        return QProxyStyle::drawControl(element, &button, painter, widget);
        break;
    }
    default:
        break;
    }
    return QProxyStyle::drawControl(element, option, painter, widget);
}

void CustomStyle_pushbutton_2::drawItemPixmap(QPainter *painter, const QRect &rectangle, int alignment, const QPixmap &pixmap) const
{
    return QProxyStyle::drawItemPixmap(painter, rectangle, alignment, pixmap);
}

void CustomStyle_pushbutton_2::drawItemText(QPainter *painter, const QRect &rectangle, int alignment, const QPalette &palette, bool enabled, const QString &text, QPalette::ColorRole textRole) const
{
    return QProxyStyle::drawItemText(painter, rectangle, alignment, palette, enabled, text, textRole);
}

/// ????????????button????????????????????????state??????????????????????????????value??????????????????????????????
/// ??????????????????hover????????????????????????painter??????????????????????????????
/// ?????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????
/// ????????????????????????????????????????????????QWidget::update()????????????????????????
/// ???????????????????????????button?????????????????????????????????draw??????????????????????????????????????????
///
/// ??????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????
/// ????????????????????????????????????????????????????????????????????????????????????
void CustomStyle_pushbutton_2::drawPrimitive(QStyle::PrimitiveElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const
{
//    if (element == PE_PanelButtonCommand) {
//        qDebug()<<"draw pe button";
//        if (widget) {
//            bool isPressed = false;
//            bool isHover = false;
//            if (!option->state.testFlag(State_Sunken)) {
//                if (option->state.testFlag(State_MouseOver)) {
//                    isHover = true;
//                }
//            } else {
//                isPressed = true;
//            }

//            QStyleOption opt = *option;
//            if (isHover) {
//                QColor color(255,255,255,51);
//                opt.palette.setColor(QPalette::Highlight, color);

//            }
//            if (isPressed) {
//                QColor color(255,255,255,21);
//                opt.palette.setColor(QPalette::Highlight, color);
//            }
//            if (!isHover && !isPressed) {
//                QColor color(255,255,255,31);
//                opt.palette.setColor(QPalette::Button,color);
//            }
//            return QProxyStyle::drawPrimitive(element, &opt, painter, widget);
//        }
//    }
//    return QProxyStyle::drawPrimitive(element, option, painter, widget);
    if (element == PE_PanelButtonCommand) {
        if (widget) {
            if (option->state & State_MouseOver) {
                if (option->state &  State_Sunken) {
                    painter->save();
                    painter->setRenderHint(QPainter::Antialiasing,true);
                    painter->setPen(Qt::NoPen);
                    QColor color(255,255,255,21);
                    painter->setBrush(color);
                    painter->drawRoundedRect(option->rect, 4, 4);
                    painter->restore();
                } else {
                    painter->save();
                    painter->setRenderHint(QPainter::Antialiasing,true);
                    painter->setPen(Qt::NoPen);
                    QColor color(255,255,255,51);
                    painter->setBrush(color);
                    painter->drawRoundedRect(option->rect, 4, 4);
                    painter->restore();
                }
            } else {
                painter->save();
                painter->setRenderHint(QPainter::Antialiasing,true);
                painter->setPen(Qt::NoPen);
                QColor color(255,255,255,0);
                painter->setBrush(color);
                painter->drawRoundedRect(option->rect, 4, 4);
                painter->restore();
            }
            return;
        }
    }
    return QProxyStyle::drawPrimitive(element, option, painter, widget);
}

QPixmap CustomStyle_pushbutton_2::generatedIconPixmap(QIcon::Mode iconMode, const QPixmap &pixmap, const QStyleOption *option) const
{
    return QProxyStyle::generatedIconPixmap(iconMode, pixmap, option);
}

QStyle::SubControl CustomStyle_pushbutton_2::hitTestComplexControl(QStyle::ComplexControl control, const QStyleOptionComplex *option, const QPoint &position, const QWidget *widget) const
{
    return QProxyStyle::hitTestComplexControl(control, option, position, widget);
}

QRect CustomStyle_pushbutton_2::itemPixmapRect(const QRect &rectangle, int alignment, const QPixmap &pixmap) const
{
    return QProxyStyle::itemPixmapRect(rectangle, alignment, pixmap);
}

QRect CustomStyle_pushbutton_2::itemTextRect(const QFontMetrics &metrics, const QRect &rectangle, int alignment, bool enabled, const QString &text) const
{
    return QProxyStyle::itemTextRect(metrics, rectangle, alignment, enabled, text);
}

int CustomStyle_pushbutton_2::pixelMetric(QStyle::PixelMetric metric, const QStyleOption *option, const QWidget *widget) const
{
    return QProxyStyle::pixelMetric(metric, option, widget);
}

/// ????????????????????????widget?????????????????????
/// ?????????style?????????????????????widget????????????polish???unpolish????????????
/// ?????????????????????polish??????widget????????????????????????????????????????????????unpolish????????????
void CustomStyle_pushbutton_2::polish(QWidget *widget)
{
    return QProxyStyle::polish(widget);
}

void CustomStyle_pushbutton_2::polish(QApplication *application)
{
    return QProxyStyle::polish(application);
}

void CustomStyle_pushbutton_2::polish(QPalette &palette)
{
    return QProxyStyle::polish(palette);
}

void CustomStyle_pushbutton_2::unpolish(QWidget *widget)
{
    return QProxyStyle::unpolish(widget);
}

void CustomStyle_pushbutton_2::unpolish(QApplication *application)
{
    return QProxyStyle::unpolish(application);
}

QSize CustomStyle_pushbutton_2::sizeFromContents(QStyle::ContentsType type, const QStyleOption *option, const QSize &contentsSize, const QWidget *widget) const
{
    return QProxyStyle::sizeFromContents(type, option, contentsSize, widget);
}

QIcon CustomStyle_pushbutton_2::standardIcon(QStyle::StandardPixmap standardIcon, const QStyleOption *option, const QWidget *widget) const
{
    return QProxyStyle::standardIcon(standardIcon, option, widget);
}

QPalette CustomStyle_pushbutton_2::standardPalette() const
{
    return QProxyStyle::standardPalette();
}

int CustomStyle_pushbutton_2::styleHint(QStyle::StyleHint hint, const QStyleOption *option, const QWidget *widget, QStyleHintReturn *returnData) const
{
    return QProxyStyle::styleHint(hint, option, widget, returnData);
}

QRect CustomStyle_pushbutton_2::subControlRect(QStyle::ComplexControl control, const QStyleOptionComplex *option, QStyle::SubControl subControl, const QWidget *widget) const
{
    return QProxyStyle::subControlRect(control, option, subControl, widget);
}

QRect CustomStyle_pushbutton_2::subElementRect(QStyle::SubElement element, const QStyleOption *option, const QWidget *widget) const
{
    return QProxyStyle::subElementRect(element, option, widget);
}
