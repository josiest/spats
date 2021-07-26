nearest_within
==============

.. doxygenfunction:: spatula::kdtree::nearest_within

Example
-------

.. literalinclude:: ../../../examples/docs/nearest_within_example.cpp
   :language: cpp

Potential output:

.. code-block:: console

   generated points: {{-22.3244, 38.9879}, {-11.6032, 42.3648}, {-1.40496, -21.0138}, {-8.27851, 48.502}, {-27.0511, 17.4109}}
   closest to {-11.6281, 10.6219}: {{-27.0511, 17.4109}}
   3 closest to {-11.6281, 10.6219}: {{-27.0511, 17.4109}, {-22.3244, 38.9879}, {-11.6032, 42.3648}}
   20 closest to {-11.6281, 10.6219}: {}
   3 L1-closest to {-11.6281, 10.6219}: {{-27.0511, 17.4109}, {-11.6032, 42.3648}, {-22.3244, 38.9879}}
