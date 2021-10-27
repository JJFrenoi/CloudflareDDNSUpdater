#ifndef DEF_UPDATOR
#define DEF_UPDATOR
#include "Config.hpp"
#include "Http.hpp"
#include "UserInfo.hpp"
#include <atomic>
#include <chrono>
#include <future>
#include <thread>
using namespace ui;
using namespace conf;
class Updator {
private:
  string dnsName;
  string dnsIp;
  future<string> publicIpAddress;
  future<string> dnsContent;
  void asyncLaunch();
  bool update();
  bool requireUpdate();

public:
  ~Updator();
  Updator(atomic<bool> &isProgramRunning);
};
#endif