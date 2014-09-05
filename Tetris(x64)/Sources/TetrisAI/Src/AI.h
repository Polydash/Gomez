/**
 * \file AI.h
 * \brief Artificial Intelligence
 */

#ifndef AI_H
#define AI_H

#include "GridInfo.h"
#include "../../Tetris/Src/TetrisLogic/TetrisPiece.h"
#include "../../Tetris/Src/Event/Events/Evt_MainGameInput.h"
#include "../../Tetris/Src/Event/IEvent.h"
#include "../../Tetris/Src/Network/Client.h"

/**
 * \class AI
 * \brief Artificial Intelligence
 * 
 * The AI calculates a score for every possible position and orientation
 * of each piece, based on different criteria and coefficients.
 * The best score indicates which move will be played.
 */
class AI
{
	private :
	
		GridInfo *m_pGrid;
		Client *m_pClient;
		
		ePieceType m_pieceType;
	
	public :
	
		AI(Client *pClient);
		~AI();
		
		bool Init();
		
	private :
	
		void CalculateAI();
		void SendMessage(eGameInput input);
		bool CheckCollision(TetrisPiece *pPiece);
		void DropPiece(TetrisPiece *pPiece);
		
		float CalculateScore(TetrisPiece *pPiece);
		
		/**
		 * \fn RowsNbTest
		 * \brief Counts the number of cleared rows and deletes them
		 * 
		 * It must be the first test to be run since it
		 * modifies the grid info. The next tests are then
		 * executed on the updated grid.
		 */
		int RowsNbTest(GridInfo *pGrid, TetrisPiece *pPiece);
		
		/**
		 * \fn AverageHeightTest
		 * \brief Calculates the height at which the piece lands
		 */
		float AverageHeightTest(TetrisPiece *pPiece);
		
		/**
		 * \fn HolesNbTest
		 * \brief Counts the number of holes
		 * 
		 * A hole is an empty space with a block directly above it.
		 */
		int HolesNbTest(GridInfo *pGrid);
		
		/**
		 * \fn PipesNbTest
		 * \brief Counts the number of pipes
		 * 
		 * A pipe is represented by multiple holes next to each other
		 * on the same column surrounded by blocks.
		 */
		int PipesNbTest(GridInfo *pGrid);
		
		void NewTetrisLoopDelegate(EventSharedPtr pEvent);
		
		void RegisterEvents();
		void UnregisterEvents();
};

#endif
