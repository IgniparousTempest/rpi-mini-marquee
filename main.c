#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

char * systems [] = { "kodi", "megadrive", "n64", "psx", "segacd", "snes", "retropie" };
int systems_len = sizeof(systems)/sizeof(systems[0]);

void display_marquee(const char* path) {
    printf("Using path: %s\n", path);
}

/// Loads the correct image path for the system, then displays the image.
/// \param system The name of the system to display.
/// \return true if system has a marquee, false otherwise
bool load_marquee(const char* system) {
    char path[100];
    strcpy(path, "/usr/share/rpi-mini-marquee/black_white/");

    // Check if a known system is matched
    for(int i = 0; i < systems_len; ++i) {
        if (!strcmp(systems[i], system)) {
            strcat(path, system);
            display_marquee(strcat(path, ".png"));
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