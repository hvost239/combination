// Combitation.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SimpleCnk.h"
#include "MultithreadCnkSolver.h"

#include <iostream>
#include <boost\multiprecision\cpp_int.hpp>

int _tmain(int argc, char* argv[])
{	
	if (argc < 3){
		std::cout << "Not enoug input params";
		return -1;
	}

	try{
		boost::multiprecision::cpp_int n = boost::lexical_cast<boost::multiprecision::cpp_int>(argv[1]);
		boost::multiprecision::cpp_int k = boost::lexical_cast<boost::multiprecision::cpp_int>(argv[2]);

		MultiThreadCnkSolver<boost::multiprecision::cpp_int> solver(2);

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



