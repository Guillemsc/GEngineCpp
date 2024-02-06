//
// Created by Guillem on 06/02/2024.
//

#ifndef GENGINEGAME_FILESYSTEMRESOURCEORIGIN_H
#define GENGINEGAME_FILESYSTEMRESOURCEORIGIN_H

#include "Contexts/Data/ResourceOrigin/ResourceOrigin.h"

#include <string>

namespace GEngine
{
    class FileSystemResourceOrigin : public ResourceOrigin
    {
    public:
        explicit FileSystemResourceOrigin(const std::string& filepath);

        std::string GetFilepath();

    private:
        std::string _filepath;
    };
} // GEngine

#endif //GENGINEGAME_FILESYSTEMRESOURCEORIGIN_H
