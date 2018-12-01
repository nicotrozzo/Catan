
#include "catanPlayerModel.h"

cards::cards()
{
	ore = 0;
	wool = 0;
	wheat = 0;
	wood = 0;
	brick = 0;
}


catanPlayerModel::catanPlayerModel()
{

}


void catanPlayerModel::setName(string name)
{
	 if (nameIs.length() == 0)
	 { 
		 nameIs = name.substr(0, MAX_NAME_LENGTH); 
	 } 
	 
}

catanPlayerModel::~catanPlayerModel()
{
}

