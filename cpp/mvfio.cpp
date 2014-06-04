#include "mvfio.h"

MVF::MVF (const char * filename)
{
	inputFile.exceptions (std::ifstream::eofbit | std::ifstream::failbit | std::ifstream::badbit);

	loadFile (filename);
	readHeader ();
}

void MVF::loadFile (const char * filename)
{
	try
	{
		inputFile.open (filename, std::ios::binary);
	}
	catch (std::ifstream::failure e)
	{
		std::cerr << "Error opening the file (" << e.what() << ")" << std::endl ;
		std::exit (EXIT_FAILURE);
	}
}

void MVF::readHeader()
{
	inputFile.seekg(0, std::ios_base::beg);
	
	try
	{
		inputFile.read((char *)&header, sizeof(header));
		frameSize = sizeof (unsigned short) * header.width * header.height;
	}
	catch (std::ifstream::failure e) 
	{
		std::cerr << "Error reading header (" << e.what() << ")" << std::endl;
		std::exit (EXIT_FAILURE);
	}
}

void MVF::validateIndex (unsigned int index)
{
	if (index > header.numOfFrames)
        {
                std::cerr << "Requested index extends beyond the end of the file. Using last frame instead." << std::endl;
                index = header.numOfFrames;
        }

        if (index < 1)
        {
                std::cerr << "Index should be positive integer. Using 1 instead." << std::endl;
                index = 1;
        }	
}

bool MVF::getFrame (unsigned int index, unsigned short * frame)
{
	validateIndex (index);

	inputFile.seekg (sizeof(header) + (index - 1) * frameSize, std::ios_base::beg);
	inputFile.read ((char *)frame, frameSize);

	return true;
}

bool MVF::getFrame (unsigned int index, std::vector<unsigned short> & frame)
{
	validateIndex (index);

	inputFile.seekg (sizeof(header) + (index - 1) * frameSize, std::ios_base::beg);

	try
	{
		inputFile.read ((char *) &frame[0], frameSize);
	}
	catch (std::ifstream::failure e) 
	{
		std::cerr << "Error reading frame (" << e.what() << ")" << std::endl;
		return false;
	}

	return true;
}
