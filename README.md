MVF - MAIA Video Format
===

MVF is a simple structure to store video-sequences from MAIA (Meteor Automatic Imager and Analyser, http://maia-project.net). It has 20B header with following structure:

* unsigned short **width**
* unsigned short **height**
* unsigned short **bpp**
* unsigned short **bppUsed**
* unsigned short **channels**
* unsigned short **reserved**
* float **fps**
* unsigned int **numOfFrames**
