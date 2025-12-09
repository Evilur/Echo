#pragma once
#include "logger.h"


#include <cstring>
#include <type_traits>

class Hash final {
public:
    template <typename T>
    static unsigned long Get(const T& element) noexcept;

private:
    static unsigned long Calculate(const unsigned char* element,
                                   unsigned short size) noexcept;
};

template <>
inline unsigned long Hash::Get(const char* const& element) noexcept {
    return Calculate((const unsigned char*)(void*)element, strlen(element) + 1);
}

template <>
inline unsigned long Hash::Get(char* const& element) noexcept {
    return Calculate((const unsigned char*)(void*)element, strlen(element) + 1);
}

template <typename T>
unsigned long Hash::Get(const T& element) noexcept {
    /* This method cannot work with pointers */
    static_assert(!std::is_pointer_v<T>,
                  "HashMap::GetHash() can't work with pointers as a key");

    /* Get the byte array from the element and calc the hash */
    return Calculate((const unsigned char*)(void*)&element, sizeof(element));
}
