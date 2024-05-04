#pragma once

#include "../../Utils/Common.hpp"

interface ISystem {
    virtual ~ISystem();
    virtual void update() = 0;    
};

