// © 2018 NIREX ALL RIGHTS RESERVED

#include "NWin.h"
#include <iostream>
#include <map>

#include "NParser.h"
#include "NString.h"
#include "NFile.h"
#include "NDocData.h"
#include "NFile.h"
#include "NProcessor.h"

bool FileValidation(const std::string& ext);
std::string Parse(std::string path);

auto main(int argc, char** argv) -> int
{
	UNREFERENCED_PARAMETER(argc);
	UNREFERENCED_PARAMETER(argv);
A:
	std::string cmd;
	std::cout << "Enter command: ";
	std::cin >> cmd;

	if (NString::ToLower(cmd) == "doc")
	{
		std::string path;
		std::cout << "Enter the path: ";
		std::cin >> path;

		std::vector<std::string> paths = NFile::GetFiles(path);

		for (const auto& p : paths)
		{
			std::string ext = "";
			std::vector<std::string> fullVec = NString::Split(p, ".");
			if (fullVec.size() >= 1)
			{
				ext = fullVec[fullVec.size() - 1];
				if (FileValidation(ext))
				{
					std::string mdData = Parse(path + "\\" + p);
					if (mdData != "E")
					{
						NFile::WriteAllText(path + "\\" + NString::Split(p, ".")[0] + ".MD", mdData);
					}
				}
			}
		}
	}
	else if (NString::ToLower(cmd) == "index")
	{
		std::string path;
		std::cout << "Enter the path: ";
		std::cin >> path;

		std::vector<std::string> paths = NFile::GetFiles(path);

		for (const auto& p : paths)
		{

		}
	}
	else
	{
		goto A;
	}

	

	return false;
}

// Languages with capability of having a double forward slash (//) comment
bool FileValidation(const std::string& ext)
{
	std::string lExt = NString::ToLower(ext);

	// Uncommon C++ Header files
	if (lExt == "hpp") return true;
	
	// Rare Header files
	else if (lExt == "h++") return true;

	// Rare Header files
	else if (lExt == "hxx") return true;

	// Rare Header files
	else if (lExt == "hh") return true;

	// Normal C++ Header files
	else if (lExt == "h") return true;

	// Any other file
	else return false;
}

