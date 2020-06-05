#include "RowCol.h"

RowCol RowCol::IMPOSSIBLE = RowCol(-1, -1);

RowCol::RowCol(int r, int c) : row(r), column(c) { }

bool RowCol::operator==(const RowCol& other) {
	return (this->row == other.row) && (this->column == other.column);
}

bool RowCol::operator!=(const RowCol& other) {
	return (this->row != other.row) || (this->column != other.column);
}