#pragma once
#include "container/dictionary.h"

class Settings final {
public:
    static void Init();

    static void Save();

private:
    class Parameter {
    public:
        enum Type { INTEGER, FLOAT, STRING };

        Parameter(int data);

        Parameter(float data);

        Parameter(const char* data);

        Parameter(const Parameter&) = delete;
        Parameter* operator=(const Parameter&) = delete;

        ~Parameter();

        void Set(int data);

        void Set(float data);

        void Set(const char* data);

        explicit operator int() const;

        explicit operator float() const;

        explicit operator const char*() const;

    private:
        void* _data = nullptr;
        const Type _type;
    };

    using section_map = Dictionary<const char*, Parameter*>;
    static inline Dictionary<const char*, section_map*>* _settings_map = nullptr;

public:
    struct UI {
        static inline Parameter chat_list_width = 500;
        static inline Parameter language = "ru";
    };
};