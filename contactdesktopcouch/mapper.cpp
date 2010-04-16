#include "mapper.h"
//#include <klineeditdialog.h>
#include <kinputdialog.h>

QVariantList Mapper::convertPhoneNumbers(KABC::PhoneNumber::List phones)
{
    QVariantList vlist;
    for (int i=0;i<phones.length();i++)
    {
        KABC::PhoneNumber pn = phones.at(i);
        if (!pn.isEmpty())
        {
          QMap<QString,QVariant> phone;
          if (!pn.id().isEmpty()) phone.insert("id",QVariant(pn.id()));
          if (!pn.number().isEmpty()) phone.insert("number",QVariant(pn.number()));
          phone.insert("type",QVariant(pn.type()));
// resolve        //if (!pnumber.id().isEmpty()) phone.insert("is_empty",QVariant(pnumber.isEmpty()));
// resolve        //phone.insert("id",QVariant(pnumber.typeList()));
          if (!phone.isEmpty()) vlist.append(phone);
        }
    }
    return vlist;
}
QVariantList Mapper::convertAddresses(KABC::Address::List adresses)
{
    QVariantList vlist;
    for (int i=0;i<adresses.length();i++)
    {
        QMap<QString,QVariant> address = Mapper::addressToQMap(adresses.at(i));
        vlist.append(address);
    }
    return vlist;
}

QMap<QString,QVariant> Mapper::addressToQMap(  KABC::Address addr )
{
    QMap<QString,QVariant> qAddr;
    if (!addr.country().isEmpty())    qAddr.insert("country",QVariant(addr.country()));
    //if (!addr.countryToISO().isE)   qAddr.insert("country_to_iso",QVariant(addr.countryToISO(addr.country())));
    if (!addr.extended().isEmpty())   qAddr.insert("extended",QVariant(addr.extended()));
    if (!addr.id().isEmpty())         qAddr.insert("id",QVariant(addr.id()));
    if (!addr.locality().isEmpty())   qAddr.insert("locality",QVariant(addr.locality()));
    if (!addr.postalCode().isEmpty()) qAddr.insert("postal_code",QVariant(addr.postalCode()));
    if (!addr.postOfficeBox().isEmpty())    qAddr.insert("postal_officebox",QVariant(addr.postOfficeBox()));
    if (!addr.region().isEmpty())           qAddr.insert("region",QVariant(addr.region()));
    if (!addr.street().isEmpty())           qAddr.insert("street",QVariant(addr.street()));
                                            qAddr.insert("type",QVariant(addr.type()));
    return qAddr;
}

