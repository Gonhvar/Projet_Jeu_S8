#ifndef SERIALIZABLE_HPP
#define SERIALIZABLE_HPP

#include "Inc.hpp"

class Serializable {
public:
	virtual std::string& serialize(std::string& toWrite) {return toWrite;};
    virtual void deSerialize(std::string& toRead) {};
};

#endif