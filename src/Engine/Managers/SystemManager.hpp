#pragma once

#include "../Utils/Allocators/StaticAllocator.hpp"
#include "../ECS/System/ISystem.hpp"

#include <vector>

#define MAX_CAP_SYS 10

class SystemManager {
private:
    using SystemContainer = std::vector<ScopePtr<ISystem>, StaticAllocator<ScopePtr<ISystem>, MAX_CAP_SYS> >;
public:
    SystemManager() = default;
    ~SystemManager() {}

    template <typename SystemType, typename... Args>
    void addSystem(Args &&...args) {
        m_systems.emplace_back(new SystemType(std::forward<Args>(args)...));
    }

    template <typename SystemType>
    SystemType* getSystem() const noexcept {
        for (const ScopePtr<ISystem>& system : m_systems) {
            if (SystemType* castedSystem = dynamic_cast<SystemType*>(system.get())) {
                return castedSystem;
            }
        }
        return nullptr;
    }

    SystemContainer& getSystems() {
        return m_systems;
    }

private:
    SystemContainer m_systems;
};

using SystemContainer =  std::vector<ScopePtr<ISystem>, StaticAllocator<ScopePtr<ISystem>, MAX_CAP_SYS> >&;