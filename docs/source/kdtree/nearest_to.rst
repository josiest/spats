nearest_to
==========

.. doxygenfunction:: spatula::kdtree::nearest_to

Example
-------

.. literalinclude:: ../../../examples/docs/nearest_to_example.cpp
   :language: cpp

Potential output:

.. code-block:: console

   generated points: {{-42, -14}, {42, 5}, {20, -9}, {49, 6}, {14, 39}}
   closest to {26, 17}: {{42, 5}}
   3 closest to {26, 17}: {{42, 5}, {14, 39}, {49, 6}}
   20 closest to {26, 17}: {{42, 5}, {14, 39}, {49, 6}, {20, -9}, {-42, -14}}
   3 L1-closest to {26, 17}: {{42, 5}, {20, -9}, {49, 6}}
