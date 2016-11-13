#pragma once
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <systemc.h>

#define frame_rows 1080
#define frame_cols 1920
#define path_frame "arquivos/carro0.bmp"

SC_MODULE(lerImagem) {
	cv::Vec3b Pixel;
	int LENGTH_COLS, LENGTH_ROWS;
	sc_fifo_out<int> o_COLS, o_ROWS;
	sc_fifo_out<int> fifo_pixelR;
	sc_fifo_out<int> fifo_pixelG;
	sc_fifo_out<int> fifo_pixelB;

	sc_fifo_out<int> o_COLS_T, o_ROWS_T;
	sc_fifo_out<int> fifo_pixelR_T;
	sc_fifo_out<int> fifo_pixelG_T;
	sc_fifo_out<int> fifo_pixelB_T;

	sc_fifo_out<int> o_COLS_S, o_ROWS_S;
	sc_fifo_out<int> fifo_pixelR_S;
	sc_fifo_out<int> fifo_pixelG_S;
	sc_fifo_out<int> fifo_pixelB_S;

	void process();

	SC_CTOR(lerImagem) {
		SC_THREAD(process);
	}

};