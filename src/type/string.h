#pragma once

#include <string_view>

class String final {
public:
    String() noexcept = delete;

    explicit String(unsigned long str_size) noexcept;

    String(const char* str) noexcept;

    String(const char* str, unsigned long str_size) noexcept;

    explicit String(const String& string) noexcept;

    ~String() noexcept;

    String operator+(char symbol) const noexcept;

    operator const char*() const noexcept;

    operator std::string_view() const noexcept;

private:
    char* const _str;
    unsigned long _size;

public:
    template<typename... Args>
    static String Format(const char* format, Args... args) noexcept;

    template <typename T>
    static T ToInt(const char* str) noexcept;
};

#include "string_imp.h"