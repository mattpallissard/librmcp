=======
librmcp
=======

.. image:: https://travis-ci.org/mattpallissard/librmcp.svg?branch=master
    :target: https://travis-ci.org/mattpallissard/librmcp

.. image:: https://codecov.io/gh/mattpallissard/librmcp/branch/master/graph/badge.svg
    :target: https://codecov.io/gh/mattpallissard/librmcp


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


development
===========


There is a `clang-tidy` file as well as a symlink to `build/compile_commands.json` for use with editors/lsp/clangd.

There is also a `clang-format`


todo
====

1. docment what's here
2. finish this todo...
