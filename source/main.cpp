#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

#include <downloadInfo.hpp>
#include <curl/curl.h>
#include <switch.h>

int main(int argc, char *argv[])
{
    consoleInit(NULL);

    padConfigureInput(1, HidNpadStyleSet_NpadStandard);

    PadState pad;
    padInitializeDefault(&pad);

    socketInitializeDefault();
    nxlinkStdio();

    printf("curl_global_init\n");
    curl_global_init(CURL_GLOBAL_DEFAULT);

    std::string downloadLink = getTrackDownloadLink(253451);

    std::cout << downloadLink << ".\n";
    printf("\e[32mExit.\e[0m");

    while (appletMainLoop())
    {
        padUpdate(&pad);

        u64 kDown = padGetButtonsDown(&pad);

        if (kDown & HidNpadButton_Plus)
            break;

        consoleUpdate(NULL);
    }

    curl_global_cleanup();
    socketExit();
    consoleExit(NULL);
    
    return 0;
}