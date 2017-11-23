#ifndef PICKLELOAD_H
#define PICKLELOAD_H

#include <map>
#include <boost/python.hpp>
#include <Python.h>

#include "pyutils.h"

struct _PickleData {
    // Whether this structure has been initialized
    bool initialized;

    // Information for a row of data from the pickle file
    int elapsedTime;
    bool isWrite;
    std::string fileName;
    int diskNum;
    int size;
};
typedef struct _PickleData PickleData;

class PickleLoader {
public:
    PickleLoader();

    PickleData itemAtIndex(std::string pickleFile, int index);

    int loadPickle(std::string pickleFile);

private:
    // Python-callable attributes and functions:
    py::object pickleloader;
    py::object load_pickle;
    std::vector<std::string> pickle_list;
    std::map<std::string, py::list> pickle_data;
};


#endif
