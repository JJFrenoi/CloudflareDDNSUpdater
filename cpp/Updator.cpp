#include "Updator.hpp"
#include <cstdlib>
#include <future>
#include <iostream>

bool Updator::requireUpdate() {
  cout << "Checking for update:" << endl;
  asyncLaunch();
  dnsIp = publicIpAddress.get();
  auto content = dnsContent.get();
  cout << "\tPublic Ip is: " << dnsIp << "\n\tDns content is: " << content
       << endl;
  return dnsIp != content;
}
Updator::Updator(atomic<bool> &isProgramRunning) {
  cout << "**Init Updator**\n\t"
       << "Updator will watch over " << userInfo.dns_name << endl;
  const auto delay = chrono::milliseconds(config.updateTime * 60 * 1000);
  unsigned int checkCounter = 1;
  while (isProgramRunning) {
    system("date");
    cout << "Checking: " << checkCounter << endl;
    if (requireUpdate())
      update();
    //cout << "Press q + enter to exit program" << endl;
    this_thread::sleep_for(delay);
    checkCounter++;
  }
}
Updator::~Updator() {}
void Updator::asyncLaunch() {
  publicIpAddress = async([]() {
    auto *http = new Http(false);
    auto publicIp = http->getPublicIpAddress()->getResponseString();
    delete http;
    return publicIp;
  });
  dnsContent = async([]() {
    auto *http = new Http(false);
    auto type = Type::A;
    auto content = http->getDNSRecords(&userInfo.email, &userInfo.authKey,
                                       &userInfo.zone_identifier, &type,
                                       &userInfo.dns_name)
                       ->getDNSRecords()[0]
                       ->content;
    delete http;
    return content;
  });
}
bool Updator::update() {
  cout << "Updating " << dnsName << endl;
  auto *http = new Http(false);
  auto type = Type::A;
  auto dnsToUpdate =
      http->getDNSRecords(&userInfo.email, &userInfo.authKey,
                          &userInfo.zone_identifier, &type, &userInfo.dns_name)
          ->getDNSRecords()[0];
  dnsToUpdate->content = dnsIp;
  http->updateDNSRecord(*dnsToUpdate, &userInfo.email, &userInfo.authKey,
                        &userInfo.zone_identifier);
  delete dnsToUpdate;
  delete http;
  auto res = requireUpdate();
  if (!res)
    cout << "**Update successfull**" << endl;
  return !res;
}