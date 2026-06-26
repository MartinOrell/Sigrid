#pragma once

#include <vector>
#include <optional>
#include <functional> //Reference wrapper

namespace sigrid{

    template <typename T> class SigridVector{

        public:
            SigridVector();

            void push_back(const T& value);

            std::optional<std::reference_wrapper<T>> at(const unsigned int& position);
            const std::optional<std::reference_wrapper<const T>> at(const unsigned int& position) const;
            std::optional<std::reference_wrapper<T>> at(const int& position);
            const std::optional<std::reference_wrapper<const T>> at(const int& position) const;

            unsigned int size() const;

        private:

            std::vector<T> m_vector;
    };
}