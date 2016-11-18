/****************************************************/
/*													*/
/*	Author:		Eskalante							*/
/*	Desc.:		Example usage of drag using OpenCV.	*/
/*													*/
/****************************************************/

#include <iostream>
#include <Windows.h>

#include <opencv2\opencv.hpp>

#include "drag.h"
#include "functions.h"

using namespace std;
using namespace cv;

#define WIDTH	(640)
#define HEIGHT	(480)

int main() {
	// init
	bool exitapp = false;
	drag d(rect(100, 100, 200, 200)); // drag will start from this area
	// opencv
	namedWindow("Main", WINDOW_NORMAL);
	setMouseCallback("Main", mouse, NULL);
	Mat screen = Mat(600, 600, CV_8UC3, Scalar(255.0, 0.0, 0.0)); // back buffer
	cur.x = 0;
	cur.y = 0;
	Rect area;
	// loop
	while (!exitapp) {
		// clear
		screen = Scalar(255.0, 0.0, 0.0); // paint back buffer with blue color
		rectangle(screen, rtr(d.getButtonArea()), Scalar(155.0, 0, 155.0), -1); // highlight starting area
		// TODO
		if (d.update(ptp(cur), click)) { // update coordinates
			area = rtr(d.getActiveArea()); // get current dragging area
			rectangle(screen, area, Scalar(255.0, 255.0, 255.0), 1); // draw this area with white rectangle 
			line(screen, ptp(d.getStart()), ptp(d.getEnd()), Scalar(0.0, 0.0, 255, 0)); // draw line from start to end
		}
		else
			rectangle(screen, area, Scalar(255.0, 255.0, 255.0), -1); // after dragging leave filled white rectangle
		if (GetAsyncKeyState(VK_SPACE) & 0x8000) // press Space for reset
			area = Rect();
		// show
		imshow("Main", screen);
		// update
		waitKey(1);
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) // press ESC to exit
			exitapp = true;
	}
	// exit
	return 0;
}