/*
 * This file was generated by qdbusxml2cpp version 0.7
 * Command line was: qdbusxml2cpp -m -a settingsadaptor -i settings.h -l Settings /media/storage/PROGRAMMING/MasterThesis/GitRepo/DesktopCouchResource/calendardesktopcouch/calendardesktopcouch/qtcreator-build/org.kde.Akonadi.calendardesktopcouch.Settings.xml
 *
 * qdbusxml2cpp is Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
 *
 * This is an auto-generated file.
 * Do not edit! All changes made to it will be lost.
 */

#include "settingsadaptor.h"
#include <QtCore/QMetaObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>

/*
 * Implementation of adaptor class SettingsAdaptor
 */

SettingsAdaptor::SettingsAdaptor(Settings *parent)
    : QDBusAbstractAdaptor(parent)
{
    // constructor
    setAutoRelaySignals(true);
}

SettingsAdaptor::~SettingsAdaptor()
{
    // destructor
}

bool SettingsAdaptor::readOnly()
{
    // handle method call org.kde.Akonadi.calendardesktopcouch.Settings.readOnly
    return parent()->readOnly();
}

void SettingsAdaptor::setReadOnly(bool in0)
{
    // handle method call org.kde.Akonadi.calendardesktopcouch.Settings.setReadOnly
    parent()->setReadOnly(in0);
}


#include "settingsadaptor.moc"