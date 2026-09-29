#include "Entity.hpp"
#include "SparseArray.hpp"
#include <iostream>

int main(void)
{
    auto sparse_array = SparseArray<Entity>();

    auto entity1 = Entity();
    auto entity2 = Entity();

    sparse_array.emplace_at(0);
    // sparse_array.insert_at(0, Entity());
    // sparse_array.insert_at(1, Entity());
    std::cout << sparse_array.size() << std::endl;
    return 0;
}
