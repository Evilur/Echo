#pragma once
#include "container/hash_map.h"

#include <cstring>

class Settings final {
public:
    static void Save();

    static void Read();

private:
    class Parameter {
    public:
        enum Type { INTEGER, FLOAT, STRING };

        explicit Parameter(Type type);

        template<typename T>
        Parameter(Type type, T data);

        Parameter(const Parameter&) = delete;
        Parameter* operator=(const Parameter&) = delete;

        ~Parameter();

        template<typename T>
        void Set(T data);

        explicit operator int() const;

        explicit operator float() const;

        explicit operator const char*() const;

    private:
        void* _data = nullptr;
        const Type _type;
    };

    using section_map = HashMap<const char*, Parameter*>;
    static inline HashMap<const char*, section_map*>* _settings_map = nullptr;

public:
    struct UI {
        static inline Parameter chat_list_width{Parameter::INTEGER, 500};
    };
};

template <typename T>
Settings::Parameter::Parameter(const Type type, const T data) :
    Parameter(type) { Set<T>(data); }

template<>
inline void Settings::Parameter::Set(const int data) {
    if (_type != INTEGER) throw
            std::runtime_error("Settings::Parameter: Set<int> invalid type");
    *(int*)_data = data;
}

template<>
inline void Settings::Parameter::Set(const float data) {
    if (_type != FLOAT) throw
            std::runtime_error("Settings::Parameter: Set<float> invalid type");
    *(float*)_data = data;
}

template<>
inline void Settings::Parameter::Set(const char* const data){
    if (_type == STRING) {
        delete[] (char*)_data;
        _data = new char[strlen(data)+ 1];
        strcpy((char*)_data, data);
    } else if (_type == INTEGER) {
        *(int*)_data = atoi(data);
    } else if (_type == FLOAT) {
        *(float*)_data = atof(data);
    }
}