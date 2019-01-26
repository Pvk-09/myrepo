//© 2018 NIREX ALL RIGHTS RESERVED

#ifndef _N_PARSER_H_
#define _N_PARSER_H_

#include <map>
#include <vector>
#include <string>
#include "NString.h"

using NameType = std::map<std::string, std::string>;

class NParser
{
public:
	// ["name": name, "type": type]
	NameType ParseMember(const std::string& instr);

	// ["name": name, "type": type, "inputs": inputs]
	NameType ParseFunction(const std::string& instr);

	// ["name": name, "type": "class"]
	NameType ParseClass(const std::string& instr);

	// ["name": name, "type": "struct"]
	NameType ParseStruct(const std::string& instr);
};

#endif // !_N_PARSER_H_
