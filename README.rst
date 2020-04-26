=======
librmcp
=======

an rmpc library based on the IPMI 2.0 spec.

questions, comments, and PR's can be emailed to rmcp a_t pallissard D0T net

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


todo
====

1. docment what's here
2. finish this todo...
