/**
 * \file GridInfo.h
 * \brief Stores grid information
 */

#ifndef GRIDINFO_H
#define GRIDINFO_H

#include <vector>

typedef std::vector<bool> GridVector;

/**
 * \class GridInfo
 * \brief Stores grid information
 * 
 * It contains the current grid information which is used and 
 * modified by the AI without affecting the actual grid.
 */
class GridInfo
{
	private :
	
		const int m_width, m_height;
		GridVector m_grid;
	
	public :
	
		GridInfo(int width, int height);
		~GridInfo(){};
		
		int Get(int i, int j){ return m_grid[j*m_width+i]; };
		void Set(const GridVector &grid);
		void SetBlock(int i, int j, bool bVal);
		void DeleteLine(int j);
		GridInfo* GetDuplicate() const;
		
		const int GetWidth() const{ return m_width; }
		const int GetHeight() const{ return m_height; }
};

#endif

