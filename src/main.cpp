#include "util/path.h"
#include "config/settings.h"

int main(int argc, char* argv[]) {
    /* Init static classes */
    Path::Init();
    Settings::Init();

    /* Read the settings from the config file */
    Settings::Read();
}