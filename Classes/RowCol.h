#ifndef __ROW_COL_H__
#define __ROW_COL_H__

struct RowCol {
public:
	static RowCol IMPOSSIBLE;
	int row;
	int column;
public:
	RowCol(int r, int c);
	bool operator==(const RowCol& other);
	bool operator!=(const RowCol& other);
};


#endif