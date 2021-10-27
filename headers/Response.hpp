#ifndef DEF_RESPONSE
#define DEF_RESPONSE
#include "json.hpp"
#include "DNSRecord.hpp"
#include <curl/curl.h>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Response {
private:
  /* data */
  const char *url;
  long response_code;
  double elapsed;
  string response_string;
  string header_string;
  CURLcode res;
  nlohmann::json json;

public:
  Response(const char *url, long response_code, double elapsed,
           string response_string, string header_string, CURLcode res,
           nlohmann::json *json = nullptr);
  ~Response();
  string getResponseString() const;
  void printResponseString();
  void printResponseCode();
  void printResponseElapsed();
  void jsonPrettyPrint();
  nlohmann::json getElement(string element);
  string getElementAsString(string element);
  nlohmann::json getJson();
  vector<DNSRecord*> getDNSRecords();
};
#endif