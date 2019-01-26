//© 2018 NIREX ALL RIGHTS RESERVED

#ifndef _N_FILE_H_
#define _N_FILE_H_

#include <string>
#include <fstream>
#include <vector>
#include <iostream>

class NFile final
{
public:
	static std::string ReadAllText(std::string file);
	static int WriteAllText(std::string file, std::string str);
	 
	static std::vector<std::string> ReadAllLines(std::string file);
	static int WriteAllLines(std::string file, std::vector<std::string> vecstr);
	 
	static std::vector<char> ReadAllBytes(std::string fileName);
	static int WriteAllBytes(std::string fileName, std::vector<char> vecBytes);
	 
	static std::int32_t FindFirst(std::string file, std::string val);
	static std::vector<int32_t> FindAll(std::string file, std::string val);
	 
	static bool SafeFread(void* buffer, int size, int number, FILE* fp);
	static bool SafeFWrite(void* buffer, int size, int number, FILE* fp);

	static std::vector<std::string> GetFiles(std::string folder);
};

#endif // !_N_FILE_H_
