#include <ParticuleEssential/System/VirtualFile.hpp>

namespace Particule::Essential::System
{
    VirtualResources* VirtualResources::Instance = nullptr;

    VirtualResources::VirtualResources()
    {
        if (Instance == nullptr)
        {
            Instance = this;
        }
    }

    VirtualResources::~VirtualResources()
    {
        if (Instance == this)
        {
            Instance = nullptr;
        }
    }

    void VirtualResources::AddFile(VirtualFile file)
    {
        files.Append(file);
    }

    VirtualFile* VirtualResources::GetFile(String path)
    {
        for (int i = 0; i < files.Size(); i++)
        {
            if (files[i].Path() == path)
            {
                return &files[i];
            }
        }
        return nullptr;
    }

    void VirtualResources::RemoveFile(String path)
    {
        for (int i = 0; i < files.Size(); i++)
        {
            if (files[i].Path() == path)
            {
                files.RemoveAt(i);
                return;
            }
        }
    }

    void VirtualResources::RemoveFile(VirtualFile* file)
    {
        for (int i = 0; i < files.Size(); i++)
        {
            if (&files[i] == file)
            {
                files.RemoveAt(i);
                return;
            }
        }
    }

    VirtualFile::VirtualFile(String path, void* data)
    {
        this->path = path;
        this->data = data;
        this->load = nullptr;
        this->unload = nullptr;
    }

    VirtualFile::VirtualFile(String path, void* data, void (*load)(void*), void (*unload)(void*))
    {
        this->path = path;
        this->data = data;
        this->load = load;
        this->unload = unload;
    }

    VirtualFile::~VirtualFile()
    {
        if (unload != nullptr)
            unload(data);
    }

    void VirtualFile::Load()
    {
        if (loaded)
            return;
        if (load != nullptr)
            load(data);
        loaded = true;
    }

    void VirtualFile::Unload()
    {
        if (!loaded)
            return;
        if (unload != nullptr)
            unload(data);
        loaded = false;
    }

    String VirtualFile::Path()
    {
        return path;
    }

    void* VirtualFile::Data()
    {
        return data;
    }
}