QVariant Mapper::addresseeToVariant( const KABC::Addressee& a )
{
    QMap<QString,QVariant> vMap;
    //vMap.insert( "_id",QVariant(QString(/*a.uid()*/"sadd")));
    //vMap.insert( "_rev", QVariant(QString(/*a.custom( "akonadi-desktop-couch-resource", "_rev" )*/"2")) );
    if (!a.givenName().isEmpty()) vMap.insert("first_name",QVariant(QString(a.givenName())));
    if (!a.familyName().isEmpty()) vMap.insert("last_name",QVariant(QString(a.familyName())));
    if (!a.nickName().isEmpty()) vMap.insert("nick_name",QVariant(QString(a.nickName())));
    if (!a.emails().isEmpty())
    {
        QVariantList list;
        for (int i =0;i<a.emails().length();i++) list.append(QVariant(a.emails().at(i)));
        vMap.insert("email_addresses",list);
    }
    if (!a.birthday().isNull()) vMap.insert("birth_date",QVariant(a.birthday()));
    if (!a.organization().isEmpty()) vMap.insert("organization",QVariant(a.organization()));
    if (!a.additionalName().isEmpty()) vMap.insert("additional_name",QVariant(a.additionalName()));
    if (!a.assembledName().isEmpty()) vMap.insert("assembled_name",QVariant(a.assembledName()));
    if (!a.categories().isEmpty())
    {
        QVariantList list;
        for (int i =0;i<a.categories().length();i++) list.append(QVariant(a.categories().at(i)));
        vMap.insert("categories",list);
    }
    vMap.insert("changed",QVariant(a.changed()));
    //vMap.insert("custom",QVariant(a.custom()));
    if (!a.customs().isEmpty())
    {
        QVariantList list;
        for (int i =0;i<a.customs().length();i++) list.append(QVariant(a.customs().at(i)));
        vMap.insert("customs",list);
    }
    if (!a.department().isEmpty()) vMap.insert("department",QVariant(a.department()));
    if (!a.mailer().isEmpty())    vMap.insert("mailer",QVariant(a.mailer()));
    if (!a.mimeType().isEmpty())  vMap.insert("mime_type",QVariant(a.mimeType()));
    if (!a.name().isEmpty())      vMap.insert("name",QVariant(a.name()));
    if (!a.note().isEmpty())      vMap.insert("note",QVariant(a.note()));
    if (!a.prefix().isEmpty())    vMap.insert("prefix",QVariant(a.prefix()));
    if (!a.productId().isEmpty()) vMap.insert("product_id",QVariant(a.productId()));
    if (!a.realName().isEmpty())  vMap.insert("real_name",QVariant(a.realName()));
    if (!a.role().isEmpty())      vMap.insert("role",QVariant(a.role()));
    if (!a.revision().isNull())   vMap.insert("revision",QVariant(a.revision()));
    if (!a.suffix().isEmpty())    vMap.insert("suffix",QVariant(a.suffix()));
    if (!a.title().isEmpty()) vMap.insert("tittle",QVariant(a.title()));
   // vMap.insert("url",QVariant(a.url()));
    if (!a.preferredEmail().isEmpty())  vMap.insert("preffered_email",QVariant(a.preferredEmail()));
    //vMap.insert("time_zone",QVariant(a.timeZone()));

    if (!a.addresses().isEmpty())
    { 
        KABC::Address::List alist =  a.addresses();
        QVariantList qvlist = Mapper::convertAddresses(alist);
        vMap.insert("addresses",qvlist);
    }
/*
    alist =  a.addresses(KABC::Address::Dom);
    qvlist = Mapper::convertAddresses(alist);
    vMap.insert("addresses_dom",QVariant(qvlist));

    alist =  a.addresses(KABC::Address::Intl);
    qvlist = Mapper::convertAddresses(alist);
    vMap.insert("addresses_intl",QVariant(qvlist));

    alist =  a.addresses(KABC::Address::Parcel);
    qvlist = Mapper::convertAddresses(alist);
    vMap.insert("addresses_parcel",QVariant(qvlist));

    alist =  a.addresses(KABC::Address::Postal);
    qvlist = Mapper::convertAddresses(alist);
    vMap.insert("addresses_postal",QVariant(qvlist));

    alist =  a.addresses(KABC::Address::Pref);
    qvlist = Mapper::convertAddresses(alist);
    vMap.insert("addresses_pref",QVariant(qvlist));

    alist =  a.addresses(KABC::Address::Work);
    qvlist = Mapper::convertAddresses(alist);
    vMap.insert("addresses_work",QVariant(qvlist));
*/
    //--a.photo();
    //--a.resource();
    //--a.sound();
    //--a.timeZone();
    //--a.addresses
    if (a.secrecy().isValid())
    {
        KABC::Secrecy  sec =  a.secrecy();
        QMap<QString,QVariant> vSec;
        vSec.insert("is_valid",QVariant(sec.isValid()));
        vSec.insert("type",QVariant(sec.type()));
        vMap.insert("secrecy",QVariant(vSec));
    }
    if (!a.phoneNumbers().isEmpty())
    {
      QVariantList vlist;
      KABC::PhoneNumber::List phones = a.phoneNumbers();
      vlist = Mapper::convertPhoneNumbers(phones);
      vMap.insert("phone_numbers",vlist);
    }
/*
    phones = a.phoneNumbers(KABC::PhoneNumber::Car);
    vlist = Mapper::convertPhoneNumbers(phones);
    vMap.insert("phone_numbers_car",QVariant(vlist));

    phones = a.phoneNumbers(KABC::PhoneNumber::Cell);
    vlist = Mapper::convertPhoneNumbers(phones);
    vMap.insert("phone_numbers_cell",QVariant(vlist));

    phones = a.phoneNumbers(KABC::PhoneNumber::Fax);
    vlist = Mapper::convertPhoneNumbers(phones);
    vMap.insert("phone_numbers_fax",QVariant(vlist));

    phones = a.phoneNumbers(KABC::PhoneNumber::Isdn);
    vlist = Mapper::convertPhoneNumbers(phones);
    vMap.insert("phone_numbers_isdn",QVariant(vlist));

    phones = a.phoneNumbers(KABC::PhoneNumber::Bbs);
    vlist = Mapper::convertPhoneNumbers(phones);
    vMap.insert("phone_numbers_bbs",QVariant(vlist));

    phones = a.phoneNumbers(KABC::PhoneNumber::Modem);
    vlist = Mapper::convertPhoneNumbers(phones);
    vMap.insert("phone_numbers_modem",QVariant(vlist));

    phones = a.phoneNumbers(KABC::PhoneNumber::Msg);
    vlist = Mapper::convertPhoneNumbers(phones);
    vMap.insert("phone_numbers_msg",QVariant(vlist));

    phones = a.phoneNumbers(KABC::PhoneNumber::Pager);
    vlist = Mapper::convertPhoneNumbers(phones);
    vMap.insert("phone_numbers_pager",QVariant(vlist));

    phones = a.phoneNumbers(KABC::PhoneNumber::Pcs);
    vlist = Mapper::convertPhoneNumbers(phones);
    vMap.insert("phone_numbers_pcs",QVariant(vlist));

    phones = a.phoneNumbers(KABC::PhoneNumber::Pref);
    vlist = Mapper::convertPhoneNumbers(phones);
    vMap.insert("phone_numbers_pref",QVariant(vlist));

    phones = a.phoneNumbers(KABC::PhoneNumber::Video);
    vlist = Mapper::convertPhoneNumbers(phones);
    vMap.insert("phone_numbers_video",QVariant(vlist));

    phones = a.phoneNumbers(KABC::PhoneNumber::Work);
    vlist = Mapper::convertPhoneNumbers(phones);
    vMap.insert("phone_numbers_work",QVariant(vlist));

    phones = a.phoneNumbers(KABC::PhoneNumber::Voice);
    vlist = Mapper::convertPhoneNumbers(phones);
    vMap.insert("phone_numbers_voice",QVariant(vlist));*/

    // FIXME handle known fields
    // FIXME restore unknown fields from customs
    return QVariant(vMap);
}

