#include "../../../includes/ParticuleEssential/Types/String.hpp"
#include <cstdio>

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

String &String::operator+=(const int number)
{
    char buffer[20];
    sprintf(buffer, "%d", number);
    return *this += buffer;
}

String String::operator+(const String &other) const
{
    String result;
    result.length = length + other.length;
    result.data = new char[result.length + 1];
    strcpy(result.data, data);
    strcpy(result.data + length, other.data);
    return result;
}

String String::operator+(const char *data) const
{
    size_t otherLength = strlen(data);
    String result;
    result.length = length + otherLength;
    result.data = new char[result.length + 1];
    strcpy(result.data, this->data);
    strcpy(result.data + length, data);
    return result;
}

String String::operator+(const int number) const
{
    char buffer[20];
    sprintf(buffer, "%d", number);
    return *this + buffer;
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

char &String::operator[](size_t index)
{
    return data[index];
}

const char &String::operator[](size_t index) const
{
    return data[index];
}

const char *String::c_str() const
{
    return data;
}

size_t String::size() const
{
    return length;
}

bool String::empty() const
{
    return length == 0;
}

void String::clear()
{
    delete[] data;
    length = 0;
    data = nullptr;
}