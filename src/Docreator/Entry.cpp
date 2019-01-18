// © 2018 NIREX ALL RIGHTS RESERVED

#include "NString.h"
#include "NFile.h"
#include "NDocData.h"
#include "NFile.h"
#include <iostream>
#include <Windows.h>

std::string Parse(std::string path);
std::string Process(std::vector<NDocData> data);
std::vector<std::string> GetFiles(std::string folder);

auto main(int argc, char** argv) -> int
{
	if (argc == 1)
	{
		return 1;
	}

	if (argc == 2)
	{
		std::string path = argv[2];
		std::vector<std::string> paths = GetFiles(path);
	
		for (const auto& p : paths)
		{
			if (NString::SplitNoEmpty(p, ".")[1] == "h" || NString::SplitNoEmpty(p, ".")[1] == "cpp")
			{
				std::string mdData = Parse(p);
				NFile::WriteAllText(NString::ToUpper(NString::SplitNoEmpty(p, ".")[0]) + ".MD", mdData);
			}
		}
	}

	return false;
}

std::string Parse(std::string path)
{
	std::string allText = NFile::ReadAllText(path);
	std::string MarkDown = "";

	// //-->DOC_CLASS
	// // DESCRIPTION
	// class X
	// {
	std::vector<NDocData> ClassDoc;
	std::vector<std::string> ClassData = NString::SplitNoEmpty(allText, "//-->DOC_CLASS");
	for (size_t i = 1; i < ClassData.size(); i++)
	{
		ClassDoc.push_back(NDocData());
		ClassDoc[i].lines = NString::ToVector(NString::SplitNoEmpty(ClassData[i], "{")[0]);
		ClassDoc[i].type = "class";

		ClassDoc[i].ident.Name = NString::SplitNoEmpty(NString::SplitNoEmpty(ClassData[i], "{")[0], "class ")[1];
		ClassDoc[i].ident.Name = NString::FullTrim(ClassDoc[i].ident.Name);

		ClassDoc[i].ident.Type = ClassDoc[i].type;
		ClassDoc[i].ident.Type = NString::FullTrim(ClassDoc[i].ident.Type);
	}
	MarkDown += Process(ClassDoc);
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
	std::vector<std::string> FuncData = NString::SplitNoEmpty(allText, "//-->DOC_FUNC");
	for (size_t i = 1; i < FuncData.size(); i++)
	{
		FuncData[i] = NString::SplitNoEmpty(FuncData[i], "{")[0];

		FuncDoc.push_back(NDocData());
		FuncDoc[i].lines = NString::ToVector(NString::SplitNoEmpty(FuncData[i], "{")[0]);
		FuncDoc[i].type = "function";

		FuncDoc[i].ident.Name = NString::SplitNoEmpty(NString::SplitNoEmpty(FuncData[i], "(")[0], " ")[1];
		FuncDoc[i].ident.Name = NString::FullTrim(FuncDoc[i].ident.Name);

		FuncDoc[i].ident.Type = NString::SplitNoEmpty(NString::SplitNoEmpty(FuncData[i], "(")[0], " ")[0];
		FuncDoc[i].ident.Type = NString::FullTrim(FuncDoc[i].ident.Type);
	}
	MarkDown += Process(FuncDoc);
	MarkDown += "\n";

	// //-->DOC_STRUCT
	// // DESCRIPTION
	// struct X
	// {
	std::vector<NDocData> StructDoc;
	std::vector<std::string> StructData = NString::SplitNoEmpty(allText, "//-->DOC_STRUCT");
	for (size_t i = 1; i < StructData.size(); i++)
	{
		StructDoc.push_back(NDocData());
		StructDoc[i].lines = NString::ToVector(NString::SplitNoEmpty(StructData[i], "{")[0]);
		StructDoc[i].type = "struct";

		StructDoc[i].ident.Name = NString::SplitNoEmpty(NString::SplitNoEmpty(StructData[i], "{")[0], "struct ")[1];
		StructDoc[i].ident.Name = NString::FullTrim(StructDoc[i].ident.Name);

		StructDoc[i].ident.Type = StructDoc[i].type;
		StructDoc[i].ident.Type = NString::FullTrim(StructDoc[i].ident.Type);
	}
	MarkDown += Process(StructDoc);
	MarkDown += "\n";

	// //-->DOC_MEMBER
	// // DESCRIPTION
	// void* pX;
	std::vector<NDocData> MemberDoc;
	std::vector<std::string> MemberData = NString::SplitNoEmpty(allText, "//-->DOC_MEMBER");
	for (size_t i = 1; i < MemberData.size(); i++)
	{
		MemberDoc.push_back(NDocData());
		MemberDoc[i].lines = NString::ToVector(NString::SplitNoEmpty(MemberData[i], ";")[0]);
		MemberDoc[i].type = "member";

		MemberDoc[i].ident.Name = NString::SplitNoEmpty(NString::SplitNoEmpty(StructData[i], ";")[0], " ")[1];
		MemberDoc[i].ident.Name = NString::FullTrim(MemberDoc[i].ident.Name);

		MemberDoc[i].ident.Type = NString::SplitNoEmpty(NString::SplitNoEmpty(StructData[i], ";")[0], " ")[0];
		MemberDoc[i].ident.Type = NString::FullTrim(MemberDoc[i].ident.Type);
	}
	MarkDown += Process(MemberDoc);
	MarkDown += "\n";

	return MarkDown;
}

std::string Process(std::vector<NDocData> data)
{
	return "";
}

std::vector<std::string> GetFiles(std::string folder)
{
	std::vector<std::string> names;
	std::string search_path = folder + "/*.*";
	WIN32_FIND_DATA fd;
	HANDLE hFind = ::FindFirstFile(search_path.c_str(), &fd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
				names.push_back(fd.cFileName);
			}
		} while (::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}
	return names;
}
