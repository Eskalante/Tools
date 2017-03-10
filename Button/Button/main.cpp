/********************************************************/
/*														*/
/*	Author:		Eskalante								*/
/*	Desc.:		Example usage of button using OpenCV.	*/
/*														*/
/********************************************************/

#include <iostream>
#include <Windows.h>

#include <opencv2\opencv.hpp>

#include "button.h"
#include "functions.h"

using namespace std;
using namespace cv;

#define WIDTH	(640)
#define HEIGHT	(480)

int main() {
	// init
	bool exitapp = false;
	button b(rect(HEIGHT - 100, 270, 370, HEIGHT - 50));
	// opencv
	namedWindow("Main", WINDOW_AUTOSIZE);
	setMouseCallback("Main", mouse, NULL);
	Mat screen = Mat(HEIGHT, WIDTH, CV_8UC3, Scalar(255.0, 0.0, 0.0)); // back buffer
	cur.x = 0;
	cur.y = 0;
	RNG rng(12345);
	Scalar color(255.0, 0.0, 0.0);
	// main loop
	while (!exitapp) {
		// clear
		screen = color; // paint back buffer with color
		putText(screen, "Press button to change background color.", Point(10, 50), FONT_HERSHEY_SIMPLEX, 0.7, (Scalar::all(255) - color), 2); // write info with negative color
		// TODO
		if (b.update(ptp(cur), click)) { // update coordinates
			// button is triggered, randomize background color
			color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		}
		if (b.isActive()) {
			// activated, red button
			rectangle(screen, rtr(b.getButtonArea()), Scalar(0.0, 0.0, 255.0), -1);
		}
		else {
			// normal state, green button
			rectangle(screen, rtr(b.getButtonArea()), Scalar(0.0, 255.0, 0.0), -1);
		}
		if (GetAsyncKeyState(VK_SPACE) & 0x8000) // press Space for reset
			color = Scalar(255.0, 0.0, 0.0);
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