#include "hash_map.h"
#include "container/hash_map.h"

#include "../core/unit_test.h"

void hash_map_unit_test() {
    UnitTest test("HashMap");
    constexpr const char* const num_str[16] = {
        "one", "two", "three", "four",
        "five", "six", "seven", "eight",
        "nine", "ten", "eleven", "twelve",
        "thirteen", "fourteen", "fifteen", "sixteen"
    };

    test.Run("Put(key, element) - 1", [&num_str](std::ofstream& file) {
        HashMap<const char*, int> map(4);
        for (int i = 1; i <= 16; i++) map.Put(num_str[i - 1], i);
        char* const str = new char[16];
        for (const char* const num : num_str) {
            strcpy(str, num);
            file << map.Get(num) << std::endl;
        }
        delete[] str;
    });

    test.Run("Put(key, element) - 2", [&num_str](std::ofstream& file) {
        HashMap<const char*, int> map(8);
        for (int i = 1; i <= 16; i++) map.Put(num_str[i - 1], i);
        char* const str = new char[16];
        for (const char* const num : num_str) {
            strcpy(str, num);
            file << map.Get(num) << std::endl;
        }
        delete[] str;
    });

    test.Run("Put(key, element) - 3", [&num_str](std::ofstream& file) {
        HashMap<const char*, int> map(16);
        for (int i = 1; i <= 16; i++) map.Put(num_str[i - 1], i);
        char* const str = new char[16];
        for (const char* const num : num_str) {
            strcpy(str, num);
            file << map.Get(num) << std::endl;
        }
        delete[] str;
    });

    test.Run("Put(key, element) - 4", [&num_str](std::ofstream& file) {
        HashMap<int, const char*> map(4);
        for (int i = 1; i <= 16; i++) map.Put(i, num_str[i - 1]);
        for (int i = 1; i <= 16; i++) {
            file << map.Get(i) << std::endl;
        }
    });

    test.Run("Put(key, element) - 5", [&num_str](std::ofstream& file) {
        HashMap<int, const char*> map(8);
        for (int i = 1; i <= 16; i++) map.Put(i, num_str[i - 1]);
        for (int i = 1; i <= 16; i++) {
            file << map.Get(i) << std::endl;
        }
    });

    test.Run("Put(key, element) - 6", [&num_str](std::ofstream& file) {
        HashMap<int, const char*> map(16);
        for (int i = 1; i <= 16; i++) map.Put(i, num_str[i - 1]);
        for (int i = 1; i <= 16; i++) {
            file << map.Get(i) << std::endl;
        }
    });
}