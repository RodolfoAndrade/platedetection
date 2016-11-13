#pragma once
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <systemc.h>
#include <vector>

SC_MODULE(difference_hist)
{
	int sum;
	int max_vert;
	int total_sum;
	int difference;
	int maximum;
	int average;
	int n;
	int m;
	std::vector<int> vert;
	int LENGTH_COLS, LENGTH_ROWS;

	sc_fifo_in<int> i_COLS, i_ROWS;
	sc_fifo_in<int> fifo_pixelDilate;

	sc_fifo_out<int> o_ROWS;
	sc_fifo_out<int> o_average;
	sc_fifo_out<int> o_posi_max;
	sc_fifo_out<int> fifoVectorDifference;

	void process();
	SC_CTOR(difference_hist) {
		SC_THREAD(process);
	}
};