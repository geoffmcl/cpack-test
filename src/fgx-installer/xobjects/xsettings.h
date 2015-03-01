#ifndef XSETTINGS_H
#define XSETTINGS_H

#include <QSettings>

class XSettings : public QSettings
{
    Q_OBJECT
public:
    //explicit XSettings(QObject *parent = 0);
    XSettings();

    enum OS{
        OS_LINUX,
        OS_WINDOWS,
        OS_MAC
    };

    static XSettings::OS os();
    static QString osString();

    static QString temp();
    static QString temp(QString append);

    static QString _server_url();
    static QString server_url();
    static QString server_url(QString append_1);
    static QString server_url(QString append_1, QString append_2);

    static bool DEV();

    static XSettings& getInstance()
            {
                // The only instance
                // Guaranteed to be lazy initialized
                // Guaranteed that it will be destroyed correctly
                static XSettings instance;
                return instance;
            }

signals:

public slots:

};

#endif // XSETTINGS_H
