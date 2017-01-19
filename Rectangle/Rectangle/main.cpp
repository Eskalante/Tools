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
	// INIT
	bool exitapp = false;
	// drag will start from first area and end in second
	drag d(rect(300, 300, 400, 400), rect(200, 50, WIDTH - 50, HEIGHT - 50));
	// opencv initialize
	namedWindow("Main", WINDOW_AUTOSIZE);
	setMouseCallback("Main", mouse, NULL);
	Mat screen = Mat(HEIGHT, WIDTH, CV_8UC3, Scalar(255.0, 0.0, 0.0)); // back buffer
	cur.x = 0;
	cur.y = 0;
	Rect area;
	// LOOP
	while (!exitapp) {
		// clear
		screen = Scalar(255.0, 0.0, 0.0); // paint back buffer with blue color
		rectangle(screen, rtr(d.getBorderArea()), Scalar(255.0, 0, 155.0), -1); // highlight border area
		rectangle(screen, rtr(d.getButtonArea()), Scalar(155.0, 0, 155.0), -1); // highlight starting area
																				// TODO
		if (d.update(ptp(cur), click)) { // update coordinates
			area = rtr(d.getActiveArea()); // get current dragging area
			rectangle(screen, area, Scalar(255.0, 255.0, 255.0), 1); // draw this area with white rectangle 
			line(screen, ptp(d.getStart()), ptp(d.getEnd()), Scalar(0.0, 0.0, 255, 0)); // draw line from start to end
			putText(screen, writeString("Start: ", d.getStart()), Point(10, 50), FONT_HERSHEY_SIMPLEX, 1, Scalar(255.0, 255.0, 255.0)); // write start position
			putText(screen, writeString("End: ", d.getEnd()), Point(10, 100), FONT_HERSHEY_SIMPLEX, 1, Scalar(255.0, 255.0, 255.0)); // write start position
			putText(screen, writeString("Distance: ", d.getResult()), Point(10, 150), FONT_HERSHEY_SIMPLEX, 1, Scalar(255.0, 255.0, 255.0)); // write start position
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
	// EXIT
	return 0;
}