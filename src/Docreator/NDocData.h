// © 2018 NIREX ALL RIGHTS RESERVED

#ifndef _N_DOCDATA_H_
#define _N_DOCDATA_H_

#include <string>
#include <vector>
#include "NIdent.h"

struct NDocData
{
	std::vector<std::string> lines;
	std::string type;
	NIdent ident;
};

#endif //!_N_DOCDATA_H_