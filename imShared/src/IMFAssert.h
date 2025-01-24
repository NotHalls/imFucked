#pragma once

#define IMF_ASSERT(x, msg)\
{\
    if(x)\
    {\
        std::cerr << "ASSERTION CALLED: " + std::string(msg);\
        throw std::runtime_error("ASSERTION CALLED: " + std::string(msg));\
    }\
}