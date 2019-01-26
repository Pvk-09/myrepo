//© 2018 NIREX ALL RIGHTS RESERVED

#include "NProcessor.h"

std::string NProcessor::Process(std::vector<NDocData> data)
{
	std::string sData = "";
	for (const auto& p : data)
	{
		sData += "### **" + NString::ToUpper(p.type) + "**: " + p.ident.Name + "\n\n";
		sData += "``` " + NString::FullTrim(p.code) + " ```" + "\n\n";

		for (int i = 1; i < p.lines.size() - 1; i++)
		{
			sData += "" + NString::Split(p.lines[i], "//")[1] + "" + "\n\n";
		}

		sData += "##### **Description:**" + NString::Split(p.lines[0], "//")[1] + "\n\n";
	}

	return sData;
}

std::string NProcessor::FunctionProcess(std::vector<NDocData> data)
{
	std::string sData = "";
	for (const auto& p : data)
	{
		std::string name = NString::FullTrim(NString::Split(p.ident.Name, "(")[0]);
		name = NString::Split(name, " ")[NString::Split(name, " ").size() - 1];
		sData += "### **" + NString::ToUpper(p.type) + "**: " + NString::FullTrim(name) + "\n\n";
		sData += "``` " + NString::FullTrim(p.code) + " ```" + "\n\n";

		for (int i = 1; i < p.lines.size() - 1; i++)
		{
			sData += "" + NString::Split(p.lines[i], "//")[1] + "" + "\n\n";
		}

		sData += "##### **Description:**" + NString::Split(p.lines[0], "//")[1] + "\n\n";
	}

	return sData;
}
