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
	button(rect sArea) :bDragState(0), sButtonArea(sArea) {
		point nill;
		nill.x = 0;
		nill.y = 0;
		sStart = nill;
		sEnd = nill;
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
			if (bDragState) {
				// update
				sEnd.x = sCursor.x;
				sEnd.y = sCursor.y;
			}
			else {
				if (isIn(sCursor))
					// on left button down
					sStart.x = sCursor.x;
				sStart.y = sCursor.y;
				sEnd.x = sCursor.x;
				sEnd.y = sCursor.y;
				// start dragging
				bDragState = true;
			}
		}
		else {
			if (bDragState) {
				// on left button up
				sEnd.x = sCursor.x;
				sEnd.y = sCursor.y;
				// end dragging
				bDragState = false;
			}
		}
		return bDragState;
	}

	// MAIN
public:
	rect	getActiveArea() const {
		return calcActiveArea();
	}
	point	getTopLeft() const {
		point ret;
		ret.x = calcActiveArea().left;
		ret.y = calcActiveArea().top;
		return ret;
	}
	point	getTopRight() const {
		point ret;
		ret.x = calcActiveArea().right;
		ret.y = calcActiveArea().top;
		return ret;
	}
	point	getBottomLeft() const {
		point ret;
		ret.x = calcActiveArea().left;
		ret.y = calcActiveArea().bottom;
		return ret;
	}
	point	getBottomRight() const {
		point ret;
		ret.x = calcActiveArea().right;
		ret.y = calcActiveArea().bottom;
		return ret;
	}
	// return vector between start and end points
	point	getResult() const {
		point ret;
		ret.x = abs(sStart.x - sEnd.x);
		ret.y = abs(sStart.y - sEnd.y);
		return ret;
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
	point	sStart;			// starting point
	point	sEnd;			// ending point
	bool	bDragState;		// status of the drag

	// HELP
private:
	// calculate if point is in rectangle
	bool	isIn(point sCursor) {
		if (sCursor.x <= sButtonArea.right &&
			sCursor.x >= sButtonArea.left &&
			sCursor.y <= sButtonArea.bottom &&
			sCursor.y >= sButtonArea.top) {
			return true;
		}
		return false;
	}
	// calculate rectangle from two points (top left and bottom right)
	rect	calcActiveArea() const {
		rect ret;
		// find top&bottom points
		if (sStart.y >= sEnd.y) {
			ret.bottom = sStart.y;
			ret.top = sEnd.y;
		}
		else {
			ret.bottom = sEnd.y;
			ret.top = sStart.y;
		}
		// find left&right points
		if (sStart.x >= sEnd.x) {
			ret.right = sStart.x;
			ret.left = sEnd.x;
		}
		else {
			ret.right = sEnd.x;
			ret.left = sStart.x;
		}
		return ret;
	}
	// calculate absolute value
	int		abs(signed int value) const {
		if (value < 0) {
			return (-1 * value);
		}
		return value;
	}
};