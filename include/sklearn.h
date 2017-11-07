#ifndef SKLEARN_H
#define SKLEARN_H

class Sklearn {
public:
    Sklearn() { }; // Default Constructor

    Sklearn(std::string filename);

    void predict();

private:
    std::string filename;


};

#endif
