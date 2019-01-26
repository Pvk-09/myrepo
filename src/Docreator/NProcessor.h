//© 2018 NIREX ALL RIGHTS RESERVED

#ifndef _N_PROCESSOR_H_
#define _N_PROCESSOR_H_

#include "NString.h"
#include "NDocData.h"

class NProcessor
{
public:
	std::string Process(std::vector<NDocData> data);
	std::string FunctionProcess(std::vector<NDocData> data);
};

#endif // !_N_PROCESSOR_H_
