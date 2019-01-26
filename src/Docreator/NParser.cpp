//© 2018 NIREX ALL RIGHTS RESERVED

#include "NParser.h"

// ["name": name, "type": type]
NameType NParser::ParseMember(const std::string& instr)
{
	std::map<std::string, std::string> retmap;

	std::string name = NString::FullTrim(NString::Split(instr, " ")[NString::Split(instr, " ").size() - 1]);
	std::string type = NString::FullTrim(NString::Split(instr, name)[0]);

	retmap.emplace("name", name);
	retmap.emplace("type", type);

	return retmap;
}

// ["name": name, "type": type, "inputs": inputs]
NameType NParser::ParseFunction(const std::string& instr)
{
	std::map<std::string, std::string> retmap;

	std::string inputs = NString::Split(instr, "(")[NString::Split(instr, "(").size() - 1];
	inputs =  "(" + inputs;

	std::string basic = NString::FullTrim(NString::Split(instr, inputs)[0]);
	std::string name = NString::FullTrim(NString::Split(basic, " ")[NString::Split(basic, " ").size() - 1]);
	std::string type = NString::FullTrim(NString::Split(basic, name)[0]);

	retmap.emplace("name", name);
	retmap.emplace("type", type);
	retmap.emplace("inputs", inputs);

	return retmap;
}
