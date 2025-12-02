#pragma once
#include <filesystem>
#include <pwd.h>
#include <unistd.h>

namespace fs = std::filesystem;

class Path final {
public:
    /* Initialize the class */
    static void Init();

/* If we are compiling for Unix based */
#if defined(__unix__) || defined(__unix) || defined(unix)
    /* Get the user home directory */
    static inline const fs::path HOME_DIR = getpwuid(getuid())->pw_dir;

    /* Get the config directory */
    static inline const fs::path CONFIG_DIR = HOME_DIR / ".config";

    /* Get the log directory */
    static inline const fs::path LOG_DIR = HOME_DIR / ".cache/Echo";

#endif
    /* Get the config file path */
    static inline const fs::path CONFIG_FILE = CONFIG_DIR / "Echo.ini";

    /* Get the ultralight log file path */
    static inline const fs::path ULTRALIGHT_LOG = LOG_DIR / "ultralight.log";

    /* Get the basic log file */
    static inline const fs::path LOG_FILE = LOG_DIR / "echo.log";
};
