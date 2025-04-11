#ifndef RESOURCES_HPP
#define RESOURCES_HPP
#include <string>

namespace Particule::Api
{
    struct Resource {
        void* data;
        std::string path;
        Resource(const std::string& path) : data(nullptr), path(path) {}
        Resource(void* data) : data(data), path("") {}
        Resource(const Resource& other) : data(other.data), path(other.path) {}
        Resource& operator=(const Resource& other) {
            if (this != &other) {
                data = other.data;
                path = other.path;
            }
            return *this;
        }
        ~Resource() = default;
    };
}

#endif // RESOURCES_HPP