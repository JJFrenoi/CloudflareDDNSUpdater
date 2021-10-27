#ifndef DEF_DNSRECORD
#define DEF_DNSRECORD
#include "Type.hpp"
#include "json.hpp"
using namespace std;
class DNSRecord {
private:
  void init(string *id = nullptr, Type *type = nullptr, string *name = nullptr,
            string *content = nullptr, bool *proxied = nullptr,
            int *ttl = nullptr);

public:
  string id;
  Type type;
  string name;
  string content;
  bool proxied;
  int ttl;
  DNSRecord(nlohmann::json *json);
  DNSRecord(string *id = nullptr, Type *type = nullptr, string *name = nullptr,
            string *content = nullptr, bool *proxied = nullptr,
            int *ttl = nullptr);
  ~DNSRecord();
  void print();
  nlohmann::json toJson();
};
#endif