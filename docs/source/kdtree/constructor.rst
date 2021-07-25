kdtree constructor
==================

.. doxygenfunction:: spatula::kdtree::kdtree(InputIt begin, InputIt end)
.. doxygenfunction:: spatula::kdtree::kdtree(std::vector<point> const &points)
.. doxygenfunction:: spatula::kdtree::kdtree(std::initializer_list<point> points)

Example
-------

.. literalinclude:: ../../../examples/docs/constructor_example.cpp
   :language: cpp

Output

.. code-block:: console

   closest to origin: {{0, 0}}
   closest to origin: {{0, 0}, {0, 1}, {1, 0}}
   closest to origin: {{1, -1}, {1, 2}, {5, 6}}
