/* -*- Mode: C++; indent-tabs-mode: nil; tab-width: 4 -*-
 * -*- coding: utf-8 -*-
 *
 * Copyright (C) 2020 KylinSoft Co., Ltd.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

//#include <iostream>
#include <QVector>
#include <QSet>
#include "xeventmonitor.h"

// Virtual button codes that are not defined by X11.
#define Button1            1
#define Button2            2
#define Button3            3
#define WheelUp            4
#define WheelDown          5
#define WheelLeft          6
#define WheelRight         7
#define XButton1           8
#define XButton2           9

XEventMonitor *XEventMonitor::instance_ = new XEventMonitor();

QVector<KeySym> ModifiersVec{
    XK_Control_L,
    XK_Control_R,
    XK_Shift_L,
    XK_Shift_R,
    XK_Super_L,
    XK_Super_R,
    XK_Alt_L,
    XK_Alt_R
};

class XEventMonitorPrivate
{
public:
    XEventMonitorPrivate(XEventMonitor *parent);
    virtual ~XEventMonitorPrivate();
    void run();

protected:
    XEventMonitor *q_ptr;
    QSet<KeySym> modifiers;

    bool filterWheelEvent(int detail);
    static void callback(XPointer trash, XRecordInterceptData* data);
    void handleRecordEvent(XRecordInterceptData *);
    void emitButtonSignal(const char *member, xEvent *event);
    void emitKeySignal(const char *member, xEvent *event);
    void updateModifier(xEvent *event, bool isAdd);

private:
    Q_DECLARE_PUBLIC(XEventMonitor)
};

XEventMonitorPrivate::XEventMonitorPrivate(XEventMonitor *parent)
    : q_ptr(parent)
{

}

XEventMonitorPrivate::~XEventMonitorPrivate()
{

}

void XEventMonitorPrivate::emitButtonSignal(const char *member, xEvent *event)
{
    int x = event->u.keyButtonPointer.rootX;
    int y = event->u.keyButtonPointer.rootY;
    QMetaObject::invokeMethod(q_ptr, member,
                              Qt::DirectConnection,
                              Q_ARG(int, x),
                              Q_ARG(int, y));
}
#include <syslog.h>
void XEventMonitorPrivate::emitKeySignal(const char *member, xEvent *event)
{
    Display *display = XOpenDisplay(NULL);

    int keyCode = event->u.u.detail;
    KeySym keySym = XkbKeycodeToKeysym(display, event->u.u.detail, 0, 0);

    QString keyStrSplice;
    for(auto modifier : modifiers)
    {
        keyStrSplice += QString(XKeysymToString(modifier)) + "+";
    }
    //??????????????????
    if(ModifiersVec.contains(keySym) && !modifiers.isEmpty())
        keyStrSplice.remove(keyStrSplice.length() - 1, 1);
    else
        keyStrSplice += XKeysymToString(keySym);

    QMetaObject::invokeMethod(q_ptr, member,
                              Qt::AutoConnection,
                              Q_ARG(int, keyCode));
    QMetaObject::invokeMethod(q_ptr, member,
                              Qt::AutoConnection,
                              Q_ARG(QString, keyStrSplice));

    XCloseDisplay(display);
}

void XEventMonitorPrivate::run()
{
    Display* display = XOpenDisplay(0);
    if (display == 0) {
        fprintf(stderr, "unable to open display\n");
        return;
    }

    // Receive from ALL clients, including future clients.
    XRecordClientSpec clients = XRecordAllClients;
    XRecordRange* range = XRecordAllocRange();
    if (range == 0) {
        fprintf(stderr, "unable to allocate XRecordRange\n");
        return;
    }

    // Receive KeyPress, KeyRelease, ButtonPress, ButtonRelease and MotionNotify events.
    memset(range, 0, sizeof(XRecordRange));
    range->device_events.first = KeyPress;
    range->device_events.last  = MotionNotify;

    // And create the XRECORD context.
    XRecordContext context = XRecordCreateContext(display, 0, &clients, 1, &range, 1);
    if (context == 0) {
        fprintf(stderr, "XRecordCreateContext failed\n");
        return;
    }
    XFree(range);

    XSync(display, True);

    Display* display_datalink = XOpenDisplay(0);
    if (display_datalink == 0) {
        fprintf(stderr, "unable to open second display\n");
        XCloseDisplay (display_datalink);
        return;
    }
    if (!XRecordEnableContext(display_datalink, context,  callback, (XPointer) this)) {
        fprintf(stderr, "XRecordEnableContext() failed\n");
        XCloseDisplay (display_datalink);
        return;
    }
    XCloseDisplay (display_datalink);

}

void XEventMonitorPrivate::callback(XPointer ptr, XRecordInterceptData* data)
{
    ((XEventMonitorPrivate *) ptr)->handleRecordEvent(data);
}

void XEventMonitorPrivate::handleRecordEvent(XRecordInterceptData* data)
{

    if (data->category == XRecordFromServer) {
        xEvent * event = (xEvent *)data->data;
        switch (event->u.u.type)
        {
        case ButtonPress:
            if (filterWheelEvent(event->u.u.detail)) {
                emitButtonSignal("buttonPress", event);
            }
            break;
        case MotionNotify:
            emitButtonSignal("buttonDrag", event);
           break;
        case ButtonRelease:
            if (filterWheelEvent(event->u.u.detail)) {
                emitButtonSignal("buttonRelease", event);
            }
            break;
        case KeyPress:
            updateModifier(event, true);
            emitKeySignal("keyPress", event);
            break;
        case KeyRelease:
            updateModifier(event, false);
            emitKeySignal("keyRelease", event);
            break;
        default:
            break;
        }
    }
    fflush(stdout);
    XRecordFreeData(data);
}

bool XEventMonitorPrivate::filterWheelEvent(int detail)
{
    return detail != WheelUp && detail != WheelDown && detail != WheelLeft && detail != WheelRight;
}

void XEventMonitorPrivate::updateModifier(xEvent *event, bool isAdd)
{
    Display *display = XOpenDisplay(NULL);
    KeySym keySym = XkbKeycodeToKeysym(display, event->u.u.detail, 0, 0);

    if(ModifiersVec.contains(keySym))
    {
        if(isAdd)
        {
            modifiers.insert(keySym);
        }
        else
        {
            modifiers.remove(keySym);
        }
    }

    XCloseDisplay(display);
}

XEventMonitor::XEventMonitor(QObject *parent)
    : QThread(parent),
      d_ptr(new XEventMonitorPrivate(this))
{
    Q_D(XEventMonitor);
}

XEventMonitor::~XEventMonitor()
{
    requestInterruption();
    quit();
    wait();
}

void XEventMonitor::run()
{
    if(!isInterruptionRequested())
    {
        d_ptr->run();
    }
}

bool checkCapsState()
{
    //?????????????????????
    Display *display = XOpenDisplay(NULL);
    bool capsState = false;
    if(display) {
        unsigned int n;
        XkbGetIndicatorState(display, XkbUseCoreKbd, &n);
        capsState = (n & 0x01) == 1;
    }
    XCloseDisplay (display);
    return capsState;
}
