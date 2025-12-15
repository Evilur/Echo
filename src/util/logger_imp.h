#pragma once

#include <cstdio>
#include <ctime>

template <typename... Args>
void Logger::Log(FILE* const stream,
                 const LogLevel log_level,
                 const char* const format,
                 Args... args) {
    /* Get current time */
    char time_buffer[20];
    const time_t current_time = time(nullptr);
    const tm* const time_info = localtime(&current_time);
    strftime(time_buffer, sizeof(time_buffer),
             "%Y.%m.%d %H:%M:%S", time_info);

    /* Print the prefix */
    fprintf(stream, "%s[%s] %s",
            COLOR_CODE_STR[log_level],
            time_buffer,
            LOG_LEVEL_STR[log_level]);

    /* Print the message */
    fprintf(stream, format, args...);

    /* Print a new line char */
    fputc('\n', stream);
}