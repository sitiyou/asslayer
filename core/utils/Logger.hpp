#pragma once

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

namespace asslayer {

inline bool g_debugEnabled = []() -> bool {
    const char *value = std::getenv("ASSLAYER_DEBUG");
    return value && *value && std::strcmp(value, "0") != 0;
}();

inline void logTimestamp(FILE *fp) {
    time_t now = time(nullptr);
    struct tm tm_buf;
    localtime_r(&now, &tm_buf);
    char buf[9];
    strftime(buf, sizeof(buf), "%H:%M:%S", &tm_buf);
    fprintf(fp, "%s ", buf);
}

} // namespace asslayer

#define LAY_ERR(...)                                                           \
    do {                                                                       \
        ::asslayer::logTimestamp(stderr);                                      \
        fprintf(stderr, "[ERROR] " __VA_ARGS__);                               \
        fputc('\n', stderr);                                                   \
    } while (0)

#define LAY_WARN(...)                                                          \
    do {                                                                       \
        ::asslayer::logTimestamp(stderr);                                      \
        fprintf(stderr, "[WARN] " __VA_ARGS__);                                \
        fputc('\n', stderr);                                                   \
    } while (0)

#define LAY_LOG(...)                                                           \
    do {                                                                       \
        ::asslayer::logTimestamp(stderr);                                      \
        fprintf(stderr, "[INFO] " __VA_ARGS__);                                \
        fputc('\n', stderr);                                                   \
    } while (0)

#define LAY_DEBUG(...)                                                         \
    do {                                                                       \
        if (::asslayer::g_debugEnabled) {                                      \
            ::asslayer::logTimestamp(stderr);                                  \
            fprintf(stderr, "[DEBUG] " __VA_ARGS__);                           \
            fputc('\n', stderr);                                               \
        }                                                                      \
    } while (0)
