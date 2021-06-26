#ifndef SPATULA_KDTREE_HPP
#define SPATULA_KDTREE_HPP

// templates
#include <type_traits>

// resource handlers
#include <vector>
#include <memory>
#include <string>

// utilities
#include <limits>
#include <stdexcept>

// functional interface/algorithms
#include <algorithm>

#ifdef DEBUG
#include <catch2/catch.hpp>
#include "util.hpp"
#endif

namespace spatula {

/**
 * A simple kd-tree implementation.
 *
 * The generic point class should implement `std::size` and `operator[]` for as
 * many dimensions as `std::size` returns.
 */
template<class point>
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
            auto by_axis = [&axis](point const & a, point const & b) {
                return a[axis] < b[axis];
            };
            std::sort(points.begin(), points.end(), by_axis);

            // the current node is the middle of the sorted points
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

    /* Abstraction Function
     *
     * - a tree where each node represents a point in a space
     *
     * - the axis associated with the depth of a node is defined as depth mod d,
     *   where d is the dimension of the point space and it defines the normal
     *   to a plane that bisects the bounding box of all the node's children
     */

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

    // find the nearest k points to p
    //  assumes q is not null, k is positive, r is either null or positive
    template<typename distance_fn>

    auto nearest_to(point const & p, node * q,
                    typename std::decay<decltype(p[0])>::type r,
                    distance_fn distance,
                    size_t depth, size_t k) const

