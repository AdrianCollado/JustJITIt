//===========================================================================//
//                                Just JIT It                                //
//                Implementing your own simple JIT compiler.                 //
//---------------------------------------------------------------------------//
// This file is the entry point for the entire application.                  //
//---------------------------------------------------------------------------//
// Copyright (C) 2017 - Adrian J. Collado                                    //
// All Rights Reserved                                                       //
//---------------------------------------------------------------------------//
// Permission is hereby granted, free of charge, to any person obtaining a   //
// copy of this software and associated documentation files (the             //
// “Software”), to deal in the Software without restriction, including       //
// without limitation the rights to use, copy, modify, merge, publish,       //
// distribute, sublicense, and/or sell copies of the Software, and to permit //
// persons to whom the Software is furnished to do so, subject to the        //
// following conditions:                                                     //
//                                                                           //
// The above copyright notice and this permission notice shall be included   //
// in all copies or substantial portions of the Software.                    //
//                                                                           //
// THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS   //
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF                //
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN //
// NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,  //
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR     //
// OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE //
// USE OR OTHER DEALINGS IN THE SOFTWARE.                                    //
//===========================================================================//
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

// The entry point in "AOT-Naive" operating mode.
extern int MainAN(const std::vector<std::string>& args);
// The entry point in "AOT-Optimized" operating mode.
extern int MainAO(const std::vector<std::string>& args);
// The entry point in "JIT-Naive" operating mode.
extern int MainJN(const std::vector<std::string>& args);
// The entry point in "JIT-Optimized" operating mode.
extern int MainJO(const std::vector<std::string>& args);
// The entry point in "Interpreted-Naive" operating mode.
extern int MainIN(const std::vector<std::string>& args);

int main(int argc, char **argv) {
	// Parse the arguments.
	std::vector<std::string> args(argv + 1, argv + argc);

	bool iA, iJ, iI, iN, iO = false;

	// Check if we are AOT compiling the code.
	iA = iA || (std::find(args.begin(), args.end(), "-a") != args.end());
	iA = iA || (std::find(args.begin(), args.end(), "-an") != args.end());
	iA = iA || (std::find(args.begin(), args.end(), "-ao") != args.end());

	// Check if we are JIT compiling the code.
	iJ = iJ || (std::find(args.begin(), args.end(), "-j") != args.end());
	iJ = iJ || (std::find(args.begin(), args.end(), "-jn") != args.end());
	iJ = iJ || (std::find(args.begin(), args.end(), "-jo") != args.end());

	// Check if we are interpreting the code.
	iI = iI || (std::find(args.begin(), args.end(), "-i") != args.end());

	// Check if we are operating naively.
	iN = iN || (std::find(args.begin(), args.end(), "-an") != args.end());
	iN = iN || (std::find(args.begin(), args.end(), "-jn") != args.end());

	// Check if we are operating opbimized.
	iO = iO || (std::find(args.begin(), args.end(), "-ao") != args.end());
	iO = iO || (std::find(args.begin(), args.end(), "-jo") != args.end());

	// Default to JIT.
	if (!iA && !iJ && !iI) iJ = true;

	// Default to Naive operation.
	if (!iN && !iO) iN = true;

	// Only one operation is allowed.
	if (!(iA != iJ != iI)) {
		std::cerr << "Error: You must select a single operation." << std::endl;
		return -1;
	}

	// Select the correct method.
	if (iJ && iN) return MainJN(args);
	else if (iJ && iO) return MainJO(args);
	else if (iA && iN) return MainAN(args);
	else if (iA && iO) return MainAO(args);
	else return MainIN(args);
}