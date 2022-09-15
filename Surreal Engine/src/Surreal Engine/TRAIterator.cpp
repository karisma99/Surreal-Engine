//TRAIterator

#include "TRAIterator.h"
#include "TerrainRectangleArea.h"

TRAIterator::TRAIterator(int _i, int _j, TerrainRectangleArea* p)
{
	i = _i; 
	j = _j; 
	pRect = p;
}

TRAIterator::TRAIterator(const TRAIterator& other)
{
	this->i = other.i; 
	this->j = other.j; 
	this->pRect = other.pRect;
}

TRAIterator& TRAIterator::operator= (const TRAIterator& other)
{
	this->i = other.i;
	this->j = other.j;
	this->pRect = other.pRect;

	return *this;
}

bool TRAIterator::operator!= (const TRAIterator& other)
{
	if (this->i == other.i && this->j == other.j)
		return false;
	else
		return true;
}

TRAIterator& TRAIterator::operator++ ()
{
	int nextJ = this->j + 1; 
	if (nextJ > pRect->GetMaxJ())
	{
		i = i + 1; 
		j = pRect->GetMinJ();
	}
	else
	{
		j = nextJ; 
	}

	return *this;
}

TRAIterator TRAIterator::operator+(int x)
{
	TRAIterator t = TRAIterator(this->i, this->j, this->pRect);

	for (int n = 0; n < x; n++)
	{
		++t;
	}
	
	return t;
}
