#include "ArduiPi_OLED_lib.h"
#include "Adafruit_GFX.h"
#include "ArduiPi_OLED.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <iostream>

std::string systems [] = { "kodi", "megadrive", "n64", "psx", "segacd", "snes", "retropie" };
int systems_len = sizeof(systems)/sizeof(systems[0]);

/// Loads the image at the path and converts it to the correct format. The returned image will use a single bit per
/// colour.
/// \param path Image path.
/// \param image_bmp
/// \return Converted image.
uint8_t* load_image(const char* path, uint8_t* image_bmp) {
    SDL_RWops *rwop;
    rwop = SDL_RWFromFile(path, "rb");
    SDL_Surface * image = IMG_LoadPNM_RW(rwop);
    auto *pixels = (Uint8*) image->pixels;

    for (int i = 0; i < image->w * image->h; i += 8) {
        uint8_t num = 0;
        for (int j = 0; j < 8; ++j) {
            num = num << 1;
            // 1 is black
            if (pixels[i + j] == 1)
                num += 1;
        }
        image_bmp[i / 8] = num;
    }

    return image_bmp;
}

void display_marquee(const char* path) {
    printf("Using path: %s\n", path);
    uint8_t image_bmp[128 * 32 / 8];
    load_image(path, image_bmp);

    ArduiPi_OLED display;
    if ( !display.init(OLED_I2C_RESET, OLED_ADAFRUIT_I2C_128x32) )
        exit(EXIT_FAILURE);
    display.begin();
    display.clearDisplay();  // clears the screen  buffer
    display.display();  // clear display
    display.drawBitmap(0, 0, image_bmp, 128, 32, WHITE);
}

/// Loads the correct image path for the system, then displays the image.
/// \param system The name of the system to display.
/// \return true if system has a marquee, false otherwise
bool load_marquee(const char* system) {
    char path[100];
    //strcpy(path, "/usr/share/rpi-mini-marquee/marquees/black_white/");
    strcpy(path, "/home/courts/rpi-mini-marquee/marquees/black_white/");

    // Check if a known system is matched
    for(int i = 0; i < systems_len; ++i) {
        if (!systems[i].compare(system)) {
            strcat(path, system);
            display_marquee(strcat(path, ".pbm"));
            return true;
        }
    }
    return false;
}

/// Prints the help screen.
/// \param program_name The name the user typed to execute the program.
void print_help(const char* program_name) {
    printf("Usage: %s {OPTION | SYSTEM_NAME | OPTION SYSTEM_NAME}\n", program_name);
    printf("Alters the image displayed on the Raspberry Pi's mini marquee.\n");
    printf("\n");
    printf("  -f SYSTEM NAME    forces the marquee to change, if the provided one fails, it defaults to \"retropie\".\n");
    printf("  -h, --help        displays this help screen.\n");
}

int main(int argc, char *argv[]) {
    // rpi-mini-marquee -h
    if (argc > 1 && (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0))
        load_marquee(argv[1]);
    // rpi-mini-marquee psx
    else if (argc == 2) {
        if (!load_marquee("retropie")) {
            printf("%s: invalid input '%s'\n", argv[0], argv[1]);
            printf("Try '%s --help' for more information.\n", argv[0]);
            return EXIT_FAILURE;
        }
    }
    // rpi-mini-marquee -f psx
    else if (argc == 3 && strcmp(argv[1], "-f") == 0) {
        if (!load_marquee(argv[2]))
            load_marquee("retropie");
    }
    // Show error screen
    else {
        printf("%s: invalid input '%s'\n", argv[0], argv[1]);
        printf("Try '%s --help' for more information.\n", argv[0]);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}