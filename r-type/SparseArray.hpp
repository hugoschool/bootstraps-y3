#pragma once

#include <algorithm>
#include <optional>
#include <utility>
#include <vector>

template <typename Component> // You can also mirror the definition of std::vector, that takes an additional allocator.
class SparseArray {
    public:
        using ValueType = std::optional<Component>; // optional component type
        using ReferenceType = ValueType &;
        using ConstReferenceType = ValueType const &;
        using ContainerT = std::vector<ValueType>; // optionally add your allocator template here
        using size_type = typename ContainerT::size_type;
        using iterator = typename ContainerT::iterator;
        using const_iterator = typename ContainerT::const_iterator;

    public:
        SparseArray() : _data() {}; // You can add more constructors.
        SparseArray(SparseArray const &array) : _data(array._data) {};  // copy constructor
        SparseArray(SparseArray &&array) noexcept : _data(std::move(array._data)) {};   // move constructor
        ~SparseArray() {};

        SparseArray &operator=(SparseArray const &array) {  // copy assignment operator
            _data = array._data;
        };
        SparseArray &operator=(SparseArray &&array) noexcept {  // move assignment operator
            _data = std::move(array._data);
        };

        ReferenceType operator[](size_t idx) {
            return _data[idx];
        };
        ConstReferenceType operator[](size_t idx) const {
            return _data[idx];
        };

        iterator begin() {
            return _data.begin();
        };
        const_iterator begin() const {
            return _data.begin();
        };
        const_iterator cbegin() const {
            return _data.cbegin();
        };
        iterator end() {
            return _data.end();
        };

        const_iterator end() const {
            return _data.end();
        };
        const_iterator cend() const {
            return _data.cend();
        };

        size_type size() const {
            return _data.size();
        };

        ReferenceType insert_at(size_type pos, Component const &component) {
            return *_data.insert(begin() + pos, component);
        };
        ReferenceType insert_at(size_type pos, Component &&component) {
            return *_data.insert(begin() + pos, std::move(component));
        };

        template <class... Params>
        ReferenceType emplace_at(size_type pos, Params &&...params) { // optional
            ValueType value = std::make_optional<Component>(std::forward<Params>(params)...);
            return *_data.emplace(begin() + pos, value);
        };

        void erase(size_type pos) {
            _data[pos] = std::nullopt;
        };

        size_type get_index(ValueType const &value) const {
            iterator &it = std::find(begin(), end(), value);

            if (it == end()) {
                return size();
            }
            return std::distance(begin(), value);
        };

    private:
        ContainerT _data;
};
