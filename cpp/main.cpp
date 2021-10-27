/*
*** CLOUDFLARE DYNAMIC DNS UPDATER *** version 1.0.0

Opensource software targeting a Cloudflare A record.
Updating record content upon Dynamic DNS changes.
Developped with C++, JSON library: <https://github.com/nlohmann/json>, libcurl.
Deployed in a docker container.

Licensed under the MIT License <http://opensource.org/licenses/MIT>.
SPDX-License-Identifier: MIT
Copyright (c) 2021 Jean Frénoi.
*/
#include "Updator.hpp"
bool isConfigsOk() {
  try {
    auto *http = new Http(false);
    auto type = Type::A;
    auto content = http->getDNSRecords(&userInfo.email, &userInfo.authKey,
                                       &userInfo.zone_identifier, &type,
                                       &userInfo.dns_name)
                       ->getDNSRecords();
    delete http;
    return content.size() == 1;
  } catch (const exception &ex) {
    return false;
  } catch (const string &ex) {
    return false;
  }
}
int main() {
  cout << "Welcome to cloudflareDDNS updater" << endl;
  cout << "**Prodived by Jean Frénoi**" << endl;
  ui::init();
  conf::init();
  if (isConfigsOk()) {
    atomic<bool> running{true};
    thread thread_updator(
        [](atomic<bool> *isProgramRunning) {
          auto updator = new Updator(*isProgramRunning);
          delete updator;
        },
        &running);
    thread_updator.join();
  }
  cout << "Program ended" << endl;
  return 0;
}
