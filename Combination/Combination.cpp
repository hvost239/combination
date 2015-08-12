// Combitation.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SimpleCnk.h"
#include "MultithreadCnkSolver.h"

#include <iostream>
#include <boost\multiprecision\cpp_int.hpp>



typedef boost::multiprecision::cpp_int T;

int _tmain(int argc, char* argv[])
{	
	if (argc < 3){
		std::cout << "Not enough input params";
		return -1;
	}

	try{
		T n = boost::lexical_cast<T>(argv[1]);
		T k = boost::lexical_cast<T>(argv[2]);

		MultiThreadCnkSolver<T> solver(2);

		auto result = solver(n, k);
		std::cout << result;
	}
	catch (boost::bad_lexical_cast&){
		std::cout << "Input params is not a number";
		return -1;
	}
	catch (std::invalid_argument& ex) {
		std::cout << "Error: " << ex.what();
		return -1;
	}
	
	return 0;
}



