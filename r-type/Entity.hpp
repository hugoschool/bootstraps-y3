#pragma once

#include <cstddef>

class Entity {
    public:
        explicit Entity() : _content(0) {
        }

        ~Entity() {};

        operator std::size_t() const {
            return _content;
        }

    private:
        std::size_t _content;
};
