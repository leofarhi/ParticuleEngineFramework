#include <gint/dma.h>
#include <ParticuleApi/System/gint.hpp>
#include <ParticuleApi/System/File.hpp>

using namespace gint;

namespace Particule::Api
{
    #include <type_traits>

    template<typename Func>
    void File::OpenWith(const std::string& path, Mode mode, Endian endian, Func&& func) {
        gint::gint_wswitch_enter();
        File* file = new File(path, mode, endian);
        func(file);
        delete file;
        gint::gint_wswitch_exit();
    }

    template<typename T>
    void File::Write(const T& data) {
        static_assert(std::is_trivially_copyable<T>::value, "T must be trivially copyable");
        if (endian == Endian::BigEndian)
            WriteBigEndian(&data, sizeof(T));
        else
            WriteLittleEndian(&data, sizeof(T));
    }

    template<typename T>
    void File::Write(const T* data, size_t size) {
        static_assert(std::is_trivially_copyable<T>::value, "T must be trivially copyable");
        for (size_t i = 0; i < size; ++i)
            Write(data[i]);
    }

    template<typename T>
    void File::Read(T& data) {
        static_assert(std::is_trivially_copyable<T>::value, "T must be trivially copyable");
        if (endian == Endian::BigEndian)
            ReadBigEndian(&data, sizeof(T));
        else
            ReadLittleEndian(&data, sizeof(T));
    }

    template<typename T>
    void File::Read(T* data, size_t size) {
        static_assert(std::is_trivially_copyable<T>::value, "T must be trivially copyable");
        for (size_t i = 0; i < size; ++i)
            Read(data[i]);
    }

}