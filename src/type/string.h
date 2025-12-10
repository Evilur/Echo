#pragma once

#include <string_view>
#include <cstdio>

class String final {
public:
    String() noexcept = delete;

    explicit String(unsigned long str_size) noexcept;

    String(const char* str) noexcept;

    String(const char* str, unsigned long str_size) noexcept;

    String(const String&) noexcept = delete;

    String(String&&) noexcept = default;

    ~String() noexcept;

    String operator+(char symbol) const noexcept;

    operator const char*() const noexcept;

    operator std::string_view() const noexcept;

private:
    char* const _str;
    unsigned long _size;

    template <typename T>
    static T ToUInt(const char* str) noexcept;

    template <typename T, typename U>
    static T ToInt(const char* str) noexcept;

public:
    template<typename... Args>
    static String Format(const char* format, Args... args) noexcept;

    static unsigned char ToUInt8(const char* str) noexcept;

    static unsigned short ToUInt16(const char* str) noexcept;

    static unsigned int ToUInt32(const char* str) noexcept;

    static unsigned long ToUInt64(const char* str) noexcept;

    static char ToInt8(const char* str) noexcept;

    static short ToInt16(const char* str) noexcept;

    static int ToInt32(const char* str) noexcept;

    static long ToInt64(const char* str) noexcept;

};

template <typename T>
T String::ToUInt(const char* str) noexcept {
    T result = 0;
    while (*str >= '0' && *str <= '9') {
        result *= 10;
        result += *str++ - '0';
    }
    return result;
}

template <typename T, typename U>
T String::ToInt(const char* str) noexcept {
    if (*str++ == '-') return -ToUInt<U>(str);
    return ToUInt<U>(str);
}

template <typename... Args>
String String::Format(const char* const format, Args... args) noexcept {
    const int string_size = snprintf(nullptr, 0, format, args...);
    String result(string_size);
    sprintf(result._str, format, args...);
    return result;
}