#ifndef MAPPER_H
#define MAPPER_H

#include <kabc/addressee.h>
#include <couchdb-qt.h>
#include <desktop_couch.h>
#include <kabc/phonenumber.h>
#include <kabc/secrecy.h>
class Mapper
{
public:
    Mapper();
    static QVariant addresseeToVariant( const KABC::Addressee& a );
    static KABC::Addressee variantToAddressee( const QVariant& v );
private:
    static QVariantList convertPhoneNumbers( const KABC::PhoneNumber::List phones );
    static QVariantList convertAddresses( const KABC::Address::List adresses );
    static QMap<QString,QVariant> addressToQMap( const KABC::Address address );
};

#endif // MAPPER_H
