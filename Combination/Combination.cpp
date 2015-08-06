// Combitation.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SimpleCnk.h"



int _tmain(int argc, _TCHAR* argv[])
{
	SimpleCnk<int> solver;
	
	auto result = solver(1, 1);
	return 0;
}

