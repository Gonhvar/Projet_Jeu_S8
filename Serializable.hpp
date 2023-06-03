#ifndef SERIALIZABLE_HPP
#define SERIALIZABLE_HPP

#include "Inc.hpp"

class Serializable {
public:
	virtual std::string serialize(std::string& toWrite) = 0;
    virtual void deSerialize(std::string& toRead) = 0;
};

#endif