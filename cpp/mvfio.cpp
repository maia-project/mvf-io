#include "mvfio.h"

/**
 * Constructor for reading
 */
MVF::MVF (const char * filename)
{
	inputFile.exceptions (std::ifstream::eofbit | std::ifstream::failbit | std::ifstream::badbit);

	open (filename, std::ios::in);

	readHeader ();
}

/**
 * Constructor for writing 
 */

MVF::MVF (const char * filename, unsigned short width, unsigned short height, unsigned short bppUsed, unsigned short channels, float fps, unsigned int numOfFrames)
{
	inputFile.exceptions (std::ofstream::eofbit | std::ofstream::failbit | std::ofstream::badbit);

        open (filename, std::ios::out);
	
	this->header.width = width;
        this->header.height = height;
        this->header.bppUsed = bppUsed;
        this->header.channels = channels;
        this->header.fps = fps;
        this->header.numOfFrames = 0;

	frameSize = width*height;

        writeHeader (this->header);	
}

MVF::~MVF ()
{
	inputFile.close ();
}

void MVF::open (const char * filename, std::ios_base::openmode mode)
{
	try
	{
		inputFile.open (filename, mode | std::ios::binary);
	}
	catch (std::fstream::failure e)
	{
		std::cerr << "Error opening the file " << filename << " (" << e.what() << ")" << std::endl ;
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
	catch (std::fstream::failure e) 
	{
		std::cerr << "Error reading header (" << e.what() << ")" << std::endl;
		std::exit (EXIT_FAILURE);
	}
}


void MVF::writeHeader (FILE_HEADER_MVF in_header)
{
	inputFile.seekg(0, std::ios_base::beg);

	try
	{
		inputFile.write ((char *)&in_header, sizeof (in_header));
	}
	catch (std::fstream::failure e)
	{
		std::cerr << "Error writing header (" << e.what() << ")" << std::endl;
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

bool MVF::add (std::vector<unsigned short> & frame)
{
	inputFile.seekg (0, std::ios_base::end);

	try
	{
		inputFile.write ((char *)&frame[0], frameSize*2);
	}
	catch (std::ifstream::failure e)
        {
                std::cerr << "Error writing frame (" << e.what() << ")" << std::endl;
                return false;
        }

	this->header.numOfFrames++;

	writeHeader (this->header);

        return true;

}
