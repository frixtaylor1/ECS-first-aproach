#ifndef SYSTEMMANAGER_HPP
#define SYSTEMMANAGER_HPP

#include "./SystemManager.hpp"

template <typename SystemType, typename... Args>
void SystemManager::addSystem(Args &&...args) {
    m_systems.emplace_back(new SystemType(std::forward<Args>(args)...));
}

template <typename SystemType>
SystemType* SystemManager::getSystem() const noexcept {
    for (const ScopePtr<ISystem>& system : m_systems) {
        if (SystemType* castedSystem = dynamic_cast<SystemType*>(system.get())) {
            return castedSystem;
        }
    }
    return nullptr;
}

#endif // SYSTEMMANAGER_HPP