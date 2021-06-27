.. spatula documentation master file, created by
   sphinx-quickstart on Fri Jun 25 23:30:18 2021.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

spatula: spatial searching
==========================

`spatula` is a C++ library that provides spatial partitioning data structures
that are simple and easy to use. Spatial partitioning data structures organize
sets of points so that searching can implemented efficiently. Spatula currently
only provides a `k-d tree <https://en.wikipedia.org/wiki/K-d_tree>`_ data
structure, which is a good fit for low-dimensional data.

Spatial searching algorithms are useful in many contexts. In video games they're
often used to implement collision detection. Perhaps the most notable use is in
machine learning and robotics - but that's beyond the scope of this library. The
data-structures that spatula provides aren't designed to be optimized for large
amounts of data; the main motivation behind spatula is ease of use. If your
project requires more optimization, consider using
`nanoflann <https://github.com/jlblancoc/nanoflann>`_.

Data Structures
---------------
spatial-partitioning data structures that implement spatial searching

.. toctree::
   :maxdepth: 2

   kdtree.rst

Geometric Utilities
-------------------
geometric classes and functions useful for spatial searching 

.. toctree::
   :maxdepth: 2

   geometry.rst

Indices and tables
------------------

* :ref:`genindex`
* :ref:`modindex`
* :ref:`search`