        -> std::vector<std::pair<
               point, typename std::decay<decltype(p[0])>::type
           >>
    {
        check_rep();
#ifdef DEBUG
        if (!q) {
            UNSCOPED_INFO("q is null");
        }
        if (k <= 0) {
            UNSCOPED_INFO("k is not positive");
        }
        if (r <= 0) {
            UNSCOPED_INFO("r is not positive");
        }
#endif
        // define the match type and how to compare/reduce them
        using num_t = typename std::decay<decltype(p[0])>::type;
        using match_t = std::pair<point, num_t>;
        auto cmp_by_distance = [](match_t const & a, match_t const & b) {
            return a.second < b.second;
        };
        auto reduce_by_distance = [](match_t const & p, num_t dist) {
            return p.second < dist;
        };

        // define nearest to originally be empty
        std::vector<match_t> nearest;

        // compute the current distance
        match_t current{q->data, distance(p, q->data)};

        // if r is max value then we don't care about being witihin radius
        //  so default to true
        bool within_radius = true;
        if (r < std::numeric_limits<num_t>::max()) {
            // otherwise check if current distance is within radius

            // r is given as a normal radius
            //  in order to make a comparison using the specified norm
            //  we'll compute the distance between the origin
            //  and a point on the surface of the sphere of radius r
            point const origin = {0};
            point surface = {0};
            surface[0] = r;

            within_radius = current.second < distance(origin, surface);
        }

        // base case: no children - add current to nearest if within radius
        if (!q->left && within_radius) {
            nearest.push_back(current);
        }
        if (!q->left) { // then return the current matches
            return nearest;
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
        if (preferred) {
            nearest = nearest_to(p, preferred, r, distance, depth+1, k);
        }
        num_t preferred_best = std::numeric_limits<num_t>::max();
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

            auto other_nearest = nearest_to(p, other, r, distance, depth+1, k);

            // merge the two nearest vectors
            nearest.reserve(nearest.size() + other_nearest.size());
            nearest.insert(nearest.end(),
                           other_nearest.begin(), other_nearest.end());

            // sort by distance 
            std::sort(nearest.begin(), nearest.end(), cmp_by_distance);

            // remove any extra values
            if (nearest.size() > k) {
                nearest.erase(nearest.begin() + k, nearest.end());
            }
        }

        // find appropriate place to insert
        auto it = std::lower_bound(nearest.begin(), nearest.end(),
                                   current.second, reduce_by_distance);

        // if current best is not good enough but there aren't enough nearest
        // values yet, just add current and return
        if (it == nearest.end() && nearest.size() < k && within_radius) {
            nearest.push_back(current);
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
public:
    /**
     * Create a kdtree from an iterator of points.
     *
     * @param begin pointer to the first point.
     * @param end   pointer past the last point.
     *
     * @throw std::invalid_argument if any item has inconsistent dimensions.
     *
     * Example:
     *
     * @code{.cpp}
     * // alias the point class we're using
     * using point = std::vector<int>;
     *
     * // define the points to use
     * std::vector<point> points;
     * points.push_back(point{0, 0});
     *
     * // create the kdtree
     * namespace sp = spatula;
     * sp::kdtree<point> index(points.begin(), points.end());
     * @endcode
     */
    template<class InputIt>
    kdtree(InputIt begin, InputIt end)
    {
        // if no points, leave root as null
        if (begin == end) {
            return;
        }
        root = std::make_unique<node>(std::vector<point>(begin, end), 0);
        check_rep();
    }
    /**
     * Create a kdtree from a vector of points.
     *
     * @param points the points to intialize the kdtree with.
     *
     * @throw std::invalid_argument if any item has inconsistent dimensions.
     *
     * Example:
     *
     * @code{.cpp}
     * // alias the point class we're using
     * using point = std::vector<int>;
     *
     * // define the points to use
     * std::vector<point> points;
     * points.push_back(point{0, 0});
     *
     * //create the kdtree
     * namespace sp = spatula;
     * sp::kdtree index(points);
     * @endcode
     */
    kdtree(std::vector<point> const & points)
        : kdtree<point>(points.begin(), points.end()) {}

    /**
     * Find the nearest k points to p.
     *
     * @param p         the point to compare to.
     * @param distance  computes the distance between two points.
     * @param k         the maximum number of points to return.
     *
     * @throw std::invalid_argument if p has a different dimension than the
     *        points in the tree.
     *
     * @return  the k points nearest to p.
     *
     *  If the tree has less than k points, then as many points as are
     *  in the tree will be returned.
     *
     *  The returned points will be sorted in order of nearest to p.
     */
    template<typename distance_fn>
    std::vector<point> nearest_to(point const & p, distance_fn distance,
                                  size_t k = 1) const
    {
        check_rep();
        // base case: k = 0 or root is null - return an empty vector
        if (k == 0 || !root) {
            return std::vector<point>();
        }
        // otherwise call recursive search

        // since radius isn't specified for nearest_to, defualt to max possible
        using num_t = typename std::decay<decltype(p[0])>::type;
        auto const max_radius = std::numeric_limits<num_t>::max();

        auto nearest_matches =
            nearest_to(p, root.get(), max_radius, distance, 0, k);

        // convert match vector to point vector
        std::vector<point> nearest;
        nearest.reserve(nearest_matches.size());

        using match_t = std::pair<point, num_t>;
        auto to_point = [](match_t const & match) { return match.first; };

        std::transform(nearest_matches.begin(), nearest_matches.end(),
                       std::back_inserter(nearest), to_point);

        return nearest;
    }

    /**
     * Find the nearest k points to p within radius r.
     *
     * @param p         the point to compare to.
     * @param distance  computes the distance between two points.
     * @param r         the radius to find points within.
     * @param k         the maximum number of points to return.
     *
     * @throw std::invalid_argument if r is not positive and if p is not
     *                              the same dimension as the points in the tree.
     *
     * @return  the k points nearest to p within r radius of p
     *
     *  If the tree has less than k points, or if there are fewer than
     *  k points within r radius of p, then as many points as
     *  there are that satisfy those conditions will be returned.
     *
     *  The returned points will be sorted in order of nearest to p.
     */
    template<typename distance_fn>
    std::vector<point>
    nearest_within(point const & p, distance_fn distance,
                   typename std::decay<decltype(p[0])>::type r,
                   size_t k = 1) const
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
        auto nearest_matches = nearest_to(p, root.get(), r, distance, 0, k);

        // convert match vector to point vector
        std::vector<point> nearest;
        nearest.reserve(nearest_matches.size());

        // alias the underlying number type for the point
        using num_t = typename std::decay<decltype(p[0])>::type;
        using match_t = std::pair<point, num_t>;
        auto to_point = [](match_t const & match) { return match.first; };

        std::transform(nearest_matches.begin(), nearest_matches.end(),
                       std::back_inserter(nearest), to_point);

        return nearest;
    }
};
}

#endif
