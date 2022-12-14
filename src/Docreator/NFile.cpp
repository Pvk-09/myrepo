//? 2018 NIREX ALL RIGHTS RESERVED

#include "NWin.h"
#include "NFile.h"

std::string NFile::ReadAllText(std::string file)
{
	std::ifstream f(file.c_str());

	std::string str = "";
	std::string outstr = "";
	int iter = 0;
	while (std::getline(f, str))
	{
		iter++;
		outstr += str;
		outstr += 10;
	}
	f.close();
	return outstr;
}

int NFile::WriteAllText(std::string file, std::string str)
{
	std::ofstream f;
	f.open(file);
	f << str;
	f.close();
	return 0;
}

std::vector<std::string> NFile::ReadAllLines(std::string file)
{
	std::ifstream f(file.c_str());
	std::vector<std::string> retv;

	std::string str = "";
	while (std::getline(f, str))
	{
		retv.push_back(str);
	}

	f.close();
	return retv;
}

int NFile::WriteAllLines(std::string file, std::vector<std::string> vecstr)
{
	std::ofstream f;
	f.open(file);

	for (size_t i = 0; i < vecstr.size(); i++)
	{
		f << vecstr[i];
		f << std::endl;
	}

	f.close();
	return 0;
}

std::vector<char> NFile::ReadAllBytes(std::string fileName)
{
	std::ifstream ifs(fileName, std::ios::binary | std::ios::ate);
	std::ifstream::pos_type pos = ifs.tellg();

	std::vector<char> result((const unsigned int)pos);

	ifs.seekg(0, std::ios::beg);
	ifs.read(&result[0], pos);

	return result;
}

int NFile::WriteAllBytes(std::string fileName, std::vector<char> vecBytes)
{
	std::ofstream ofs(fileName, std::ios::binary | std::ios::out);

	ofs.write(vecBytes.data(), vecBytes.size());

	if (ofs.bad()) //bad() function will check for badbit
	{
		return 1;
	}

	ofs.close();
	return 0;
}

std::int32_t NFile::FindFirst(std::string file, std::string val)
{
	std::ifstream f(file.c_str());

	std::string str = "";
	int iter = 0;
	while (std::getline(f, str))
	{
		if (val == str)
		{
			return iter;
		}
		iter++;
	}
	f.close();
	return -1;
}

std::vector<int32_t> NFile::FindAll(std::string file, std::string val)
{
	std::ifstream f(file.c_str());
	std::vector<int32_t> retv;

	std::string str = "";
	int iter = 0;

	while (std::getline(f, str))
	{
		if (val == str)
		{
			retv.push_back(iter);
		}
		iter++;
	}

	f.close();
	return retv;
}

bool NFile::SafeFread(void* buffer, int size, int number, FILE* fp)
{
	using namespace std;
	int ItemsRead;
	if (feof(fp))
	{
		return false;
	}
	ItemsRead = (int)fread(buffer, size, number, fp);
	if (ItemsRead < number)
	{
		return false;
	}
	return true;
}

bool NFile::SafeFWrite(void* buffer, int size, int number, FILE* fp)
{
	if (fwrite(buffer, size, number, fp) == number)
	{
		return false;
	}
	return true;
}

std::vector<std::string> NFile::GetFiles(std::string folder)
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
	