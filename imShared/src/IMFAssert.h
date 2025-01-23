#pragma once

#define IMF_ASSERT(x, msg)\
{\
    if(x)\
    {\
        throw std::runtime_error("ASSERTION CALLED: " + std::string(msg));\
    }\
}