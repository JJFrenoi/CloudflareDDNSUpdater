#include <iostream>
#include <string>
enum Type {
  A,
  AAAA,
  CNAME,
  HTTPS,
  TXT,
  SRV,
  LOC,
  MX,
  NS,
  CERT,
  DNSKEY,
  DS,
  NAPTR,
  SMIMEA,
  SSHFP,
  SVCB,
  TLSA,
  URI,
};
static inline Type getStringType(std::string *type) {
  if (*type == "A")
    return A;
  else if (*type == "AAAA")
    return AAAA;
  else if (*type == "CNAME")
    return CNAME;
  else if (*type == "HTTPS")
    return HTTPS;
  else if (*type == "TXT")
    return TXT;
  else if (*type == "SRV")
    return SRV;
  else if (*type == "LOC")
    return LOC;
  else if (*type == "MX")
    return MX;
  else if (*type == "NS")
    return NS;
  else if (*type == "CERT")
    return CERT;
  else if (*type == "DNSKEY")
    return DNSKEY;
  else if (*type == "DS")
    return DS;
  else if (*type == "NAPTR")
    return NAPTR;
  else if (*type == "SMIMEA")
    return SMIMEA;
  else if (*type == "SSHFP")
    return SSHFP;
  else if (*type == "SVCB")
    return SVCB;
  else if (*type == "TLSA")
    return TLSA;
  else if (*type == "URI")
    return URI;
  else
    return A;
}
static inline std::string getTypeString(Type *type) {
  switch (*type) {
  case A:
    return "A";
  case AAAA:
    return "AAAA";
  case CNAME:
    return "CNAME";
  case HTTPS:
    return "HTTPS";
  case TXT:
    return "TXT";
  case SRV:
    return "SRV";
  case LOC:
    return "LOC";
  case MX:
    return "MX";
  case NS:
    return "NS";
  case CERT:
    return "CERT";
  case DNSKEY:
    return "DNSKEY";
  case DS:
    return "DS";
  case NAPTR:
    return "NAPTR";
  case SMIMEA:
    return "SMIMEA";
  case SSHFP:
    return "SSHFP";
  case SVCB:
    return "SVCB";
  case TLSA:
    return "TLSA";
  case URI:
    return "URI";
  }
  return "A";
}