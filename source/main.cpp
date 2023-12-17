#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>

#include <nlohmann/json.hpp>
#include <curl/curl.h>
#include <switch.h>
#include <borealis.hpp>

#include <Client.hpp>
#include <DownloadInfo.hpp>

using json = nlohmann::json;
using namespace brls::literals;

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

int main(int argc, char *argv[])
{
    padConfigureInput(1, HidNpadStyleSet_NpadStandard);

    PadState pad;
    padInitializeDefault(&pad);

    socketInitializeDefault();
    nxlinkStdio();

    brls::Logger::setLogLevel(brls::LogLevel::LOG_DEBUG);

    // Init the app and i18n
    if (!brls::Application::init())
    {
        brls::Logger::error("Unable to init Borealis application");
        return EXIT_FAILURE;
    }

    brls::Application::createWindow("ymnx");

    // Have the application register an action on every activity that will quit when you press BUTTON_START
    brls::Application::setGlobalQuit(false);

    //brls::Application::registerXMLView("SettingsTab", SettingsTab::create);

    class MainActivity : public brls::Activity
    {
    public:
        // Declare that the content of this activity is the given XML file
        CONTENT_FROM_XML_RES("activity/main.xml");
    };

    // Create and push the main activity to the stack
    brls::Application::pushActivity(new MainActivity());

    Client *client = new Client("");
    client->initialize();

    client->accountInfo();
    client->search("Yakui The Maid", true, "all", 0);

    std::string downloadLink = getTrackDownloadLink(43207144);

    /*CURL *curl;
    FILE *fp;
    CURLcode res;
    char outfilename[FILENAME_MAX] = "/music/track2.mp3";
    curl = curl_easy_init();
    if (curl)
    {
        printf("download TRACK\n");
        fp = fopen(outfilename, "wb");
        curl_easy_setopt(curl, CURLOPT_URL, downloadLink.c_str());
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        fclose(fp);
    }*/

    printf("%s\n", downloadLink.c_str());

    while (brls::Application::mainLoop())
    {  
    }

    printf("\e[32mExit.\e[0m\n");

    client->~Client();

    socketExit();
    _exit(0);
}