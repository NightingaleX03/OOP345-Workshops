#ifndef SENECA_COLLECTION_H
#define SENECA_COLLECTION_H

#include <iostream>
#include <string>

namespace seneca {

    template <typename T, unsigned C>
    class Collection {

    private:
        // private member variables
        T m_smallestItem = 9999;
        T m_largestItem = -9999;

        T m_items[C]{};
        unsigned m_size{};
        unsigned m_capacity{ C };

    public:
        Collection() = default;
        auto size() const -> unsigned { return m_size; }
        auto capacity() const -> unsigned { return N; }
        auto operator+=(const T& item) -> Collection& {}
        auto getSmallestItem() const -> const T& {}
        auto getLargestItem() const -> const T& {}
        std::ostream print(std::ostream& os) const;

    template <typename T, unsigned N>
    std::ostream& operator<<(std::ostream& os, const Collection<T, N>& col) {}

    };
} 
#endif // SENECA_COLLECTION_H
