#pragma once
#include "../../Utils/Common.hpp"
#include <raylib.h>

/**
 * Specification of type IComponent...
 */
interface IComponent { 
    virtual ~IComponent(); 
};

interface IDrawableComponent : extends IComponent {
    virtual ~IDrawableComponent();
};