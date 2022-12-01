#include "TRAIterator.h"



TRAIterator::TRAIterator(CellIndex ind, TerrainRectangleArea* area)
{
	current = ind;
	TerRectArea = area;
}

void TRAIterator::next()
{
	int i = current.i;
	int j = current.j;
	if (j + 1 > TerRectArea->max.j)
	{
		i += 1;
		j = TerRectArea->min.j;
	}
	else
	{
		j += 1;
	}
	CellIndex cellidx(i, j);
	current = cellidx;
}
