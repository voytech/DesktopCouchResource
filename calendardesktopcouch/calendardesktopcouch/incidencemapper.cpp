#include "incidencemapper.h"
#include <kcal/alarm.h>
#include <kcal/duration.h>
#include <kurl.h>
#include <kcal/event.h>
#include <kcal/journal.h>
#include <kcal/todo.h>
IncidenceMapper::IncidenceMapper()
{
}
QVariant IncidenceMapper::incidenceToVariant(KCal::Incidence* incidence)
{
    QMap<QString,QVariant> incidenceMap;
    //inserting alarms
    const KCal::ListBase<KCal::Alarm> alarms = incidence->alarms();
    QMap<QString,QVariant> alarmsMap;
    for (int i = 0;i<alarms.size();i++)
    {
        const KCal::Alarm& alarm = *alarms.at(i);
        QVariant alarmV = alarmToVariant(alarm);
        alarmsMap.insert(QString().setNum(i,10),alarmV);
    }
    incidenceMap.insert("alarms",QVariant(alarmsMap));
    //inserting attachments
    const KCal::ListBase<KCal::Attachment>  attachments = incidence->attachments();
    QMap<QString,QVariant> attachmentsMap;
    for (int i = 0;i<attachments.size();i++)
    {
        const KCal::Attachment& attachment = *attachments.at(i);
        QVariant attachmentV = attachmentToVariant(attachment);
        attachmentsMap.insert(QString().setNum(i,10),attachmentV);
    }
    incidenceMap.insert("attachments",QVariant(attachmentsMap));
    //inseritng attendees
    const KCal::ListBase<KCal::Attendee> attendees = incidence->attendees();
    QMap<QString,QVariant> attendeesMap;
    for (int i = 0;i<attendees.size();i++)
    {
        const KCal::Attendee& attendee = *attendees.at(i);        
        QMap<QString,QVariant> attendeeM = attendeeToVariant(attendee);
        attendeesMap.insert(QString().setNum(i,10),QVariant(attendeeM));
    }
    incidenceMap.insert("attendees",attendeesMap);
    //inserting categories;
    QStringList categories = incidence->categories();
    QMap<QString,QVariant> categoriesMap;
    for (int i=0;i<categories.size();i++)
    {

        QString category = categories.at(i);        
        categoriesMap.insert(QString().setNum(i,10),QVariant(category));
    }
    incidenceMap.insert("categories",QVariant(categoriesMap));
    QStringList comments = incidence->comments();
    QMap<QString,QVariant> commentsMap;
    for (int i=0;i<comments.size();i++)
    {
        QString comment = comments.at(i);
        commentsMap.insert(QString().setNum(i,10),QVariant(comment));
    }
    incidenceMap.insert("comments",QVariant(commentsMap));
    QString description = incidence->description();
    incidenceMap.insert("description",QVariant(description));

    incidenceMap.insert("descriptionIsRich",QVariant(incidence->descriptionIsRich()));
    incidenceMap.insert("dtEnd",QVariant(incidence->dtEnd().toString()));
    incidenceMap.insert("dtStart",QVariant(incidence->dtStart().toString()));

    //incidenceMap.insert("dtStartDateStr",QVariant(incidence->dtStartDateStr()));
    //incidenceMap.insert("dtStartStr",QVariant(incidence->dtStartStr()));
    //incidenceMap.insert("dtStartTimeStr",QVariant(incidence->dtStartTimeStr()));
    incidenceMap.insert("type",QVariant(incidence->type()));
    incidenceMap.insert("allDay",QVariant(incidence->allDay()));
    incidenceMap.insert("duration",durationToVariant(incidence->duration()));
    incidenceMap.insert("hasDuration",QVariant(incidence->hasDuration()));
    incidenceMap.insert("hasGeo",QVariant(incidence->hasGeo()));
    incidenceMap.insert("geoLatitude",QVariant(incidence->geoLatitude()));
    incidenceMap.insert("geoLongitude",QVariant(incidence->geoLongitude()));
    incidenceMap.insert("isReadOnly",QVariant(incidence->isReadOnly()));
    incidenceMap.insert("lastModified",QVariant(incidence->lastModified().toString()));
    incidenceMap.insert("location",QVariant(incidence->location()));
    incidenceMap.insert("locationIsRich",QVariant(incidence->locationIsRich()));
    incidenceMap.insert("priority",QVariant(incidence->priority()));
    incidenceMap.insert("relatedToUid",QVariant(incidence->relatedToUid()));
    QStringList resources = incidence->resources();
    QMap<QString,QVariant> resourcesMap;
    for (int i=0;i<resources.size();i++)
    {
        QString resource = resources.at(i);
        commentsMap.insert(QString().setNum(i,10),QVariant(resource));
    }
    incidenceMap.insert("resources",QVariant(resourcesMap));
    incidenceMap.insert("revision",QVariant(incidence->revision()));
    incidenceMap.insert("richDescription",QVariant(incidence->richDescription()));
    incidenceMap.insert("richLocation",QVariant(incidence->richLocation()));
    incidenceMap.insert("richSummary",QVariant(incidence->richSummary()));
    incidenceMap.insert("schedulingID",QVariant(incidence->schedulingID()));
    incidenceMap.insert("secrecy",QVariant(incidence->secrecy()));
    //incidenceMap.insert("secrecyList",QVariant(incidence->secrecyList()));
    //incidenceMap.insert("secrecyName",QVariant(incidence->secrecyName(incidence->secrecy())));
    //incidenceMap.insert("secrecyStr",QVariant(incidence->secrecyStr()));
    incidenceMap.insert("status",QVariant(incidence->status()));
    //incidenceMap.insert("statusName",QVariant(incidence->statusName(incidence->status())));
    //incidenceMap.insert("statusStr",QVariant(incidence->statusStr()));
    incidenceMap.insert("summary",QVariant(incidence->summary()));
    incidenceMap.insert("summaryIsRich",QVariant(incidence->summaryIsRich()));
    incidenceMap.insert("uid",QVariant(incidence->uid()));

    QMap<QString,QVariant> personMap = personToVariant(incidence->organizer());
    incidenceMap.insert("organizer",QVariant(personMap));

    //incidenceMap.insert("relatedTo",QVariant(incidence->setRe))
    //incidenceMap.insert()

    /*incidence->dtStartStr();
    incidence->dtStartTimeStr();

    incidence->hasDuration();
    incidence->hasGeo();
    incidence->isReadOnly();
    incidence->lastModified();
    incidence->location();
    incidence->relatedTo(); //!!!!!!!!!!!!!!!!!!!
    incidence->organizer(); //DONE
    incidence->relations(); //!!!!!!!!!!!!!!!!!!!
    incidence->resources();
    incidence->priority();
    incidence->recurs();
    incidence->richSummary();
    incidence->secrecyList();
    incidence->secrecyName();
    incidence->startDateTimesForDate(); //!!!!!!!!!!!!!!!!!!!! TODO
    incidence->startDateTimesForDateTime(); //!!!!!!!!!!!!!!!!! TODO
    incidence->status();*/

    //KUrl url = incidence->uri(); //!!!!!!!!!!!!!!!!!!!!!! TODO
    //url.
    return QVariant(incidenceMap);
}
KCal::Incidence* IncidenceMapper::variantToIncidence(const QVariant& variant)
{
    KCal::Incidence* incidence = NULL;

    QMap<QString,QVariant> incidenceMap = variant.toMap();
    if (incidenceMap.contains("type"))
    {
        QByteArray type = incidenceMap.value("type").toByteArray();
        if (type == "Event") incidence = new KCal::Event();
        else
            if (type == "Journal") incidence = new KCal::Journal();
        else
            if (type == "ToDo") incidence = new KCal::Todo();
    }
    if (incidence != NULL)
    {
        if (incidenceMap.contains("attendees"))
        {
            QMap<QString,QVariant> attendees = incidenceMap.value("attendees").toMap();
            for (int i=0;i<attendees.size();i++)
            {

               QVariant attendeeMap = attendees.value(QString().setNum(i,10));
               KCal::Attendee attendee = variantToAttendee(attendeeMap.toMap());
               incidence->addAttendee(new KCal::Attendee(attendee),true);
            }
         }
        if (incidenceMap.contains("allDay")) incidence->setAllDay(incidenceMap.value("allDay").toBool());
        if (incidenceMap.contains("categories"))
        {
            QMap<QString,QVariant> categoriesMap = incidenceMap.value("categories").toMap();
            QStringList categories;
            for (int i = 0;i<categoriesMap.size();i++)
            {
                QVariant categoryMap = categoriesMap.value(QString().setNum(i,10));
                categories.append(categoryMap.toString());
            }
            incidence->setCategories(categories);
        }
        if (incidenceMap.contains("comments"))
        {
            QMap<QString,QVariant> commentsMap = incidenceMap.value("comments").toMap();
            for (int i =0;i<commentsMap.size();i++)
            {
                QVariant comment = commentsMap.value(QString().setNum(i,10));
                incidence->addComment(comment.toString());
            }
        }
        if (incidenceMap.contains("description")) incidence->setDescription(incidenceMap.value("description").toString());
        //if (incidenceMap.contains("descriptionIsRich")) incidence.setDsetDescription(incidenceMap.value("description").toString());
        //incidenceMap.insert("descriptionIsRich",QVariant(incidence->descriptionIsRich()));
        //if (incidenceMap.contains("dtEnd")) incidence.setDsetDescription(incidenceMap.value("description").toString());
        //incidenceMap.insert("dtEnd",QVariant(incidence->dtEnd().toString()));
        if (incidenceMap.contains("dtStart"))
        {
            KDateTime start = KDateTime::fromString(incidenceMap.value("dtStart").toString(),KDateTime::ISODate,NULL);
            incidence->setDtStart(start);
        }
        //incidenceMap.insert("dtStartDateStr",QVariant(incidence->dtStartDateStr()));
        //incidenceMap.insert("dtStartStr",QVariant(incidence->dtStartStr()));
        //incidenceMap.insert("dtStartTimeStr",QVariant(incidence->dtStartTimeStr()));
        if (incidenceMap.contains("duration"))
        {
            incidence->setDuration(variantToDuration(incidenceMap.value("duration").toMap()));
        }
        if (incidenceMap.contains("hasDuration")) incidence->setHasDuration(incidenceMap.value("hasDuration").toBool());
        if (incidenceMap.contains("hasGeo")) incidence->setHasGeo(incidenceMap.value("hasGeo").toBool());
        if (incidenceMap.contains("geoLatitude")) incidence->setGeoLatitude(incidenceMap.value("geoLatitude").toFloat());
        if (incidenceMap.contains("geoLongitude")) incidence->setGeoLongitude(incidenceMap.value("geoLongitude").toFloat());
        if (incidenceMap.contains("isReadOnly")) incidence->setReadOnly(incidenceMap.value("isReadOnly").toBool());
        //incidenceMap.insert("lastModified",QVariant(incidence->lastModified().toString()));
        if (incidenceMap.contains("lastModified"))
        {
             KDateTime start = KDateTime::fromString(incidenceMap.value("lastModified").toString(),KDateTime::ISODate,NULL);
             incidence->setLastModified(start);
        }
        if (incidenceMap.contains("location")) incidence->setLocation(incidenceMap.value("location").toString());
        //if (incidenceMap.contains("locationIsRich")) incidence.
        //incidenceMap.insert("locationIsRich",QVariant(incidence->locationIsRich()));
        if (incidenceMap.contains("priority")) incidence->setPriority(incidenceMap.value("priority").toInt());
        if (incidenceMap.contains("relatedToUid")) incidence->setRelatedToUid(incidenceMap.value("relatedToUid").toString());
        if (incidenceMap.contains("resources"))
        {
            QMap<QString,QVariant> resourcesMap = incidenceMap.value("resources").toMap();
            QStringList resourcesList;
            for (int i=0;i<resourcesMap.size();i++)
            {
                QVariant resource = resourcesMap.value(QString().setNum(i,10));
                resourcesList.append(resource.toString());

            }
            incidence->setResources(resourcesList);
        }
        if (incidenceMap.contains("revision")) incidence->setRevision(incidenceMap.value("revision").toInt());
        //if (incidenceMap.contains("richDescription")) incidence.set(incidenceMap.value("revision").toInt());
        //incidenceMap.insert("richDescription",QVariant(incidence->richDescription()));
        //incidenceMap.insert("richLocation",QVariant(incidence->richLocation()));
        //incidenceMap.insert("richSummary",QVariant(incidence->richSummary()));
        if (incidenceMap.contains("schedulingID")) incidence->setSchedulingID(incidenceMap.value("schedulingID").toString());
        if (incidenceMap.contains("secrecy")) incidence->setSecrecy((KCal::Incidence::Secrecy)incidenceMap.value("secrecy").toInt());
        //incidenceMap.insert("secrecyList",QVariant(incidence->secrecyList()));
        //incidenceMap.insert("secrecyName",QVariant(incidence->secrecyName(incidence->secrecy())));
        //incidenceMap.insert("secrecyStr",QVariant(incidence->secrecyStr()));
        if (incidenceMap.contains("status")) incidence->setStatus((KCal::Incidence::Status)incidenceMap.value("status").toInt());
        //incidenceMap.insert("statusName",QVariant(incidence->statusName(incidence->status())));
        //incidenceMap.insert("statusStr",QVariant(incidence->statusStr()));
        if (incidenceMap.contains("summary")) incidence->setSummary(incidenceMap.value("summary").toString());

        //incidenceMap.insert("summaryIsRich",QVariant(incidence->summaryIsRich()));
        if (incidenceMap.contains("uid")) incidence->setUid(incidenceMap.value("uid").toString());
        if (incidenceMap.contains("organizer"))
        {
            KCal::Person person = variantToPerson(incidenceMap.value("organizer").toMap());
            incidence->setOrganizer(person);
        }
     }
     return incidence;
}
QMap<QString,QVariant> IncidenceMapper::personToVariant(const KCal::Person& person)
{
    QMap<QString,QVariant> personMap;
    personMap.insert("email",QVariant(person.email()));
    personMap.insert("fullName",QVariant(person.fullName()));
    personMap.insert("name",QVariant(person.name()));
    return personMap;
}
KCal::Person IncidenceMapper::variantToPerson(const QMap<QString, QVariant> &personMap)
{
    KCal::Person person;
    if (personMap.contains("fullName")) person = KCal::Person(personMap.value("fullName").toString());
    if (personMap.contains("email")) person.setEmail(personMap.value("email").toString());
    if (personMap.contains("name")) person.setName(personMap.value("name").toString());
    return person;
}

