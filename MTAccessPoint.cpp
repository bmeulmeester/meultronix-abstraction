#include "MTAccessPoint.h"

#include "SPIFFS.h"

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

    this->registerSPIFFSRoutes();
    this->registerStatusRoute();

    mIsEnabled = true;

    SPIFFS.begin();

    Serial.print("Local IP Address: ");
    Serial.println(this->getIpAddress());
}

void MTAccessPoint::stopBroadcasting()
{
    mIsEnabled = false;

    WiFi.enableAP(false);
    this->mAsyncWebServer->end();
    SPIFFS.end();
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

void MTAccessPoint::registerSPIFFSRoutes()
{
    mAsyncWebServer->on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "index.html", String(), false);
    });

    mAsyncWebServer->on("/bulma-0.9.0-min.css", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "bulma-0.9.0-min.css", "text/css");
    });

    mAsyncWebServer->onNotFound([](AsyncWebServerRequest *request) {
        AsyncWebServerResponse *response = request->beginResponse(SPIFFS, "/not-found.html", "text/html");
        response->setCode(404);

        request->send(response);
    });
}

void MTAccessPoint::registerStatusRoute()
{
    mAsyncWebServer->on("/status", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(200, "text/plain", "Hello, world");
    });
}