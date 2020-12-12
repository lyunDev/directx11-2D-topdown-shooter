#pragma once
// ./;$(SolutionDir)Framework/;
//#include "../Framework/Framework.h"

#include "Framework.h"
#pragma comment(lib, "Framework.lib")

#ifdef NDEBUG
	#ifdef _DEBUG
		#undef _DEBUG
	#endif
#endif