//
// Created by Guillem on 06/02/2024.
//

#include "FileSystemResourceOrigin.h"

#include <utility>

namespace GEngine
{
    FileSystemResourceOrigin::FileSystemResourceOrigin(std::string filepath)
        : ResourceOrigin(ResourceOriginType::FILE_SYSTEM), _filepath(std::move(filepath))
    {

    }

    std::string FileSystemResourceOrigin::GetFilepath() const
    {
        return _filepath;
    }
} // GEngine