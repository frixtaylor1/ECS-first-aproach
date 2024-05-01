#include "./Entity.hpp"

Entity::Entity() {
    id_counter++;
    id = id_counter;
}

Entity::~Entity() {
}

bool Entity::operator == (const Entity& entity) const {
    return (id == entity.getId());
}

bool Entity::operator == (size_t anId) const {
    return (getId() == anId);
}

size_t Entity::getId() const {
    return this->id;
}

size_t Entity::id_counter = 0;