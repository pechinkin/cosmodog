#pragma once

#include <iostream>
#include <TerminalColors.hpp>

namespace csd
{
	#define SCOPE_DUMP auto dumper__ = csd::Dumper{*this, __PRETTY_FUNCTION__};

struct Dumpable
{
	virtual void dump() const = 0;
};

class Dumper
{
	const Dumpable& dumpy_;
	const std::string funcName_;

public:

	Dumper(const Dumpable& dumpy, const std::string& funcName);

	~Dumper();
};

Dumper::Dumper(const Dumpable& dumpy, const std::string& funcName)
:
	dumpy_{dumpy},
	funcName_{funcName}
{
	std::cout << GREEN << "\t[!!!] Enter " << funcName_ << "\n\n" << RESET;

	dumpy_.dump();
}

Dumper::~Dumper()
{
	std::cout << RED << "\t[!!!] Leave " << funcName_ << "\n\n" << RESET;

	dumpy_.dump();
}

};