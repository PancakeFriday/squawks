// My includes
#include "Globals.h"
#include "Squawks.h"

int main()
{
	Squawks squawks;
	squawks.init();
	squawks.run();
	squawks.close();

	return EXIT_SUCCESS;
}
