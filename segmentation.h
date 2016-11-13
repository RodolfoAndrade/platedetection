#pragma once
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <systemc.h>
#include <vector>

SC_MODULE(segmentation) {
	int vert;
	std::vector<int> horz;
	int r, g, b;
	int LENGTH_COLS, LENGTH_ROWS;
	sc_fifo_in<int> i_COLS, i_ROWS;
	sc_fifo_in<int> fifoVectorDifferenceVertThreshold;
	sc_fifo_in<int> fifoVectorDifferenceHorzThreshold;
	sc_fifo_in<int> fifo_pixelR;
	sc_fifo_in<int> fifo_pixelG;
	sc_fifo_in<int> fifo_pixelB;

	void process();
	SC_CTOR(segmentation) {
		SC_THREAD(process);
	}
};