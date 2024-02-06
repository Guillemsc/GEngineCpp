//
// Created by Guillem on 06/02/2024.
//

#include "FileSystemResourceOrigin.h"

namespace GEngine
{
    FileSystemResourceOrigin::FileSystemResourceOrigin(const std::string &filepath)
    {
        _filepath = filepath;
    }

    std::string FileSystemResourceOrigin::GetFilepath()
    {
        return _filepath;
    }
} // GEngine