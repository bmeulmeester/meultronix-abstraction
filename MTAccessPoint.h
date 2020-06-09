#ifndef MEULTRONIX_ACCESS_POINT_H
#define MEULTRONIX_ACCESS_POINT_H

#include "WiFi.h"
#include "ESPAsyncWebServer.h"

class MTAccessPoint
{
private:
    const char *mSsid;
    const char *mPassword;
    int mPort;

    bool mIsEnabled;

    AsyncWebServer *mAsyncWebServer;

public:
    MTAccessPoint(const char *ssid, const char *password, int port = 80);

    void startBroadcasting();
    void stopBroadcasting();

    bool isEnabled();

    String getIpAddress();

    void registerStatusRoute();
};

#endif