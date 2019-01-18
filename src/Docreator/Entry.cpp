// © 2018 NIREX ALL RIGHTS RESERVED

#include "NString.h"
#include "NFile.h"

#include "NDocData.h"
#include "NFile.h"

void Parse(std::string path);
std::string Process(std::vector<NDocData> data);

auto main(int argc, char** argv) -> int
{
	
	return false;
}

void Parse(std::string path)
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
}

std::string Process(std::vector<NDocData> data)
{
	return "";
}