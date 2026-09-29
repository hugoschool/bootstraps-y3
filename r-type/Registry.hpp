#pragma once

#include "Entity.hpp"
#include "SparseArray.hpp"
#include <any>
#include <iterator>
#include <optional>
#include <typeindex>
#include <unordered_map>
#include <vector>

// TODO: exceptions
class Registry {
    public:
        Registry() : _componentsArrays(), _entities() {};
        ~Registry() {};

        template <class Component>
        SparseArray<Component> &registerComponent() {
            auto array = SparseArray<Component>();
            std::pair pair = _componentsArrays.insert_or_assign(std::type_index(typeid(Component)), std::any_cast<SparseArray<Component>>(array));

            return std::any_cast<SparseArray<Component>&>((*pair.first).second);
        }

        template <class Component>
        SparseArray<Component> &getComponents() {
            return std::any_cast<SparseArray<Component>&>(_componentsArrays.at(std::type_index(typeid(Component))));
        }

        template <class Component>
        SparseArray<Component> const &getComponents() const {
            return std::any_cast<SparseArray<Component>&>(_componentsArrays.at(std::type_index(typeid(Component))));
        }

        Entity spawnEntity() {
            std::optional<Entity> entity = std::make_optional<Entity>();
            _entities.push_back(entity);
            return entity.value();
        }

        Entity entityFromIndex(std::size_t idx) {
            // TODO: exception
            return _entities.at(idx).value();
        }

        std::size_t getIndexOfEntity(Entity const &e) {
            auto it = std::find(_entities.begin(), _entities.end(), std::make_optional<Entity>(e));

            if (it == _entities.end())
                return _entities.size();

            return std::distance(_entities.begin(), it);
        }

        void killEntity(Entity const &e) {
            auto it = std::find(_entities.begin(), _entities.end(), e);

            if (it == _entities.end())
                return;

            (*it) = std::nullopt;
        }

        template <typename Component>
        typename SparseArray<Component>::ReferenceType addComponent(Entity const &to, Component &&c) {
            SparseArray<Component> &components = getComponents<Component>();
            std::size_t idx = getIndexOfEntity(to);

            return components.insert_at(idx, c);
        }

        template <typename Component, typename ...Params>
        typename SparseArray<Component>::ReferenceType emplaceComponent(Entity const &to, Params &&...p) {
            SparseArray<Component> &components = getComponents<Component>();
            std::size_t idx = getIndexOfEntity(to);

            return components.emplace_at(idx, p...);
        }

        template <typename Component>
        void removeComponent(Entity const &from) {
            SparseArray<Component> &components = getComponents<Component>();
            std::size_t idx = getIndexOfEntity(from);

            components.erase(idx);
        }

    private:
        std::unordered_map<std::type_index, std::any> _componentsArrays;

        // TODO: create an entities array class
        std::vector<std::optional<Entity>> _entities;
};
