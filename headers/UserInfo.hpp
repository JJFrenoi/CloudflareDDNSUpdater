#ifndef DEF_USERINFO
#define DEF_USERINFO
#include "json.hpp"
#include <fstream>
#include <string>
using namespace std;
using json = nlohmann::json;
namespace ui {
inline struct UserInfo {
  string email;
  string authKey;
  string zone_identifier;
  string dns_name;
} userInfo;
inline void toJson(json &j) {
  j = json{{"email", userInfo.email},
           {"authKey", userInfo.authKey},
           {"zone_identifier", userInfo.zone_identifier},
           {"dns_name", userInfo.dns_name}};
}
inline void fromJson(const json &j) {
  try {
    userInfo.email = j["email"];
    userInfo.authKey = j["authKey"];
    userInfo.dns_name = j["dns_name"];
    userInfo.zone_identifier = j["zone_identifier"];
  } catch (json::type_error &e) {
    throw "UserInfo: Wrong configuration";
  } catch (nlohmann::detail::out_of_range &e) {
    throw "UserInfo: Wrong configuration";
  }
}
inline void isConfigSet() {
  if (userInfo.authKey.size() < 5)
    throw "UserInfo: authkey not set, go to userinfo.json";
  else if (userInfo.dns_name.size() < 1)
    throw "UserInfo: dns_name not set, go to userinfo.json";
  else if (userInfo.email.size() < 3)
    throw "UserInfo: email not set, go to userinfo.json";
  else if (userInfo.zone_identifier.size() < 5)
    throw "UserInfo: zone_identifier not set, go to userinfo.json";
}
inline void init() {
  ifstream i("resources/userinfo.json");
  json j;
  i >> j;
  fromJson(j);
  isConfigSet();
}
} // namespace ui
#endif