#ifndef DEF_CONF
#define DEF_CONF
#include "json.hpp"
#include <fstream>
using namespace std;
using json = nlohmann::json;
namespace conf {
inline struct Config {
  bool safeStop = true;
  unsigned int updateTime = 1;
} config;
inline void fromJson(const json &j) {
  try {
    config.safeStop = j["safe_stop"];
    config.updateTime = j["update_time"];
  } catch (json::type_error &e) {
    throw "Config: Wrong configuration";
  } catch (nlohmann::detail::out_of_range &e) {
    throw "Config: Wrong configuration";
  }
}
inline void init() {
  ifstream i("resources/config.json");
  json j;
  i >> j;
  fromJson(j);
}
} // namespace conf
#endif