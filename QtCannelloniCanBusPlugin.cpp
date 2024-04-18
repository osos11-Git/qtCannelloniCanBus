#include "CannelloniCanBackend.h"

#include <QCanBusFactory>
#include <QObject>
#include <QStringList>
#include <limits>

class QtCannelloniCanBusPlugin : public QObject, public QCanBusFactory
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QCanBusFactory" FILE "plugin.json")
    Q_INTERFACES(QCanBusFactory)

public:
	
    QList<QCanBusDeviceInfo> availableDevices(QString *errorMessage) const override
    {
        Q_UNUSED(errorMessage);
        QList<QCanBusDeviceInfo> deviceList;
        
        return deviceList;
    }

    QCanBusDevice* createDevice(const QString& interfaceName,
                                QString* errorMessage) const override
    {
        static constexpr auto quint16max = std::numeric_limits<quint16>::max();

        auto tokens = interfaceName.split(QChar(','));
        if (tokens.size() < 2 || tokens.size() > 4)
        {
            if (errorMessage)
            {
                *errorMessage = "Invalid interface name format";
            }
            return nullptr;
        }
        qsizetype tokenIndex = 0;
        QHostAddress localAddr(QHostAddress::AnyIPv4);
        if (tokens.size() > 3 && !localAddr.setAddress(tokens[tokenIndex++]))
        {
            if (errorMessage)
            {
                *errorMessage = "Invalid local address format";
            }
            return nullptr;
        }
        bool ok;
        uint localPort = 0;
        if (tokens.size() > 2)
        {
            localPort = tokens[tokenIndex++].toUInt(&ok);
            if (!ok || localPort > quint16max)
            {
                if (errorMessage)
                {
                    *errorMessage = "Invalid local port format";
                }
                return nullptr;
            }
        }
        QHostAddress remoteAddr(tokens[tokenIndex++]);
        if (remoteAddr.isNull())
        {
            if (errorMessage)
            {
                *errorMessage = "Invalid remote address format";
            }
            return nullptr;
        }
        auto remotePort = tokens[tokenIndex++].toUInt(&ok);
        if (!ok || remotePort > quint16max)
        {
            if (errorMessage)
            {
                *errorMessage = "Invalid remote port format";
            }
            return nullptr;
        }
        return new CannelloniCanBackend(localAddr, localPort, remoteAddr, remotePort);
    }
};

#include "QtCannelloniCanBusPlugin.moc"
