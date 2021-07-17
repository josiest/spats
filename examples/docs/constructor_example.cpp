#include "spatula/kdtree.hpp"
#include <vector>

int main()
{
    // define some useful aliases
    namespace sp = spatula;
    using point = std::vector<int>;

    // create the point set to be used for the k-d tree
    std::vector<point> points{point{0, 0}};

    // create tree from iterators
    // note: we must specify the type because C++ doesn't know to deduce the
    //  underlying type from iterators
    {
        sp::kdtree<point> index(points.begin(), points.end());
    }
    // create tree from vector
    // note: on the other hand, using a vector, we can deduce the type
    {
        sp::kdtree index(points);
    }
}
