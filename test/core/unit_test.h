#pragma once
#include <cstdio>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <unistd.h>

namespace fs = std::filesystem;

class UnitTest final {
public:
    explicit UnitTest(const char* title);

    template<typename F>
    void Run(const char* title, F func);

private:
    unsigned short _counter = 1;

    static inline unsigned short _block_counter = 1;
    static inline const char* _current_block_title = nullptr;
};

template <typename F> void UnitTest::Run(const char* title, F func) {
    /* Print the number of the test */
    printf("\033[34mUnit test #%hu (%s)", _counter++, title);
    fflush(stdout);

    /* Create a temporary file to store the current output */
    char filename[strlen(_current_block_title) +
                  strlen(title) +
                  sizeof("-.result")];
    snprintf(filename, sizeof(filename), "%s.%s.result",
             _current_block_title, title);
    const fs::path temp_file_path = fs::temp_directory_path() / (char*)filename;
    std::ofstream temp_file(temp_file_path);

    /* Exec the function */
    try {
        func(temp_file);
    } catch (std::exception& e) {
        temp_file << e.what();
    }

    /* Close writing the file */
    temp_file.close();

    /* Open two files for reading: current output and right output */
    snprintf(filename, sizeof(filename), "%s/%s.unit",
             _current_block_title, title);
    fs::path right_output_file_path = fs::path("test/units") / (char*)filename;
    std::ifstream current_output(temp_file_path),
                  right_output(right_output_file_path);

    /* Compare two files */
    bool are_equal = true;
    while (!current_output.eof() && !right_output.eof()) {
        /* Read the data to the buffers */
        constexpr unsigned short buffer_size = 1024;
        char current_output_buffer[buffer_size],
             right_output_buffer[buffer_size];
        unsigned int current_output_buffer_len =
            current_output.read(current_output_buffer, buffer_size).gcount(),
                           right_output_buffer_len =
            right_output.read(right_output_buffer, buffer_size).gcount();

        /* Ignore last invisible chars */
        if (current_output.eof()) {
            char last_char =
                current_output_buffer[current_output_buffer_len - 1];
            while (last_char == '\n' || last_char == '\r' || last_char == ' ')
                last_char =
                    current_output_buffer[--current_output_buffer_len - 1];
        }
        if (right_output.eof()) {
            char last_char =
                right_output_buffer[right_output_buffer_len - 1];
            while (last_char == '\n' || last_char == '\r' || last_char == ' ')
                last_char =
                    right_output_buffer[--right_output_buffer_len - 1];
        }

        /* Compare two buffers */
        if (current_output_buffer_len != right_output_buffer_len ||
            memcmp(current_output_buffer, right_output_buffer,
                   current_output_buffer_len) != 0) {
            are_equal = false;
            break;
        }
    }

    /* Close the files */
    current_output.close();
    right_output.close();

    /* Print the result */
    if (are_equal) {
        printf(" \033[32m[OK]\n");

        /* Remove the temporary file */
        fs::remove(temp_file_path);
    }
    else {
        printf(" \033[31m[ERROR]\n");
        printf("See current output in: %s\n", temp_file_path.c_str());
    }
}