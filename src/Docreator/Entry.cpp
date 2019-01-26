// © 2018 NIREX ALL RIGHTS RESERVED

#define WIN32_LEAN_AND_MEAN
#define NOGDICAPMASKS
#define NOSYSMETRICS
#define NOMENUS
#define NOICONS
#define NOSYSCOMMANDS
#define NORASTEROPS
#define OEMRESOURCE
#define NOATOM
#define NOCLIPBOARD
#define NOCOLOR
#define NOCTLMGR
#define NODRAWTEXT
#define NOKERNEL
#define NONLS
#define NOMEMMGR
#define NOMETAFILE
#define NOMINMAX
#define NOOPENFILE
#define NOSCROLL
#define NOSERVICE
#define NOSOUND
#define NOTEXTMETRIC
#define NOWH
#define NOCOMM
#define NOKANJI
#define NOHELP
#define NOPROFILER
#define NODEFERWINDOWPOS
#define NOMCX
#define NORPC
#define NOPROXYSTUB
#define NOIMAGE
#define NOTAPE
#define STRICT

#include <Windows.h>
#include <iostream>
#include <map>

#include "NParser.h"
#include "NString.h"
#include "NFile.h"
#include "NDocData.h"
#include "NFile.h"

std::string Parse(std::string path);
std::string Process(std::vector<NDocData> data);
std::vector<std::string> GetFiles(std::string folder);

auto main(int argc, char** argv) -> int
{
	UNREFERENCED_PARAMETER(argc);
	UNREFERENCED_PARAMETER(argv);

	std::string path;
	std::cout << "Enter the path: ";
	std::cin >> path;

	std::vector<std::string> paths = GetFiles(path);

	for (const auto& p : paths)
	{
		if (NString::Split(p, ".")[1] == "h" || NString::Split(p, ".")[1] == "cpp")
		{
			std::string mdData = Parse(path + "\\" + p);
			NFile::WriteAllText(path + "\\" + NString::ToUpper(NString::Split(p, ".")[0]) + ".MD", mdData);
		}
	}

	return false;
}

std::string Parse(std::string path)
{
	NParser parser;
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
		nDocData.type = "class";
		
		nDocData.ident.Name = NString::Split(NString::Split(ClassData[i], "{")[0], "class ")[1];
		nDocData.ident.Name = NString::FullTrim(nDocData.ident.Name);
		
		nDocData.ident.Type = nDocData.type;
		nDocData.ident.Type = NString::FullTrim(nDocData.ident.Type);

		ClassDoc.push_back(nDocData);
	}
	MarkDown += Process(ClassDoc);
	MarkDown += "----------";
	MarkDown += "\n";

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

		nDocData.lines = NString::ToVector(NString::SplitNoEmpty(FuncData[i], "{")[0]);

		std::string lastLine = nDocData.lines[nDocData.lines.size() - 1];

		if (NString::FullTrim(lastLine) == "")
		{
			nDocData.lines.erase(nDocData.lines.begin() + nDocData.lines.size() - 1);
		}

		std::map<std::string, std::string> ntData = parser.ParseFunction(nDocData.lines[nDocData.lines.size() - 1]);

		nDocData.ident.Name = ntData["type"] + " " + ntData["name"] + " " + ntData["inputs"];
		nDocData.type = "function";

		FuncDoc.push_back(nDocData);
	}
	MarkDown += Process(FuncDoc);
	MarkDown += "----------";
	MarkDown += "\n";

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
		nDocData.type = "struct";

		nDocData.ident.Name = NString::Split(NString::Split(StructData[i], "{")[0], "struct ")[1];
		nDocData.ident.Name = NString::FullTrim(nDocData.ident.Name);

		nDocData.ident.Type = nDocData.type;
		nDocData.ident.Type = NString::FullTrim(nDocData.ident.Type);

		StructDoc.push_back(nDocData);
	}
	MarkDown += Process(StructDoc);
	MarkDown += "----------";
	MarkDown += "\n";

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

		std::map<std::string, std::string> ntData = parser.ParseMember(nDocData.lines[nDocData.lines.size() - 1]);

		nDocData.ident.Name = ntData["name"];  //NString::FullTrim(NString::Split(nDocData.lines[nDocData.lines.size() - 1], " ")[1]);
		nDocData.ident.Type = ntData["type"]; //NString::FullTrim(NString::Split(nDocData.lines[nDocData.lines.size() - 1], " ")[0]);

		MemberDoc.push_back(nDocData);
	}
	MarkDown += Process(MemberDoc);
	MarkDown += "----------";
	MarkDown += "\n";

	MarkDown += "\n###### Made with [Docreator](https://github.com/nirex0/docreator)";
	return MarkDown;
}

std::string Process(std::vector<NDocData> data)
{
	std::string sData = "";
	for (const auto& p : data)
	{
		if (p.type != "function")
		{
			sData += "### **" + NString::ToUpper(p.type) + "**: " + p.ident.Name + "\n\n";
		}
		else
		{
			std::string name = NString::FullTrim(NString::Split(p.ident.Name, "(")[0]);
			name = NString::Split(name, " ")[NString::Split(name, " ").size() - 1];

			sData += "### **" + NString::ToUpper(p.type) + "**: " + NString::FullTrim(name) + "\n\n";
		}

		sData += "``` " + p.ident.Type + " " + p.ident.Name + " ```" + "\n\n";
		for (int i = 1; i < p.lines.size() - 1; i++)
		{
			sData += "" + NString::Split(p.lines[i], "//")[1] + "" + "\n\n";
		}
		sData += "#### **Description:**\n" + NString::Split(p.lines[0],"//")[1] + "\n\n";
	}
	
	return sData;
}

std::vector<std::string> GetFiles(std::string folder)
{
	std::vector<std::string> names;
	std::string search_path = folder + "/*.*";
	
	WIN32_FIND_DATA fd;
	HANDLE hFind = FindFirstFile(search_path.c_str(), &fd);

	if (hFind != INVALID_HANDLE_VALUE) 
	{
		do 
		{
			if (!(fd.dwFileAttributes& FILE_ATTRIBUTE_DIRECTORY)) 
			{
				names.push_back(fd.cFileName);
			}
		} while (FindNextFile(hFind, &fd));
		FindClose(hFind);
	}
	return names;
}