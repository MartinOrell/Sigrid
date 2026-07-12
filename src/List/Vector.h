#pragma once

#include <vector>
#include <optional>
#include <functional> //Reference wrapper

namespace sigrid{namespace list{

    template <typename T> class Vector{

        public:
            Vector() = default;
            Vector(const Vector&) = default;
            Vector(Vector&&) = default;
            Vector& operator=(const Vector&) = default;
            Vector& operator=(Vector&&) = default;

            void push_back(const T& value);
            void insert(const unsigned int& position, const T& value);
            void pop_back();
            void erase(const unsigned int& position);
            void eraseFrom(const unsigned int& position);
            typename std::vector<T>::iterator erase(const typename std::vector<T>::iterator& iterator);
            void clear();

            std::optional<std::reference_wrapper<T>> front();
            const std::optional<std::reference_wrapper<const T>> front() const;
            std::optional<std::reference_wrapper<T>> back();
            const std::optional<std::reference_wrapper<const T>> back() const;
            std::optional<std::reference_wrapper<T>> at(const unsigned int& position);
            const std::optional<std::reference_wrapper<const T>> at(const unsigned int& position) const;
            std::optional<std::reference_wrapper<T>> at(const int& position);
            const std::optional<std::reference_wrapper<const T>> at(const int& position) const;

            unsigned int size() const;

            typename std::vector<T>::iterator begin();
            typename std::vector<T>::const_iterator begin() const;
            typename std::vector<T>::iterator end();
            typename std::vector<T>::const_iterator end() const;

        private:

            std::vector<T> m_vector;
    };
}}