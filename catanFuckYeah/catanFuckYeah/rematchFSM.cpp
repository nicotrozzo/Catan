#include "rematchFSM.h"



rematchFSM::rematchFSM(bool iWon) :  genericFSM(&fsmTable[0][0], , ,iWon ? : )
{
}


rematchFSM::~rematchFSM()
{
}
