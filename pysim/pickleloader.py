# PickleLoader class
# Loads pickles and stores their data for easy access by an outside class. Intended for use with the
# Boost Python framework.

import pickle

pickle_list = []
pickle_data = {}

def load_pickle(filename):
    """
    Load the pickle at the given filename.
    PARAMETERS:
        filename: the name of the pickle file
    RETURNS: a pointer to the pickle_data field, which is also stored in this class.
    """
    pickle_list.append(filename)
    print("[Python] Loading pickle file: %s..." % (filename))
    with open(filename) as data_file:
        pickle_data[filename] = pickle.load(data_file)
    print("[Python] Finished loading file.")
    print(pickle_data[filename][0])
    return pickle_data[filename]
