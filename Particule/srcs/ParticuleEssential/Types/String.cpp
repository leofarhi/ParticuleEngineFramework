#include "../../includes/ParticuleEssential/Types/String.hpp"

String::String()
{
    length = 0;
    data = nullptr;
}

String::String(const char *data)
{
    length = strlen(data);
    this->data = new char[length + 1];
    strcpy(this->data, data);
}

String::~String()
{
    delete[] data;
}

String::String(const String &other)
{
    length = other.length;
    data = new char[length + 1];
    strcpy(data, other.data);
}

String &String::operator=(const String &other)
{
    if (this == &other)
    {
        return *this;
    }
    delete[] data;
    length = other.length;
    data = new char[length + 1];
    strcpy(data, other.data);
    return *this;
}

String &String::operator=(const char *data)
{
    delete[] this->data;
    length = strlen(data);
    this->data = new char[length + 1];
    strcpy(this->data, data);
    return *this;
}

String &String::operator+=(const String &other)
{
    char *newData = new char[length + other.length + 1];
    strcpy(newData, data);
    strcpy(newData + length, other.data);
    delete[] data;
    data = newData;
    length += other.length;
    return *this;
}

String &String::operator+=(const char *data)
{
    size_t otherLength = strlen(data);
    char *newData = new char[length + otherLength + 1];
    strcpy(newData, this->data);
    strcpy(newData + length, data);
    delete[] this->data;
    this->data = newData;
    length += otherLength;
    return *this;
}

bool String::operator==(const String &other) const
{
    return strcmp(data, other.data) == 0;
}

bool String::operator==(const char *data) const
{
    return strcmp(this->data, data) == 0;
}

bool String::operator!=(const String &other) const
{
    return strcmp(data, other.data) != 0;
}

bool String::operator!=(const char *data) const
{
    return strcmp(this->data, data) != 0;
}

