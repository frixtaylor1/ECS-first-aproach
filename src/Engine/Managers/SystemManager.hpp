#pragma once

#include "../Utils/Allocators/StaticVectorAllocator.hpp"
#include "../ECS/System/ISystem.hpp"

#include <vector>

#define MAX_CAP_SYS 10

class SystemManager {
private:
    using SystemContainer = std::vector<ScopePtr<ISystem>, StaticVectorAllocator<ScopePtr<ISystem>, MAX_CAP_SYS> >;
public:
    SystemManager();
    ~SystemManager();

    template <typename SystemType, typename... Args>
    void addSystem(Args &&...args);

    template <typename SystemType>
    SystemType* getSystem() const noexcept;

    SystemContainer& getSystems();

private:
    SystemContainer m_systems;
};

#include "./SystemManagerImp.hpp"

using SystemContainer =  std::vector<ScopePtr<ISystem>, StaticVectorAllocator<ScopePtr<ISystem>, MAX_CAP_SYS> >&;