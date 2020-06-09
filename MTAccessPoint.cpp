#include "MTAccessPoint.h"

MTAccessPoint::MTAccessPoint(const char *ssid, const char *password, int port)
{
    mSsid = ssid;
    mPassword = password;
    mPort = port;
    mIsEnabled = false;

    mAsyncWebServer = new AsyncWebServer(mPort);
}

void MTAccessPoint::startBroadcasting()
{
    WiFi.mode(WIFI_MODE_AP);
    WiFi.softAP(mSsid, mPassword);

    this->mAsyncWebServer->begin();

    this->registerStatusRoute();

    mIsEnabled = true;

    Serial.print("Local IP Address: ");
    Serial.println(this->getIpAddress());
}

void MTAccessPoint::stopBroadcasting()
{
    WiFi.enableAP(false);

    mIsEnabled = false;
}

bool MTAccessPoint::isEnabled()
{
    return mIsEnabled;
}

String MTAccessPoint::getIpAddress()
{
    IPAddress address = WiFi.softAPIP();

    if (address) {
        return address.toString();
    }

    return "";
}

void MTAccessPoint::registerStatusRoute()
{
    mAsyncWebServer->on("/status", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(200, "text/plain", "Hello, world");
    });
}