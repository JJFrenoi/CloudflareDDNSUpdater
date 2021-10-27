#include "Http.hpp"
#include <iostream>

Http::Http(bool verbose) {
  this->verbose = verbose;
  if (this->verbose) {
    cout << "Http service started" << endl;
    cout << "Using curl " << curl_version() << endl;
  }
}
Http::~Http() {
  cleanCurl();
}
Response *Http::getRequest(const char *url) {
  initCurl();
  setDefaultConfig(url);
  CURLcode res;
  string response_string;
  string header_string;
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
  curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header_string);
  res = curl_easy_perform(curl);
  handleError(res);
  auto infos = getInfos();
  cleanCurl();
  return new Response(infos.url, infos.response_code, infos.elapsed,
                      response_string, header_string, res, nullptr);
}
Response *Http::getUserInfo(string *email, string *apikey) {
  initCurl();
  string url = Urls::cloudflareBaseURL + Urls::user;
  setDefaultConfig(url.c_str());
  CURLcode res;
  string response_string;
  string header_string;
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
  curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header_string);
  vector<HttpHeader *> headers = HttpHeader::getConstHeaders(email, apikey);
  setHeaders(headers);
  res = curl_easy_perform(curl);
  auto infos = getInfos();
  auto json = toJson(response_string);
  handleError(res);
  cleanHeaders(headers);
  cleanCurl();
  return new Response(infos.url, infos.response_code, infos.elapsed,
                      response_string, header_string, res, &json);
}
void Http::cleanCurl() {
  if (curl) {
    curl_easy_cleanup(curl);
    curl_global_cleanup();
    curl = nullptr;
  }
}
void Http::initCurl() {
  curl_global_init(CURL_GLOBAL_DEFAULT);
  curl = curl_easy_init();
  if (!curl)
    throw("curl is null");
}
void Http::setDefaultConfig(const char *url) {
  curl_easy_setopt(curl, CURLOPT_URL, url);
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
  curl_easy_setopt(curl, CURLOPT_USERAGENT, "curl/7.42.0");
  curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 50L);
  curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);
  if (verbose)
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
}
void Http::handleError(CURLcode res) {
  if (res != CURLE_OK) {
    fprintf(stderr, "curl_easy_perform() failed: %s\n",
            curl_easy_strerror(res));
    throw curl_easy_strerror(res);
  }
}
Infos Http::getInfos() {
  Infos infos;
  curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &infos.response_code);
  curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &infos.elapsed);
  curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &infos.url);
  return infos;
}
void Http::setHeaders(vector<HttpHeader *> &headers) {
  struct curl_slist *list = NULL;
  for (auto &&i : headers) {
    list = curl_slist_append(list, i->toString().c_str());
  }
  curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);
}

void Http::setAuth(string &token) {
  curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_BEARER);
  curl_easy_setopt(curl, CURLOPT_XOAUTH2_BEARER, token.c_str());
}
json Http::toJson(string &response_string) {
  return json::parse(response_string);
}
Response *Http::getDNSRecords(string *email, string *apikey, string *zoneId,
                              Type *type, string *name) {
  initCurl();
  string url = Urls::cloudflareBaseURL + Urls::zoneUri + "/" + *zoneId + "/" +
               Urls::dnsRecordUri;
  if (type || name)
    url.append("?");
  if (type)
    url.append("type=" + getTypeString(type) + "&");
  if (name)
    url.append("name=" + *name + "&");
  setDefaultConfig(url.c_str());
  CURLcode res;
  string response_string;
  string header_string;
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
  curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header_string);
  vector<HttpHeader *> headers = HttpHeader::getConstHeaders(email, apikey);
  setHeaders(headers);
  res = curl_easy_perform(curl);
  auto infos = getInfos();
  auto json = toJson(response_string);
  handleError(res);
  cleanHeaders(headers);
  cleanCurl();
  return new Response(infos.url, infos.response_code, infos.elapsed,
                      response_string, header_string, res, &json);
}
void Http::cleanHeaders(vector<HttpHeader *> &headers) {
  for (auto &&header : headers) {
    delete header;
  }
}

Response *Http::updateDNSRecord(DNSRecord &newDNSRecord, string *email,
                                string *apikey, string *zoneId) {
  initCurl();
  string url = Urls::cloudflareBaseURL + Urls::zoneUri + "/" + *zoneId + "/" +
               Urls::dnsRecordUri + "/" + newDNSRecord.id;
  setDefaultConfig(url.c_str());
  CURLcode res;
  string response_string;
  string header_string;
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
  curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header_string);
  vector<HttpHeader *> headers = HttpHeader::getConstHeaders(email, apikey);
  setHeaders(headers);
  string stringified = newDNSRecord.toJson().dump();
  curl_easy_setopt(curl, CURLOPT_POSTFIELDS, stringified.c_str());
  curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
  curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, -1L);
  res = curl_easy_perform(curl);
  auto infos = getInfos();
  auto json = toJson(response_string);
  handleError(res);
  cleanHeaders(headers);
  cleanCurl();
  return new Response(infos.url, infos.response_code, infos.elapsed,
                      response_string, header_string, res, &json);
}
Response *Http::getPublicIpAddress() {
  return getRequest(Urls::googleIp.c_str());
}