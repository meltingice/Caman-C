#include "caman.h"

int main(int argc, char **argv) {
	if (argc != 2) {
		printf("ERROR: please specify an input file\n");
		return 1;
	}
	
	CamanInitialize();
	
	CamanInstance caman = NewCamanFromFile(argv[1]);
	brightness(caman, 5.0);

	writeCamanToFile(caman, "./output.jpg");
	
	CamanFinish();
	
	return 0;
}