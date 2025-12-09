#include "settings.h"
#include "util/logger.h"
#include "util/path.h"

#include <fstream>

void Settings::Save() {
    /* Make a backup of an old settings file (if exists) */
    copy_file(Path::CONFIG_FILE, Path::CONFIG_FILE_BAK,
              fs::copy_options::overwrite_existing);

    /* Create a new settings file */
    std::ofstream config(Path::CONFIG_FILE);
    for (const auto& [section_name, settings_section] : *_settings_map) {
        /* Print a section name */
        config << "[" << section_name << "]" << std::endl;

        /* Print all settings of this section */
        for (const auto& [setting_name, parameter] : *settings_section)
            config << setting_name << " = "
                   << (const char*)*parameter << std::endl;

        /* Print the blank line */
        config << std::endl;
    }

    /* Delete the backup file */
    fs::remove(Path::CONFIG_FILE_BAK);

    /* Print the log */
    INFO_LOG("The settings have been saved");
}

void Settings::Read() {
    /* If the _settings_map is not initialized */
    if (!_settings_map) {
        /* Add UI settings */
        section_map* ui_map = new section_map(5);
        ui_map->Put("chat_list_width", &UI::chat_list_width);

        /* Add all settings sections to the master dictionary */
        _settings_map = new HashMap<const char*, section_map*>(16);
        _settings_map->Put("UI", ui_map);
    }

    /* TODO: handle existing .bak config file */

    /* Parse the settings .ini file */
    std::ifstream config(Path::CONFIG_FILE);
    const section_map* current_section = nullptr;
    while (!config.eof()) {
        /* Read the line */
        char line[1024];
        config.getline(line, sizeof(line));

        /* Delete comments */
        if (char* comment_start = strchr(line, ';');
            comment_start != nullptr) *comment_start = '\0';
        if (char* comment_start = strchr(line, '#');
            comment_start != nullptr) *comment_start = '\0';

        /* Delete spaces in the start and at the end */
        char* line_ptr = line;
        while (*line_ptr == ' ') line_ptr++;
        for (char* line_end = line + strlen(line);
             *line_end == ' '; line_end--) *line_end = '\0';

        /* Ignore empty lines */
        if (line_ptr[0] == '\0') continue;

        /* If the line is a section */
        if (line_ptr[0] == '[') {
            /* Get the section name */
            line_ptr++;
            if (char* comment_start = strchr(line, ']');
                comment_start != nullptr) *comment_start = '\0';

            /* Save the current section */
            try {
                current_section = _settings_map->Get(line_ptr);
            } catch (const std::runtime_error&) { }
            continue;
        }

        /* If the line is a 'key = value' pair,
         * Try to find the '=' symbol */
        char* delimiter = strchr(line_ptr, '=');
        if (delimiter == nullptr) continue;

        const char* const key = line_ptr;
        const char* value = delimiter + 1;

        /* Delete spaces around the '=' delimiter */
        for (char* before_delimiter = delimiter - 1; *before_delimiter == ' ';
             before_delimiter--) *before_delimiter = '\0';
        while (*value == ' ') value++;

        /* If this parameter is out of sections, scip it */
        if (current_section == nullptr) continue;

        /* Put the parameter to the settings */
        try {
            current_section->Get(key)->Set(value);
            TRACE_LOG("Parameter %s has been read from the disk", key);
        } catch (const std::runtime_error&) { }
    }

    INFO_LOG("The settings have been read from the disk");
}

Settings::Parameter::Parameter(const Type type) : _type(type) {
    if (type == INTEGER) _data = new int(0);
    else if (type == FLOAT) _data = new float(0);
}

Settings::Parameter::~Parameter() {
    if (_type == INTEGER) delete (int*)_data;
    else if (_type == FLOAT) delete (float*)_data;
    else delete[] (char*)_data;
}

Settings::Parameter::operator int() const {
    if (_type != INTEGER) throw
            std::runtime_error("Settings::Parameter: Get<int> invalid type");
    return *(int*)_data;
}

Settings::Parameter::operator float() const {
    if (_type != FLOAT) throw
            std::runtime_error("Settings::Parameter: Get<float> invalid type");
    return *(float*)_data;
}

Settings::Parameter::operator const char*() const {
    /* If the parameter is already a string */
    if (_type == STRING) return (const char*)_data;

    /* If the parameter is an integer or a float */
    static char result[24];
    if (_type == INTEGER) snprintf(result, sizeof(result), "%d", *(int*)_data);
    else snprintf(result, sizeof(result), "%f", *(float*)_data);
    return result;
}