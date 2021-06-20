#ifndef KDTREE_HPP
#define KDTREE_HPP

#include <vector>
#include <memory>
#include <algorithm>
#include <string>

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
    // can't compute the distance between points in different dimensions
    if (std::size(a) != std::size(b)) {
        throw std::invalid_argument{"points must be the same dimension!"};
    }
    // compute the sum of the squares of the difference
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
private:
    struct node {
        std::unique_ptr<point> value;
        std::unique_ptr<node> left;
        std::unique_ptr<node> right;

        node(std::vector<point> points, int depth)
        {
            // base case no points - leave everything as null
            if (points.size() == 0) {
                return;
            }
            auto const median = points.size()/2;
            value = std::make_unique<point>(points[median]);

            // base case one point - left and right left as null
            if (points.size() == 1) {
                return;
            }
            // base case two points - right left as null
            if (points.size() == 2) {
                left = std::make_unique<node>(
                    std::vector<point>{points[0]}, depth+1
                );
            }

            // sort points by axis
            int const axis = depth % std::size(points.back());
            std::sort(points.begin(), points.end(),
                      [&axis](point const & a, point const & b) {
                return a[axis] < b[axis];
            });

            // split points by the median and set the left and right nodes
            std::vector<point> left_points(points.begin(),
                                           points.begin() + median);
            left = std::make_unique<node>(left_points, depth + 1);

            std::vector<point> right_points(points.begin() + median + 1,
                                            points.end());
            right = std::make_unique<node>(right_points, depth + 1);
        }
    };
    node root;
    distance_fn<point, num_t> distance;
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
        : root(std::vector<point>(begin, end), 0), distance{distance}
    {
        // no points, no need to check they have same size
        if (begin == end) {
            return;
        }
        // ensure that all points have the same size
        point const & p = *begin;
        for (auto it = begin+1; it != end; it++) {
            point const & q = *it;
            if (std::size(p) != std::size(q)) {
                std::string message{"all points must have teh same size!"};
                throw std::invalid_argument{message};
            }
        }
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
