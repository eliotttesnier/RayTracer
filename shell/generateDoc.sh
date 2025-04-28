#!/bin/bash
rm -rf html
rm -rf doc
doxygen Doxyfile
mv ./doc/html/* ./doc/
rm -rf ./doc/html
