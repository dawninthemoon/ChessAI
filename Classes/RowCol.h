#ifndef __ROW_COL_H__
#define __ROW_COL_H__

struct Rowcol {
public:
	static Rowcol IMPOSSIBLE;
	int row;
	int column;
public:
	Rowcol();
	Rowcol(int r, int c);
	bool operator==(const Rowcol& other) const;
	bool operator!=(const Rowcol& other) const;
	Rowcol& operator+(const Rowcol& other) const;
};


#endif