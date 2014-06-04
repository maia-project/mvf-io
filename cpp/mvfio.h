#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>

struct FILE_HEADER_MVF
{
	unsigned short width;                                                                                                    
	unsigned short height;
	unsigned short bpp;
	unsigned short bppUsed;
	unsigned short channels;
	unsigned short reserved;
	float fps;
	unsigned int numOfFrames;
};

class MVF
{
public:
	MVF (const char * filename);

	FILE_HEADER_MVF header;

	int frameSize;
	int frameWidth;
	int frameHeight;

	bool getFrame (unsigned int index, unsigned short * frame);
	bool getFrame (unsigned int index, std::vector<unsigned short> & frame);
private:
	void loadFile (const char * filename);
	void readHeader ();
	void validateIndex (unsigned int index);
	std::ifstream inputFile;
};
