#pragma once

/********************************************/
/*											*/
/*	Author:		Eskalante					*/
/*	Desc.:		Support functions for drag.	*/
/*											*/
/********************************************/

#include <iostream>
#include <Windows.h>
#include <opencv2\opencv.hpp>

#include "drag.h"

using namespace std;
using namespace cv;

// mouse states
bool click = false;
POINT cur;
// mouse callback
void mouse(int event, int x, int y, int flags, void* userdata)
{
	if (event == EVENT_LBUTTONDOWN)
	{
		click = true;
		cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
		cur.x = x;
		cur.y = y;
	}
	else if (event == EVENT_RBUTTONDOWN)
	{
		cout << "Right button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
		cur.x = x;
		cur.y = y;
	}
	else if (event == EVENT_MBUTTONDOWN)
	{
		cout << "Middle button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
		cur.x = x;
		cur.y = y;
	}
	else if (event == EVENT_MOUSEMOVE)
	{
		cout << "Mouse move over the window - position (" << x << ", " << y << ")" << endl;
		cur.x = x;
		cur.y = y;
	}
	else if (event == EVENT_LBUTTONUP) {
		click = false;
		cout << "Left button of the mouse is released - position (" << x << ", " << y << ")" << endl;
		cur.x = x;
		cur.y = y;
	}
}

// conversions
Rect rtr(rect in) {
	Rect ret;
	ret.x=in.left;
	ret.y=in.top;
	ret.width=in.right-in.left;
	ret.height=in.bottom-in.top;
	return ret;
}
rect rtr(Rect in) {
	return rect(in.y, in.x, (in.x+in.width), (in.y+in.height));
}
Point ptp(point in) {
	Point ret;
	ret.x = in.x;
	ret.y = in.y;
	return ret;
}
point ptp(POINT in) {
	point ret;
	ret.x = in.x;
	ret.y = in.y;
	return ret;
}

// prepare output string
String writeString(String strText, point sCur) {
	char ch[255];
	String ret = strText;
	_itoa_s(sCur.x, ch, 10);
	ret += ch;
	ret += " ";
	_itoa_s(sCur.y, ch, 10);
	ret += ch;
	return ret;
}