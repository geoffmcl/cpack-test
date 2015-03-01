
#include <QDir>
#include <QFile>

#include "xsettings.h"


XSettings::XSettings() :
    QSettings()
{
}

//============================================
//= This is a terrible hack to enable some "test things on pete's workstation.. apologies in advance"..
bool XSettings::DEV()
{
    return QFile::exists("/home/ffs/fgx-installer/DEV.txt");
}






//===============================================
//== Os
XSettings::OS XSettings::os()
{
    #ifdef Q_WS_X11
    return XSettings::OS_LINUX;
    #endif
    #ifdef Q_WS_WIN
    return XSettings::OS_WINDOWS;
    #endif
    #ifdef Q_WS_MACX
    return XSettings::OS_MAC;
    #endif
}
QString XSettings::osString()
{
    #ifdef Q_WS_X11
    return QString("Linux");
    #endif
    #ifdef Q_WS_WIN
    return QString("Windows");
    #endif
    #ifdef Q_WS_MACX
    return QString("Mac");
    #endif
}

//=========================================================
// Temp Path
QString XSettings::temp()
{
    return XSettings::temp("");
}
QString XSettings::temp(QString append_me)
{
    return QDir::tempPath().append(append_me);
}


//=========================================================
// Server Url
QString XSettings::_server_url()
{
    return XSettings::DEV() ? "http://localhost:8000" : "http://download.fgx.ch";

}

QString XSettings::server_url()
{
    return XSettings::_server_url();
}

QString XSettings::server_url(QString append_1)
{
    return XSettings::_server_url().append(append_1);
}

QString XSettings::server_url(QString append_1, QString append_2)
{
    return XSettings::_server_url().append(append_1).append(append_2);
}




