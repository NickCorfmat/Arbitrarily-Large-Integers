// --------------------------------------------------------------
// Nicolas Corfmat
// CruzID: ncorfmat
// Assignment: pa6
// --------------------------------------------------------------

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include "BigInteger.h"

using namespace std;

int main(int argc, char * argv[]) {

	// CHECK if exactly two command line arguments.
	
	if (argc != 3) {
		cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
		return EXIT_FAILURE;
	}

	// OPEN input and output files.
	
	std::ifstream input(argv[1]);
	std::ofstream output(argv[2]);

	// CHECK if input and output files are valid.
	
	if (!input) {
		std::cerr << "Failed to access input file." << endl;
		return EXIT_FAILURE;
	}

	if (!output) {
                std::cerr << "Failed to access output file." << endl;
                return EXIT_FAILURE;
        }


	// READ lines from input file.
	
	std::string line;

	std::getline(input, line);

	BigInteger A = BigInteger(line);

	std::getline(input, line);
	std::getline(input, line);

	BigInteger B = BigInteger(line);

	BigInteger AxA = A*A;
	BigInteger BxB = B*B;
	BigInteger D = 8*(BxB*BxB*B);

	// PERFORM and PRINT computations.
	
	output << A << std::endl << std::endl;
	output << B << std::endl << std::endl;
	output << A+B << std::endl << std::endl;
	output << A-B << std::endl << std::endl;
	output << A-A << std::endl << std::endl;
	output << 3*A-2*B << std::endl << std::endl;
	output << A*B << std::endl << std::endl;
	output << AxA << std::endl << std::endl;
	output << BxB << std::endl << std::endl;
	output << 9*(AxA*AxA)+(D+D) << std::endl << std::endl;

	// CLOSE input and output files.
	
	input.close();
	output.close();

	return EXIT_SUCCESS;
}
