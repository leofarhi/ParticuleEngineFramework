#include <ParticuleEssential/System/VirtualFile.hpp>

namespace Particule::Essential
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
        for (auto& item : files) {
            if (item.Path() == path)
            {
                return &item;
            }
        }
        return nullptr;
    }

    void VirtualResources::RemoveFile(String path)
    {
        size_t i = 0;
        for (auto& item : files) {
            if (item.Path() == path)
            {
                files.RemoveAt(i);
                return;
            }
            i++;
        }
    }

    void VirtualResources::RemoveFile(VirtualFile* file)
    {
        size_t i = 0;
        for (ListNode<VirtualFile> *cur = nullptr; files.ForEach(&cur);)
        {
            if (&cur->data == file)
            {
                files.RemoveAt(i);
                return;
            }
            i++;
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