#pragma once

/****************************************/
/*										*/
/*	Author:		Eskalante				*/
/*	Name:		Button					*/
/*	Version:	1.0						*/
/*	Desc.:		Tool for buttons.		*/
/*										*/
/****************************************/

// point coordinate
struct point {
	int x;
	int y;
};
// rectangle coordinate
struct rect {
	rect() {

	}
	rect(int t, int l, int r, int b) :top(t), left(l), right(r), bottom(b) {

	}
	signed int top;
	signed int left;
	signed int right;
	signed int bottom;
};

class button {
	// C&D
public:
	// provide working area
	button(rect sArea) :bActive(0), bFalse(0), sButtonArea(sArea) {

	}
	virtual	~button() {

	}

	// SYS
public:
	// call in main cycle
	// INPUT: current cursor position, state of mouse left button (down=true)
	// OUTPUT: state of button (pushed=true)
	bool	update(point sCursor, bool bLeftButton = false) {
		if (bLeftButton) {
			if (!bActive) {
				if (isIn(sCursor, sButtonArea) && !bFalse) {
					// on left button down in area
					bActive = true;
				}
				else
					// false activation, button was allready pushed outside
					bFalse = true;
			}
		}
		else {
			// reset false state
			bFalse = false;
			if (bActive) {
				bActive = false;
				// on left button up
				if(isIn(sCursor, sButtonArea))
					return true;
			}
		}
		return false;
	}

	// MAIN
public:
	bool	isActive() const {
		return bActive;
	}

	// ACC
public:
	rect	getButtonArea() const {
		return sButtonArea;
	}
	void	setButtonArea(rect sNewArea) {
		sButtonArea = sNewArea;
	}

	// ATR
private:
	rect	sButtonArea;	// area from which the drag starts
	bool	bActive;		// button is pushed
	bool	bFalse;			// false activation

	// HELP
private:
	// calculate if point is in rectangle
	bool	isIn(point sCursor, rect sArea) {
		if (sCursor.x <= sArea.right &&
			sCursor.x >= sArea.left &&
			sCursor.y <= sArea.bottom &&
			sCursor.y >= sArea.top) {
			return true;
		}
		return false;
	}
};