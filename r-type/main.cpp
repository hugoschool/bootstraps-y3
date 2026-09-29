#include "Components.hpp"
#include "Registry.hpp"
#include "SparseArray.hpp"
#include <iostream>

int main(void)
{
    auto registry = Registry();

    registry.registerComponent<Component>();
    auto entity1 = registry.spawnEntity();
    auto entity2 = registry.spawnEntity();
    auto entity3 = registry.spawnEntity();

    registry.addComponent<Component>(entity1, Component());
    registry.addComponent<Component>(entity2, Component());

    auto components = registry.getComponents<Component>();
    std::cout << components.size() << std::endl;
    return 0;
}
