# *** CLOUDFLARE DYNAMIC DNS UPDATER *** 
## Version 1.0.0

### Description

Opensource software targeting a Cloudflare A record.
Updating record content upon Dynamic DNS changes.
Developped with C++, JSON library: https://github.com/nlohmann/json , libcurl.
Deployed in a docker container.

### Deployement

1. git clone https://github.com/JeanJeanDeLaStreet/CloudflareDDNSUpdater.git
2. cd CloudflareDDNSUpdater
3. cd resources
4. edit userinfo.json with your cloudflare infos
5. edit config.json (optional)
6. cd ..
7. docker build -t jeanjeandelastreet/cloudflareddns .
8. docker run -d --name cloudflareddns jeanjeandelastreet/cloudflareddns
