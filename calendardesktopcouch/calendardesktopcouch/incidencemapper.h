#ifndef INCIDENCEMAPPER_H
#define INCIDENCEMAPPER_H
#include <kcal/incidence.h>
#include <kcal/person.h>
#include <kdatetime.h>
#include <QVariant>
#include <kcal/attachment.h>
class IncidenceMapper
{
public:
    IncidenceMapper();
    static QVariant incidenceToVariant(KCal::Incidence* incidence);
    static KCal::Incidence* variantToIncidence(const QVariant&);
private:
    static QVariant alarmToVariant(const KCal::Alarm&);
    static QMap<QString,QVariant> attendeeToVariant(const KCal::Attendee&);
    static KCal::Attendee variantToAttendee(const QMap<QString,QVariant>&);
    static KCal::Alarm variantToAlarm(QVariant);
    static QMap<QString,QVariant> durationToVariant(const KCal::Duration&);
    static KCal::Duration variantToDuration(const QMap<QString,QVariant>&);
    static QMap<QString,QVariant> personToVariant(const KCal::Person&);
    static KCal::Person variantToPerson(const QMap<QString,QVariant>&);
    static QVariant attachmentToVariant(const KCal::Attachment&);

};

#endif // INCIDENCEMAPPER_H
