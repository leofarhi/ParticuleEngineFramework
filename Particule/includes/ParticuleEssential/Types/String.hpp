#ifndef STRING_HPP
#define STRING_HPP
#include <string.h>
#include <stdlib.h>

class String
{
public:
    size_t length;
    char *data;

    String();
    String(const char *data);
    ~String();
    String(const String &other);
    String &operator=(const String &other);
    String &operator=(const char *data);
    String &operator+=(const String &other);
    String &operator+=(const char *data);
    bool operator==(const String &other) const;
    bool operator==(const char *data) const;
    bool operator!=(const String &other) const;
    bool operator!=(const char *data) const;

};

#endif // STRING_HPP