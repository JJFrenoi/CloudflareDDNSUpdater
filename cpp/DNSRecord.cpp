#include "DNSRecord.hpp"
#include "json.hpp"
#include <iostream>
#include <string>

DNSRecord::DNSRecord(nlohmann::json *json) {
  try {
    auto result = *json;
    string id = result["id"];
    string strType = result["type"];
    Type type = getStringType(&strType);
    string name = result["name"];
    string content = result["content"];
    bool proxied = result["proxied"];
    int ttl = result["ttl"];
    init(&id, &type, &name, &content, &proxied, &ttl);
  } catch (nlohmann::json::type_error &e) {
    cout << "DNSRecordError => Not a DNS record object" << endl;
  } catch (nlohmann::detail::out_of_range &e) {
    cout << "DNSRecordError => Not a DNS record object" << endl;
  }
}
DNSRecord::DNSRecord(string *id, Type *type, string *name, string *content,
                     bool *proxied, int *ttl) {
  init(id, type, name, content, proxied, ttl);
}

DNSRecord::~DNSRecord() {}
void DNSRecord::print() {
  cout << "DNS record :\n"
       << "\t" << id << "\n"
       << "\t" << name << "\n"
       << "\t" << ttl << "\n"
       << "\t" << proxied << "\n"
       << "\t" << content << endl;
}
void DNSRecord::init(string *id, Type *type, string *name, string *content,
                     bool *proxied, int *ttl) {
  this->id = *id;
  this->type = *type;
  this->name = *name;
  this->content = *content;
  this->proxied = *proxied;
  this->ttl = *ttl;
}
nlohmann::json DNSRecord::toJson() {
  string strType = getTypeString(&type);
  nlohmann::json j = {
      {"id", id},           {"name", name},       {"type", strType},
      {"content", content}, {"proxied", proxied}, {"ttl", ttl},
  };
  return j;
}