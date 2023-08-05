#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <switch.h>

#include <curl/curl.h>

void network_request(void) 
{
    CURL *curl;
    CURLcode res;

    printf("curl init\n");
    curl_global_init(CURL_GLOBAL_DEFAULT);

    curl = curl_easy_init();

    if (curl) 
    {
        curl_easy_setopt(curl, CURLOPT_URL, "https://music.yandex.by/");
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "libnx curl/1.0");

        printf("curl_easy_perform\n");
        consoleUpdate(NULL);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
            printf("curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        else
            printf(res + "\n");

        printf("cleanup\n");
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
}

int main(int argc, char* argv[]) 
{
    consoleInit(NULL);

    padConfigureInput(1, HidNpadStyleSet_NpadStandard);

    PadState pad;
    padInitializeDefault(&pad);

    printf("Welcome to ymnx!\n");

    socketInitializeDefault();
    network_request();

    while (appletMainLoop()) 
    {
        padUpdate(&pad);

        u64 kDown = padGetButtonsDown(&pad);

        if (kDown & HidNpadButton_Plus)
            break;

        consoleUpdate(NULL);
    }

    socketExit();
    consoleExit(NULL);
    return 0;
}