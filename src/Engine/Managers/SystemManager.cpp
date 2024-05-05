#include "./SystemManager.hpp"

SystemManager::SystemManager() = default;
SystemManager::~SystemManager() = default;

SystemContainer& SystemManager::getSystems() {
    return m_systems;
}
