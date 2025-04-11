#include <ParticuleApi/System/File.hpp>
#include <sstream>
#include <algorithm>

namespace Particule::Api
{
    File::File(const std::string& path, Mode mode, Endian endian)
        : mode(mode), endian(endian) {
        const char* modeStr = nullptr;
        switch (mode) {
            case Mode::Read: modeStr = "rb"; break;
            case Mode::Write: modeStr = "wb"; break;
            case Mode::Append: modeStr = "ab"; break;
        }
        file = fopen(path.c_str(), modeStr);
        if (!file)
            throw std::runtime_error("Failed to open file: " + path);
    }

    File::File(File&& other) noexcept
        : file(other.file), mode(other.mode), endian(other.endian) {
        other.file = nullptr;
    }

    File::~File() {
        if (file)
            fclose(file);
    }

    File* File::Open(const std::string& path, Mode mode, Endian endian) {
        return new File(path, mode, endian);
    }

    void File::Close(File* file) {
        delete file;
    }

    void File::ReadBigEndian(void* data, size_t size) {
        fread(data, 1, size, file);
    #if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
        std::reverse(reinterpret_cast<char*>(data), reinterpret_cast<char*>(data) + size);
    #endif
    }

    void File::WriteBigEndian(const void* data, size_t size) {
    #if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
        std::vector<char> buffer(reinterpret_cast<const char*>(data), reinterpret_cast<const char*>(data) + size);
        std::reverse(buffer.begin(), buffer.end());
        fwrite(buffer.data(), 1, size, file);
    #else
        fwrite(data, 1, size, file);
    #endif
    }

    void File::ReadLittleEndian(void* data, size_t size) {
        fread(data, 1, size, file);
    #if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
        std::reverse(reinterpret_cast<char*>(data), reinterpret_cast<char*>(data) + size);
    #endif
    }

    void File::WriteLittleEndian(const void* data, size_t size) {
    #if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
        std::vector<char> buffer(reinterpret_cast<const char*>(data), reinterpret_cast<const char*>(data) + size);
        std::reverse(buffer.begin(), buffer.end());
        fwrite(buffer.data(), 1, size, file);
    #else
        fwrite(data, 1, size, file);
    #endif
    }

    std::string File::ReadLine() {
        std::string line;
        char ch;
        while (fread(&ch, 1, 1, file) == 1 && ch != '\n') {
            if (ch != '\r') line += ch;
        }
        return line;
    }

    std::string File::ReadAll() {
        fseek(file, 0, SEEK_END);
        long size = ftell(file);
        fseek(file, 0, SEEK_SET);
        std::string content(size, '\0');
        fread(&content[0], 1, size, file);
        return content;
    }

}