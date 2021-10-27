#ifndef DEF_HTTPHEADER
#define DEF_HTTPHEADER
#include <iostream>
#include <string>
#include <vector>
class HttpHeader {
private:
  /* data */
  std::string key;
  std::string value;

public:
  HttpHeader(std::string key, std::string value);
  ~HttpHeader();
  const std::string toString();
  static inline std::vector<HttpHeader *> getConstHeaders(std::string *email,
                                                          std::string *apikey) {
    return {new HttpHeader("X-Auth-Email", *email),
            new HttpHeader("X-Auth-Key", *apikey),
            new HttpHeader("Content-Type", "application/json"),
            new HttpHeader("Accept", "application/json")};
  }
};
#endif
