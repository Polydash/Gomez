#ifndef EVT_NEWTETRISLOOP_H
#define EVT_NEWTETRISLOOP_H

/**
 * \file Evt_NewTetrisLoop.h 
 * \brief New Tetris Loop Event
 */

#include <vector>

#include "../IEvent.h"
#include "../../TetrisLogic/TetrisGrid.h"

/**
 * \class Evt_NewTetrisLoop
 * \brief New Tetris Loop Event
 * 
 * Event allowing information of the new game loop to be launched to 
 * clients.
 * 
 * Serialize and Deserialize methods make use of stringstream to send
 * informations on the network. 
 */
class Evt_NewTetrisLoop : public IEvent
{
private :

	typedef std::vector<bool> GridVector;

	GridVector m_grid;
	ePieceType m_pieceType;
	
public :

	Evt_NewTetrisLoop(){}
	Evt_NewTetrisLoop(TetrisGrid *pGrid, ePieceType type);
	~Evt_NewTetrisLoop();
	
	virtual eEventType VGetType() const{ return ET_NEWTETRISLOOP; }
	
	const GridVector& GetGrid() const{ return m_grid; }
	ePieceType GetPieceType() const{ return m_pieceType; }
	
	virtual void VSerialize(std::ostringstream &oss);
	virtual void VDeserialize(std::istringstream &iss);
	
private :

	void SetGrid(TetrisGrid *pGrid);
};

#endif