QMap<QString,QVariant> IncidenceMapper::durationToVariant(const KCal::Duration& duration)
{
    QMap<QString,QVariant> durationMap;
    durationMap.insert("value",QVariant(duration.value()));
    durationMap.insert("type",QVariant(duration.type()));
    return durationMap;
}
KCal::Duration IncidenceMapper::variantToDuration(const QMap<QString,QVariant>& durationMap)
{
    //KCal::Duration duration;
    KCal::Duration::Type type;
    int value;
    if (durationMap.contains("value")) value = durationMap.value("value").toInt();
    if (durationMap.contains("type"))  type = (KCal::Duration::Type)durationMap.value("type").toInt();
    return KCal::Duration(value,type);
}

QMap<QString,QVariant> IncidenceMapper::attendeeToVariant(const KCal::Attendee& attendee)
{
    QMap<QString,QVariant> attendeeMap;
    //if (!attendee.isEmpty())
    //{
    attendeeMap.insert("fullName",QVariant(attendee.fullName()));
    attendeeMap.insert("name",QVariant(attendee.name()));
    //attendeeMap.insert("isEmpty",QVariant(attendee.isEmpty()));
    attendeeMap.insert("email",QVariant(attendee.email()));
    attendeeMap.insert("Role",QVariant(attendee.role()));
    attendeeMap.insert("status",QVariant(attendee.status()));
    attendeeMap.insert("statusName",QVariant(attendee.statusName(attendee.status())));
    attendeeMap.insert("roleName",QVariant(attendee.roleName(attendee.role())));
    attendeeMap.insert("roleStr",QVariant(attendee.roleStr()));
    attendeeMap.insert("RSVP",QVariant(attendee.RSVP()));
    attendeeMap.insert("delegator",QVariant(attendee.delegator()));
    attendeeMap.insert("uid",QVariant(attendee.uid()));
    attendeeMap.insert("delegate",QVariant(attendee.delegate()));
   // }
    return attendeeMap;
}
KCal::Attendee IncidenceMapper::variantToAttendee(const QMap<QString,QVariant>& attendeeMap)
{
    KCal::Attendee attendee(QString(),QString(),false,KCal::Attendee::Declined,KCal::Attendee::Chair,QString());
    if (attendeeMap.contains("name") &&
        attendeeMap.contains("Role") &&
        attendeeMap.contains("RSVP") &&
        attendeeMap.contains("email") &&
        attendeeMap.contains("status"))
    {
           QString  name = attendeeMap.value("name").toString();
           KCal::Attendee::Role role = (KCal::Attendee::Role)attendeeMap.value("Role").toInt();
           bool  rsvp = attendeeMap.value("RSVP").toBool();
           QString  uid = attendeeMap.value("uid").toString();
           QString email = attendeeMap.value("email").toString();
           KCal::Attendee::PartStat status = (KCal::Attendee::PartStat)attendeeMap.value("status").toInt();
           attendee = KCal::Attendee(name,email,rsvp,status,role,uid);
           if (attendeeMap.contains("delegate")) attendee.setDelegate(attendeeMap.value("delegate").toString());
           if (attendeeMap.contains("Delegator")) attendee.setDelegator(attendeeMap.value("Delegator").toString());
    }
    return attendee;
}

