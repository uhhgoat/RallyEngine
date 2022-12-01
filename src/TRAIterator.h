#pragma once
#include <iterator>
#include "TerrainRectangleArea.h"
class TRAIterator
{
public:
	TRAIterator() = default;
	TRAIterator(CellIndex ind, TerrainRectangleArea* area);
	TerrainRectangleArea* TerRectArea;

	CellIndex current;
	void next();


    bool operator ==(const TRAIterator& d) {
        if (current.i == d.current.i && current.j == d.current.j) {
            return true;
        }

        return false;
    }
};
