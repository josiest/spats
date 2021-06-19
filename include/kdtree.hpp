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
     * Find the nearest k points to p.
     *
     * :param p: the point to compare to
     * :param k: the maximum number of points to return
     *
     * :throws: std::invalid_argument if k is negative
     *
     * If the tree has less than k points, then as many points as are in the
     * tree will be returned.
     *
     * The returned points will be sorted in order of closest to p.
     */
    std::vector<point> nearest_to(point const & p, int k)
    {
        return std::vector<point>();
    }

    /**
     * Find the nearest k points to p within a given radius
     *
     * :param p: the point to compare to
     * :param k: the maximum number of points to return
     * :param r: the radius 
     *
     * :throws: std::invalid_argument if k is negative or if r is not positive
     */
    std::vector<point> nearest_within(point const & p, int k, double r)
    {
        return std::vector<point>();
    }
};
}

#endif
