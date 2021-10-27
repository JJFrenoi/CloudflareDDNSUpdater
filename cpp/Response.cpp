#include "Response.hpp"
#include "json.hpp"
#include <algorithm>
#include <string>
using json = nlohmann::json;

Response::Response(const char *url, long response_code, double elapsed,
                   string response_string, string header_string, CURLcode res,
                   nlohmann::json *json) {
  this->url = url;
  this->response_code = response_code;
  this->elapsed = elapsed;
  this->response_string = response_string;
  this->header_string = header_string;
  this->res = res;
  if (json)
    this->json = *json;
}
string Response::getResponseString() const {
  return response_string;
}
nlohmann::json Response::getJson() { return json; }
Response::~Response() {}
void Response::printResponseString() { cout << response_string << endl; }
nlohmann::json Response::getElement(string element) { return json[element]; }
std::string Response::getElementAsString(string element) {
  return getElement(element).dump();
}
void Response::printResponseCode() { cout << response_code << endl; }
void Response::printResponseElapsed() { cout << elapsed << endl; }
void Response::jsonPrettyPrint() {
  cout << "Pretty print :\n" << json.dump(4) << endl;
}
vector<DNSRecord *> Response::getDNSRecords() {
  vector<DNSRecord *> toReturn = {};
  try {
    nlohmann::json res = json["result"];
    if (res.is_array()) {
      vector<nlohmann::json> res2 = res;
      for (nlohmann::json r : res2) {
        toReturn.push_back(new DNSRecord(&r));
      }
    } else {
      toReturn.push_back(new DNSRecord(&res));
    }
  } catch (nlohmann::json::type_error &e) {
    cout << "DNSRecordError => Not a DNS record object" << endl;
  } catch (nlohmann::detail::out_of_range &e) {
    cout << "DNSRecordError => Not a DNS record object" << endl;
  }
  return toReturn;
}
