#include <iostream>
#include <boost/python.hpp>
#include <Python.h>
#include "sklearn.h"

Sklearn::Sklearn(std::string filename) {
    this->filename = filename;
}
