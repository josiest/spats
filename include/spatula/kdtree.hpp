#ifndef SPATULA_KDTREE_HPP
#define SPATULA_KDTREE_HPP

// resource handlers
#include <vector>
#include <memory>
#include <optional>
#include <string>

// utilities
#include <limits>
#include <stdexcept>

// functional interface/algorithms
#include <algorithm>

#define DEBUG
#ifdef DEBUG
#include <catch2/catch.hpp>
#include "util.hpp"
#endif

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
    for (size_t i = 0; i < std::size(a); i++) {
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
        point data;
        std::unique_ptr<node> left;
        std::unique_ptr<node> right;

        // create a node from a point vector
        // assumes points is non-empty and no points have been added before
        node(std::vector<point> points, size_t depth)
        {
#ifdef DEBUG
            if (points.empty()) {
                UNSCOPED_INFO("points is empty in node constructor");
            }
#endif
            // sort points by current axis
            size_t const axis = depth % std::size(points.back());
            std::sort(points.begin(), points.end(),
                      [&axis](point const & a, point const & b) {
                return a[axis] < b[axis];
            });

            size_t const median = points.size()/2;
            data = points[median];

            // base case one point - left and right are left as null
            if (points.size() == 1) {
                return;
            }
            // compare the front and last element dimensions to current
            bool const front_consistent =
                std::size(points.front()) == std::size(data);
            bool const back_consistent =
                std::size(points.back()) == std::size(data);

            // if they're not consistent it breaks the algorithm: throw error
            if (!front_consistent || !back_consistent) {
                std::string message{"all points must have the same dimension"};
                throw std::invalid_argument{message};
            }

            // split points by the median and set the left and right nodes
            std::vector<point> left_points(points.begin(),
                                           points.begin() + median);
            if (!left_points.empty()) {
                left = std::make_unique<node>(left_points, depth + 1);
            }

            std::vector<point> right_points(points.begin() + median + 1,
                                            points.end());
            if (!right_points.empty()) {
                right = std::make_unique<node>(right_points, depth + 1);
            }
        }
    };

    /* Representation Invariant
     *
     * - all points p have the same dimension given by std::size(p)
     * - if i < std::size(p) then p[i] accesses the i^th element of p
     *
     * - let d be the axis associated with the depth of a point q. Then if a
     *   point p is a child of q, p[d] <= q[d] only if p is on q's left branch.
     *   otherwise p is on q's right branch.
     *
     * - no points appear twice in the tree
     */
    std::unique_ptr<node> root;
    distance_fn<point, num_t> distance;

    /* Abstraction Function
     *
     * - a tree where each node represents a point in a space
     *
     * - the axis associated with the depth of a node is defined as depth mod d,
     *   where d is the dimension of the point space and it defines the normal
     *   to a plane that bisects the bounding box of all the node's children
     */

    // find the nearest k points to p
    //  assumes q is not null, k is positive, r is either null or positive
    std::vector<std::pair<point, num_t>>
    nearest_to(point const & p, node * q, size_t depth,
               std::optional<num_t> r, size_t k) const
    {
        check_rep();
#ifdef DEBUG
        if (!q) {
            UNSCOPED_INFO("q is null");
        }
        if (k <= 0) {
            UNSCOPED_INFO("k is not positive");
        }
        if (r && *r <= 0) {
            UNSCOPED_INFO("r is not positive");
        }
#endif
        // compute the current distance
        using match_t = std::pair<point, num_t>;
        match_t current{q->data, distance(p, q->data)};

        // base case: no children
        if (!q->left) {

            // if radius specified and current is out of bounds return empty
            if (r && current.second < (*r)*(*r)) {
                return std::vector<match_t>();
            }
            return std::vector<match_t>{current};
        }
        size_t const axis = depth % std::size(p);
        // go left if current axis in p is at most as in q
        node * preferred = q->left.get();
        node * other = q->right.get();
        // go right if current axis in p is greater than in q
        if (p[axis] > q->data[axis]) {
            preferred = q->right.get();
            other = q->left.get();
        }

        // it may be the case that the preffered branch is null
        // if so just skip it and leave nearest as empty
        std::vector<match_t> nearest;
        num_t preferred_best = std::numeric_limits<num_t>::max();

        if (preferred) {
            nearest = nearest_to(p, preferred, depth+1, r, k);
        }
        if (!nearest.empty()) {
            preferred_best = nearest.back().second;
        }
        // if other branch potnentially has closer points, also explore it
        //  in order to find if this premise is true we must intersect the
        //  splitting hyper-plane with a hypersphere of the best distance

        // this means that the best distance should be less than the distance
        // of the search point to the current axis
        num_t const distance_to_axis = std::abs(p[axis] - q->data[axis]);

        // we should also explore the other branch if there are less nearest
        // points than (k - depth) since there will otherwise be at most
        // (nearest.size() + depth) points
        bool const axis_too_far = distance_to_axis >= preferred_best;
        bool const enough_points = nearest.size() + depth >= k;

        // explore if other node exists and
        //     axis isn't too far to have closer points
        //  or not enough points have ben discovered yet
        if (other && (!axis_too_far || !enough_points)) {

            auto other_nearest = nearest_to(p, other, depth+1, r, k);

            // merge the two nearest vectors
            nearest.reserve(nearest.size() + other_nearest.size());
            nearest.insert(nearest.end(),
                           other_nearest.begin(), other_nearest.end());

            // sort by distance
            std::sort(nearest.begin(), nearest.end(),
                      [](match_t const & a, match_t const & b) {
                return a.second < b.second;
            });

            // remove any excess points
            if (nearest.size() > k) {
                nearest.erase(nearest.begin() + k, nearest.end());
            }
        }

        // find appropriate place to insert
        auto it = std::lower_bound(
                nearest.begin(), nearest.end(), current.second,
                [](match_t const & match, num_t distance) {

            return match.second < distance;
        });
        // if current best is not good enough but there aren't enough nearest
        // values yet, just add current and return
        if (it == nearest.end() && nearest.size() < k) {
            nearest.push_back(current);
            return nearest;
        }
        // otherwise if current best isn't good enough just return
        if (it == nearest.end()) {
            return nearest;
        }
        // update best results
        nearest.insert(it, current);
        if (nearest.size() > k) { // remove any excess values
            nearest.erase(nearest.begin() + k, nearest.end());
        }
        return nearest;
    }

    void check_rep(node * p, std::vector<point> & seen, size_t depth) const
    {
#ifdef DEBUG
        // check if std::size(p) gives correct dimension
        // and that p[i] gives i^th element of p
        try {
            for (size_t i = 0; i < std::size(p->data); i++) {
                // may cause segfault or throw exception if i doesn't get i^th
                // element or if std::size gives larger dimension than point
                p->data[i];
            }
        }
        catch (std::exception const & e) {
            UNSCOPED_INFO("Acessing data caused exception: " << e.what());
        }

        // no duplicate nodes
        if (std::find(seen.begin(), seen.end(), p->data) != seen.end()) {
            UNSCOPED_INFO("Duplicate point found: " << p->data);
        }
        seen.push_back(p->data);

        size_t const axis = depth % std::size(p->data);
        if (p->left) {
            // q[d] <= p[d] only if q is a left child of p
            if (p->left->data[axis] > p->data[axis]) {
                UNSCOPED_INFO("Nodes are not sorted correctly");
                UNSCOPED_INFO("  "
                        << p->left->data << " appears before " << p->data
                        << " but " << p->left->data[axis]
                        << " > " << p->data[axis]);
            }
            check_rep(p->left.get(), seen, depth+1);
        }
        if (p->right) {
            // q[d] > p[d] only if q is a right child of p
            if (p->right->data[axis] <= p->data[axis]) {
                UNSCOPED_INFO("Nodes are not sorted correctly");
                UNSCOPED_INFO("  "
                        << p->right->data << " appears after " << p->data
                        << " but " << p->right->data[axis]
                        << " <= " << p->data[axis]);
            }
            check_rep(p->right.get(), seen, depth+1);
        }
#endif
    }

    void check_rep() const
    {
#ifdef DEBUG
        if (!root) {
            return;
        }
        std::vector<point> seen;
        check_rep(root.get(), seen, 0);
        // all points have the same size
        for (auto it = seen.begin(); it != seen.end(); it++) {
            if (std::size(*it) != std::size(seen.front())) {
                UNSCOPED_INFO("point " << *it << " has inconsistent dimension");
            }
        }
#endif
    }
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
        : distance{distance}
    {
        // if no points, leave root as null
        if (begin == end) {
            return;
        }
        root = std::make_unique<node>(std::vector<point>(begin, end), 0);
        check_rep();
    }

    /**
     * Find the nearest k points to p.
     *
     * :param p: the point to compare to
     * :param k: the maximum number of points to return
     *
     * :throws:
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
    std::vector<point> nearest_to(point const & p, size_t k = 1) const
    {
        check_rep();
        // base case: k = 0 or root is null - return an empty vector
        if (k == 0 || !root) {
            return std::vector<point>();
        }
        // otherwise call recursive search
        auto nearest_matches = nearest_to(p, root.get(), 0, std::nullopt, k);

        // convert match vector to point vector
        std::vector<point> nearest;
        nearest.reserve(nearest_matches.size());
        std::transform(nearest_matches.begin(), nearest_matches.end(),
                       std::back_inserter(nearest),
                       [](auto const & match) { return match.first; });

        return nearest;
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
     *  std::invalid_argument if r is not positive
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
    std::vector<point>
    nearest_within(point const & p, num_t r, size_t k = 1) const
    {
        check_rep();
        // r must be positive
        if (r <= 0) {
            throw std::invalid_argument{"r must be positive"};
        }
        // base case: k = 0 or root is null - return an empty vector
        if (k == 0 || !root) {
            return std::vector<point>();
        }
        // otherwise call recursive search
        auto nearest_matches = nearest_to(p, root.get(), 0, r, k);

        // convert match vector to point vector
        std::vector<point> nearest;
        nearest.reserve(nearest_matches.size());
        std::transform(nearest_matches.begin(), nearest_matches.end(),
                       std::back_inserter(nearest),
                       [](auto const & match) { return match.first; });

        return nearest;
    }
};
}

#endif
