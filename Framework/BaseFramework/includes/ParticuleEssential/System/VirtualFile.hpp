#ifndef VIRUTALFILE_HPP
#define VIRUTALFILE_HPP
#include <ParticuleEssential/Types/String.hpp>
#include <ParticuleEssential/Types/List.hpp>

namespace Particule::Essential
{
    class VirtualFile
    {
        String path;
        void* data;
        bool loaded;
        //function to load the file
        void (*load)(void*);
        //function to unload the file
        void (*unload)(void*);
    public:
        VirtualFile(String path, void* data);
        VirtualFile(String path, void* data, void (*load)(void*), void (*unload)(void*));
        ~VirtualFile();
        void Load();
        void Unload();
        String Path();
        void* Data();
    };

    class VirtualResources
    {
        List<VirtualFile> files;

    public:
        static VirtualResources* Instance;

        VirtualResources();
        ~VirtualResources();
        void AddFile(VirtualFile file);
        VirtualFile *GetFile(String path);
        void RemoveFile(String path);
        void RemoveFile(VirtualFile *file);
    };
}

#endif // VIRUTALFILE_HPP