std::string Parse(std::string path)
{
	int emptyFlag = 0;
	NParser* parser = new NParser();
	NProcessor* processor = new NProcessor();

	std::string allText = NFile::ReadAllText(path);
	std::string MarkDown = "";

	// //-->DOC_CLASS
	// // DESCRIPTION
	// class X
	// {
	std::vector<NDocData> ClassDoc;
	std::vector<std::string> ClassData = NString::Split(allText, "//-->DOC_CLASS");

	for (size_t i = 1; i < ClassData.size(); i++)
	{
		NDocData nDocData;

		nDocData.lines = NString::ToVector(NString::Split(ClassData[i], "{")[0]);
		std::string lastLine = nDocData.lines[nDocData.lines.size() - 1];

		if (NString::FullTrim(lastLine) == "")
		{
			nDocData.lines.erase(nDocData.lines.begin() + nDocData.lines.size() - 1);
		}

		std::map<std::string, std::string> ntData = parser->ParseClass(nDocData.lines[nDocData.lines.size() - 1]);

		nDocData.type = NString::FullTrim(ntData["type"]);
		nDocData.ident.Name = NString::FullTrim(ntData["name"]);
		nDocData.code = nDocData.lines[nDocData.lines.size() - 1];

		ClassDoc.push_back(nDocData);
	}

	if (ClassData.size() > 1)
	{
		MarkDown += "**CLASSES:**\n";
		MarkDown += "============\n";
	}
	else emptyFlag++;

	MarkDown += processor->Process(ClassDoc);

	if (ClassData.size() > 1)
	{
		MarkDown += "----------\n";
	}

	// //-->DOC_FUNC
	// // DESCRIPTION
	// // Input 1
	// // Input 2
	// // Input 3
	// // Output
	// int X(int a, int b, int c)
	// {
	std::vector<NDocData> FuncDoc;
	std::vector<std::string> FuncData = NString::Split(allText, "//-->DOC_FUNC");
	for (size_t i = 1; i < FuncData.size(); i++)
	{
		NDocData nDocData;

		nDocData.lines = NString::ToVector(NString::SplitNoEmpty(FuncData[i], ";")[0]);

		std::string lastLine = nDocData.lines[nDocData.lines.size() - 1];

		if (NString::FullTrim(lastLine) == "")
		{
			nDocData.lines.erase(nDocData.lines.begin() + nDocData.lines.size() - 1);
		}

		std::map<std::string, std::string> ntData = parser->ParseFunction(nDocData.lines[nDocData.lines.size() - 1]);

		nDocData.ident.Name = ntData["type"] + " " + ntData["name"] + " " + ntData["inputs"];
		nDocData.type = "function";
		nDocData.code = nDocData.lines[nDocData.lines.size() - 1];

		FuncDoc.push_back(nDocData);
	}

	if (FuncData.size() > 1)
	{
		MarkDown += "**FUNCTIONS & METHODS:**\n";
		MarkDown += "========================\n";
	}
	else emptyFlag++;

	MarkDown += processor->FunctionProcess(FuncDoc);

	if (FuncData.size() > 1)
	{
		MarkDown += "----------\n";
	}

	// //-->DOC_STRUCT
	// // DESCRIPTION
	// struct X
	// {
	std::vector<NDocData> StructDoc;
	std::vector<std::string> StructData = NString::Split(allText, "//-->DOC_STRUCT");
	for (size_t i = 1; i < StructData.size(); i++)
	{
		NDocData nDocData;

		nDocData.lines = NString::ToVector(NString::Split(StructData[i], "{")[0]);
		std::string lastLine = nDocData.lines[nDocData.lines.size() - 1];

		if (NString::FullTrim(lastLine) == "")
		{
			nDocData.lines.erase(nDocData.lines.begin() + nDocData.lines.size() - 1);
		}

		std::map<std::string, std::string> ntData = parser->ParseStruct(nDocData.lines[nDocData.lines.size() - 1]);

		nDocData.type = NString::FullTrim(ntData["type"]);
		nDocData.ident.Name = NString::FullTrim(ntData["name"]);
		nDocData.code = nDocData.lines[nDocData.lines.size() - 1];

		StructDoc.push_back(nDocData);
	}

	if (StructData.size() > 1)
	{
		MarkDown += "**STRUCTURES:**\n";
		MarkDown += "===============\n";
	}
	else emptyFlag++;

	MarkDown += processor->Process(StructDoc);
	
	if (StructData.size() > 1)
	{
		MarkDown += "----------\n";
	}

	// //-->DOC_MEMBER
	// // DESCRIPTION
	// void* pX;
	std::vector<NDocData> MemberDoc;
	std::vector<std::string> MemberData = NString::Split(allText, "//-->DOC_MEMBER");
	for (size_t i = 1; i < MemberData.size(); i++)
	{
		NDocData nDocData;

		nDocData.lines = NString::ToVector(NString::Split(MemberData[i], ";")[0]);
		nDocData.type = "member";

		std::map<std::string, std::string> ntData = parser->ParseMember(nDocData.lines[nDocData.lines.size() - 1]);

		nDocData.ident.Name = ntData["name"]; 
		nDocData.ident.Type = ntData["type"];
		nDocData.code = nDocData.lines[nDocData.lines.size() - 1];

		MemberDoc.push_back(nDocData);
	}
	
	if (MemberData.size() > 1)
	{
		MarkDown += "**MEMBERS:**\n";
		MarkDown += "============\n";
	}
	else emptyFlag++;

	MarkDown += processor->Process(MemberDoc);
	
	if (MemberData.size() > 1)
	{
		MarkDown += "----------\n";
	}

	MarkDown += "\n###### Generated with [Docreator](https://github.com/nirex0/docreator)";

	delete processor;
	delete parser;

	if (emptyFlag == 4)
	{
		return "E";
	}

	return MarkDown;
}