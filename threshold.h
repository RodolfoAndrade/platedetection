#pragma once
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <systemc.h>
#include <vector>

SC_MODULE(threshold)
{
	int n_inicio;
	int n_fim;

	int LENGTH_ROWS, POSI_MAX, AVERAGE;

	sc_fifo_in<int> i_ROWS;
	sc_fifo_in<int> i_average;
	sc_fifo_in<int> i_posi_max;
	sc_fifo_in<int> fifoVectorDifference;

	sc_fifo_out<int> fifoVectorDifferenceThreshold;

	void process();
	SC_CTOR(threshold) {
		SC_THREAD(process);
	}
};