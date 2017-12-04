#ifndef INTERFACEADAPTOR_H
#define INTERFACEADAPTOR_H

#include <QDBusAbstractAdaptor>


class InterfaceAdaptor : public QDBusAbstractAdaptor
{
    Q_OBJECT

    Q_CLASSINFO("D-Bus Interface", "com.deepin.Download")
    Q_CLASSINFO("D-Bus Introspection", ""
"  <interface name=\"com.deepin.Download\">\n"
"    <method name=\"RaiseWindow\"/>\n"
"  </interface>\n"
        "")
public:
    InterfaceAdaptor(QObject *parent);
    virtual ~InterfaceAdaptor();

public:

public Q_SLOTS:
    void ShowDownWindow(  QString fileURL );

Q_SIGNALS:

};

#endif // INTERFACEADAPTOR_H
