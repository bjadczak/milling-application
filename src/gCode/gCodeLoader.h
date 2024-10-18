//
// Created by Bartosz Jadczak on 15/10/2024.
//

#ifndef GCODELOADER_H
#define GCODELOADER_H
#include <string>

#include "nfd.h"


class GCodeLoader {
    static constexpr nfdfilteritem_t filterItem[];
public:
    static std::string chooseFile();
    static std::string saveFile();
};



#endif //GCODELOADER_H
