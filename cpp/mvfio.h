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
	MVF (const char * filename, unsigned short width, unsigned short height, unsigned short bppUsed, unsigned short channels, float fps, unsigned int numOfFrames);
	~MVF ();

	FILE_HEADER_MVF header;

	int frameSize;
	int frameWidth;
	int frameHeight;

	bool getFrame (unsigned int index, unsigned short * frame);
	bool getFrame (unsigned int index, std::vector<unsigned short> & frame);
	bool add (std::vector<short unsigned int> & frame);
private:
	const char * filename;
	void open (const char * filename, std::ios_base::openmode mode);
	void readHeader ();
	void writeHeader (FILE_HEADER_MVF in_header);
	void validateIndex (unsigned int index);
	std::fstream inputFile;
};
