#include "RowCol.h"

Rowcol Rowcol::IMPOSSIBLE = Rowcol(-1, -1);

Rowcol::Rowcol() : row(0), column(0) { }
Rowcol::Rowcol(int r, int c) : row(r), column(c) { }

bool Rowcol::operator==(const Rowcol& other) const {
	return (this->row == other.row) && (this->column == other.column);
}

bool Rowcol::operator!=(const Rowcol& other) const {
	return (this->row != other.row) || (this->column != other.column);
}

const Rowcol Rowcol::operator+(const Rowcol& other) const {
	Rowcol newRowcol;
	newRowcol.row = this->row + other.row;
	newRowcol.column = this->column + other.column;
	return newRowcol;
}

const Rowcol Rowcol::operator*(int scalar) const
{
	Rowcol newRowcol;
	newRowcol.row = row * scalar;
	newRowcol.column = column * scalar;
	return newRowcol;
}
