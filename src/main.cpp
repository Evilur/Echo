#include "app/app.h"
#include "config/settings.h"
#include "util/path.h"
#include "util/logger.h"

int main() {
    /* Init static classes */
    Path::Init();

    /* Read the settings from the config file */
    Settings::Read();

    /* Set the ultralight log file */
    ultralight::Platform::instance().set_logger(
        ultralight::GetDefaultLogger(Path::ULTRALIGHT_LOG.c_str())
    );
    INFO_LOG("Ultralight log file: %s", Path::ULTRALIGHT_LOG.c_str());

    /* Run the application */
    const App app;
    app.Run();
    return 0;
}