KABC::Addressee Mapper::variantToAddressee( const QVariant& v )
{
  KABC::Addressee a;
  QVariantMap vMap = v.toMap();
  if (vMap.contains("_id")) a.setUid( vMap["_id"].toString() );
  if (vMap.contains("first_name")) a.setGivenName( vMap["first_name"].toString() );
  if (vMap.contains("last_name")) a.setFamilyName( vMap["last_name"].toString() );
  if (vMap.contains("birth_date")) a.setBirthday( QDateTime::fromString( vMap["birth_date"].toString() ) );
  if (vMap.contains("nick_name")) a.setNickName( vMap["nick_name"].toString() );
  if (vMap.contains("organization")) a.setOrganization( vMap["organization"].toString() );
  if (vMap.contains("additional_name")) a.setAdditionalName( vMap["additional_name"].toString() );

  if (vMap.contains("department")) a.setDepartment( vMap["department"].toString() );
  if (vMap.contains("name")) a.setName( vMap["name"].toString() );
  if (vMap.contains("prefix")) a.setPrefix( vMap["prefix"].toString() );
  if (vMap.contains("mailer")) a.setMailer( vMap["mailer"].toString());
  if (vMap.contains("product_id")) a.setProductId( vMap["product_id"].toString() );
  if (vMap.contains("note")) a.setNote( vMap["note"].toString() );
  if (vMap.contains("revision")) a.setRevision( QDateTime().fromString(vMap["revision"].toString()) );
  if (vMap.contains("role")) a.setRole( vMap["role"].toString() );
 //a.setSecrecy( vMap["secrecy"].toString() );
  if (vMap.contains("suffix")) a.setSuffix( vMap["suffix"].toString() );
  if (vMap.contains("tittle")) a.setTitle( vMap["tittle"].toString() );
  //a.setTimeZone();
  //a.setUrl( vMap["prefix"].toString() );
  //KUrl
  //a.setChanged(vMap["changed"].toString() );

  // extract email addresses
  if (vMap.contains("email_addresses"))
  {
    const QVariantList emails = vMap["email_addresses"].toList();
    Q_FOREACH( QVariant email, emails )
    {
        if ( !(email.toString()).isEmpty() ) a.insertEmail( email.toString() );
    }
  }
  // extract categories
  if (vMap.contains("categories"))
  {
    const QVariantList categories = vMap["categories"].toList();
    Q_FOREACH( QVariant category, categories )
    {
        if ( !(category.toString()).isEmpty() ) a.insertCategory(category.toString());
    }
  }
  // TODO

  // extract ccustoms
  /*if (vMap.contains("customs"))
  {
    const QVariantList customs = vMap["customs"].toList();
    Q_FOREACH( QVariant custom, customs )
    {
        if ( !(custom.toString()).isEmpty() ) a.insertCustom(custom.toString());
    }
  }*/
  //extract phone numbers
  if (vMap.contains("phone_numbers"))
  {

    const QVariantList numbers = vMap["phone_numbers"].toList();
    Q_FOREACH( QVariant number, numbers )
    {
        QVariantMap numbermap = number.toMap();
        const QString numberstr;
        if (numbermap.contains("number")) const QString numberstr = numbermap["number"].toString();
        if ( !numberstr.isEmpty() )
        {
            KABC::PhoneNumber phonenumber;
            phonenumber.setNumber(numberstr);
            if (numbermap.contains("id")) phonenumber.setId(numbermap["id"].toString());
            if (numbermap.contains("type"))
            {
                QString qstype = numbermap.key("type");
                phonenumber.setType((KABC::PhoneNumber::TypeFlag)(qstype.toInt()));
            }
            //phonenumber.setType(numbermap["type"].toString());
            a.insertPhoneNumber( phonenumber );
        }
    }
  }

  //extract addresses
  if (vMap.contains("addresses"))
  {
      const QVariantList addresses = vMap["addresses"].toList();
      Q_FOREACH( QVariant address, addresses )
      {
         QVariantMap addressmap = address.toMap();
         KABC::Address address;
         if (addressmap.contains("id")) address.setId(addressmap["id"].toString());
         if (addressmap.contains("country")) address.setCountry(addressmap["country"].toString());
         if (addressmap.contains("extended")) address.setExtended(addressmap["extended"].toString());
         if (addressmap.contains("locality")) address.setLocality(addressmap["locality"].toString());
         if (addressmap.contains("postal_code")) address.setPostalCode(addressmap["postal_code"].toString());
         if (addressmap.contains("postal_officebox")) address.setPostOfficeBox(addressmap["postal_officebox"].toString());
         if (addressmap.contains("region")) address.setRegion(addressmap["region"].toString());
         if (addressmap.contains("street")) address.setStreet(addressmap["street"].toString());
         if (addressmap.contains("type"))
         {
             QString qstype = addressmap.key("type");
             address.setType((KABC::Address::TypeFlag)(qstype.toInt()));
         }
         a.insertAddress( address );
      }
  }

  if (vMap.contains("secrecy"))
  {

      QVariantMap vSec = (vMap["secrecy"]).toMap();
      KABC::Secrecy sec;
      if (vSec.contains("is_valid"))
      {

      }
      if (vSec.contains("type"))
      {
          QString qstype = vSec.key("type");
          sec.setType((KABC::Secrecy::Type)(qstype.toInt()));
      }
      a.setSecrecy(sec);
  }


  a.insertCustom( "akonadi-desktop-couch-resource", "_rev", vMap["_rev"].toString() );

  // FIXME enter all other fields as custom headers as well

  return a;
}
