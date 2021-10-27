#ifndef DEF_HTTP
#define DEF_HTTP
#include "HttpHeader.hpp"
#include "Infos.hpp"
#include "Response.hpp"
#include "Urls.hpp"
#include <curl/curl.h>
#include <vector>
using namespace std;
using json = nlohmann::json;
class Http {
public:
  Http(const bool verbose);
  ~Http();
  Response *getPublicIpAddress();
  Response *updateDNSRecord(DNSRecord &newDNSRecord, string *email,
                            string *apikey, string *zoneId);
  Response *getRequest(const char *url);
  Response *getUserInfo(string *email, string *apikey);
  Response *getDNSRecords(string *email, string *apikey, string *zoneId,
                          Type *type = nullptr, string *name = nullptr);
  static int writeFunction(char *ptr, size_t size, size_t nmemb,
                           string *writerData) {
    if (writerData == NULL)
      return 0;

    writerData->append(ptr, size * nmemb);

    return size * nmemb;
  }

private:
  void cleanHeaders(vector<HttpHeader *> &headers);
  void setHeaders(vector<HttpHeader *> &headers);
  Infos getInfos();
  void handleError(CURLcode res);
  void setDefaultConfig(const char *url);
  void initCurl();
  void cleanCurl();
  void setAuth(string &token);
  nlohmann::json toJson(string &response_string);
  CURL *curl;
  bool verbose = false;
};
#endif