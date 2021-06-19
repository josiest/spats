#ifndef KDTREE_HPP
#define KDTREE_HPP

#include <vector>

namespace spats {

/**
 * A simple kd-tree implementation
 *
 * The generic point class should implement `std::size` and `operator[]` for as
 * many dimensions as `std::size` returns.
 */
template<class point>
class kdtree {
public:
    template<class InputIt>
    kdtree(InputIt begin, InputIt end)
    {
    }

    /**
     * Find the nearest k points to p
     */
    std::vector<point> nearest_to(point const & p, int k)
    {
    }

    /**
     * Find the nearest k points to p within a given radius
     */
    std::vector<point> nearest_within(point const & p, int k, double r)
    {
    }
};
}

#endif
