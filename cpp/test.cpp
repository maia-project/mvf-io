#include "mvfio.h"

int main (int argc, char * argv[])
{
	MVF *a = new MVF (argv[1]);

	unsigned short * frame = new unsigned short [a->frameSize];

	a->getFrame (1, frame);

	std::cout << a->header.width << std::endl;

	std::vector<unsigned short> f(a->frameSize);

	a->getFrame (1, f);
}
