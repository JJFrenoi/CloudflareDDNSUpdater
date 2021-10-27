#include "HttpHeader.hpp"
HttpHeader::HttpHeader(std::string key, std::string value) {
  this->key = key;
  this->value = value;
}

HttpHeader::~HttpHeader() {}
const std::string HttpHeader::toString() { return key + ": " + value; }