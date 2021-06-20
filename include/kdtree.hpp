#ifndef KDTREE_HPP
#define KDTREE_HPP

#include <vector>

namespace spats {

/**
 * A function pointer type for distance functions.
 */
template<class point, typename num_t = double>
using distance_fn = num_t(*)(point const &, point const &);

/**
 * Compute the squared distance between two points under the L2 norm
 *
 * :param a: one of the two points to find the distance between
 * :param b: the other of the two points to find the distance between
 *
 * :throws: invalid_argument if a and b size don't match
 *
 * :return: the L2 squared distance between a and b
 */
template<class point, typename num_t>
num_t L2sq(point const & a, point const & b)
{
    if (std::size(a) != std::size(b)) {
        throw std::invalid_argument{"points must be the same dimension!"};
    }
    num_t dist = 0;
    for (int i = 0; i < std::size(a); i++) {
        num_t const e = a[i]-b[i];
        dist += e*e;
    }
    return dist;
}

/**
 * A simple kd-tree implementation
 *
 * The generic point class should implement `std::size` and `operator[]` for as
 * many dimensions as `std::size` returns.
 */
template<class point, typename num_t = double>
class kdtree {
public:
    /**
     * Create a kdtree from an iterator of points.
     *
     * :param begin: pointer to the first point
     * :param end: pointer past the last point
     * :param distance: function to determine the distance between points
     *
     * :throws: `std::invalid_argument` if any item has inconsistent dimensions
     */
    template<class InputIt>
    kdtree(InputIt begin, InputIt end,
           distance_fn<point, num_t> distance)
    {
    }

    /**
     * Find the nearest k points to p.
     *
     * :param p: the point to compare to
     * :param k: the maximum number of points to return
     *
     * :throws:
     * 
     *  std::invalid_argument if k is negative.
     *
     *  std::invalid_argument if p has a different dimension than the points in
     *  the tree.
     *
     * :return: the k points nearest to p
     *
     *  If the tree has less than k points, then as many points as are in the
     *  tree will be returned.
     *
     *  The returned points will be sorted in order of nearest to p.
     */
    std::vector<point> nearest_to(point const & p, int k) const
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
     * :throws:
     *
     *  std::invalid_argument if k is negative or if r is not positive
     *
     *  std::invlaid_argument if p is not the same dimension as the points in
     *  the tree.
     *
     * :return: the k points nearest to p within r radius of p
     *
     *  If the tree has less than k points, or if there are fewer than k points
     *  within r radius of p, then as many points as there are that satisfy
     *  those conditions will be returned.
     *
     *  The returned points will be sorted in order of nearest to p.
     */
    std::vector<point> nearest_within(point const & p, int k, num_t r) const
    {
        return std::vector<point>();
    }
};
}

#endif
