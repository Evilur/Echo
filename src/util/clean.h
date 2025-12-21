#pragma once

#define PREVENT_COPY_ALLOW_MOVE(T)\
T(const T&) = delete;             \
T& operator=(const T&) = delete;  \
T(T&&) = default;                 \
T& operator=(T&&) = default

#define PREVENT_COPY_AND_MOVE(T)\
T(const T&) = delete;           \
T& operator=(const T&) = delete;\
T(T&&) = delete;                \
T& operator=(T&&) = delete
