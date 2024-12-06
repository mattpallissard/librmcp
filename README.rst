=======
librmcp
=======


A RMCP library based on the IPMI 2.0 spec.

:G
status
======


Right now all that's working is enough basic functionality to run a `ping`.  see `print_ping.c`

building
========

.. code:: sh

  mkdir build
  pushd build
  cmake ..
  cmake --build .
  ctest



work
====


+---------------------+-------------+-----------------------------------------------------+
| item                | status      | notes                                               |
+---------------------+-------------+-----------------------------------------------------+
| authentiction       | in progress | get/set complete work, serialization needs doing    |
+---------------------+-------------+-----------------------------------------------------+
| logging             | to do       | put some polish on the (internal only) debug loggin |
+---------------------+-------------+-----------------------------------------------------+
| protocol            | to do       | maintain state, etc                                 |
+---------------------+-------------+-----------------------------------------------------+
| more robust testing | in progress | maintain state, etc                                 |
+---------------------+-------------+-----------------------------------------------------+
| api                 | to do       | standardize on public /private api                  |
+---------------------+-------------+-----------------------------------------------------+
| issue tracker       | to do       | probably just use github                            |
+---------------------+-------------+-----------------------------------------------------+