QVariant IncidenceMapper::alarmToVariant(const KCal::Alarm& alarm)
{
    QMap<QString,QVariant> alarmMap;
    alarmMap.insert("duration",durationToVariant(alarm.duration()));
    alarmMap.insert("audioFile",QVariant(alarm.audioFile()));
    alarmMap.insert("enabled",QVariant(alarm.enabled()));
    alarmMap.insert("endOffset",durationToVariant(alarm.endOffset()));
    alarmMap.insert("endTime",QVariant(alarm.endTime().toString()));
    alarmMap.insert("hasEndOffset",QVariant(alarm.hasEndOffset()));
    alarmMap.insert("hasStartOffset",QVariant(alarm.hasStartOffset()));
    alarmMap.insert("hasTime",QVariant(alarm.hasTime()));
    QList<KCal::Person> persons = alarm.mailAddresses();
    QMap<QString,QVariant> addressesMap;
    for (int i =0;i<persons.size();i++)
    {
        KCal::Person person = persons.at(i);
        QMap<QString,QVariant> personMap = personToVariant(person);
        addressesMap.insert(QString().setNum(i,10),QVariant(personMap));
    }
    alarmMap.insert("addressesMap",QVariant(addressesMap));
    QStringList attachmentsList = alarm.mailAttachments();
    QMap<QString,QVariant> attachmentMap;
    for (int i =0;i<attachmentsList.size();i++)
    {
        QString attachment = attachmentsList.at(i);
        attachmentMap.insert(QString().setNum(i,10),QVariant(attachment));
    }
    alarmMap.insert("mailAttachments",QVariant(attachmentMap));
    alarmMap.insert("mailSubject",QVariant(alarm.mailSubject()));
    alarmMap.insert("mailText",QVariant(alarm.mailText()));
    alarmMap.insert("programArguments",QVariant(alarm.programArguments()));
    alarmMap.insert("programFile",QVariant(alarm.programFile()));
    alarmMap.insert("snoozeTime",QVariant(durationToVariant(alarm.snoozeTime())));
    alarmMap.insert("startOffset",QVariant(durationToVariant(alarm.startOffset())));
    alarmMap.insert("text",QVariant(alarm.text()));
    alarmMap.insert("text",QVariant(alarm.text()));
    alarmMap.insert("time",QVariant(alarm.time().toString()));
    alarmMap.insert("type",QVariant(alarm.type()));
    return QVariant(alarmMap);
}

QVariant IncidenceMapper::attachmentToVariant(const KCal::Attachment& attachment)
{
    QMap<QString,QVariant> attachmentMap;
    attachmentMap.insert("data",QVariant(attachment.data()));
    attachmentMap.insert("decodedData",QVariant(attachment.decodedData()));
    attachmentMap.insert("isBinary",QVariant(attachment.isBinary()));
    attachmentMap.insert("isLocal",QVariant(attachment.isLocal()));
    attachmentMap.insert("isUri",QVariant(attachment.isUri()));
    attachmentMap.insert("label",QVariant(attachment.label()));
    attachmentMap.insert("mimeType",QVariant(attachment.mimeType()));
    attachmentMap.insert("size",QVariant((int)attachment.size()));
    attachmentMap.insert("uri",QVariant(attachment.uri()));
    return QVariant(attachmentMap);
}


