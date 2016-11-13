#include "lerImagem.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>


void lerImagem::process(void) {

	cv::Mat src = cv::imread(path_frame);
	cv::Mat src_T;
	cv::transpose(src, src_T);
	LENGTH_COLS = src.cols;
	LENGTH_ROWS = src.rows;

	o_COLS.write(LENGTH_COLS);
	o_ROWS.write(LENGTH_ROWS);

	o_COLS_T.write(LENGTH_ROWS);
	o_ROWS_T.write(LENGTH_COLS);

	o_COLS_S.write(LENGTH_COLS);
	o_ROWS_S.write(LENGTH_ROWS);

	for (int i = 0; i < LENGTH_ROWS; i++)
	{
		for (int j = 0; j < LENGTH_COLS; j++)
		{
			Pixel = src.at<cv::Vec3b>(i, j);
			fifo_pixelR.write(Pixel[2]);
			fifo_pixelG.write(Pixel[1]);
			fifo_pixelB.write(Pixel[0]);

			fifo_pixelR_S.write(Pixel[2]);
			fifo_pixelG_S.write(Pixel[1]);
			fifo_pixelB_S.write(Pixel[0]);
		}
	}

	for (int i = 0; i < LENGTH_COLS; i++)
	{
		for (int j = 0; j < LENGTH_ROWS; j++)
		{
			Pixel = src_T.at<cv::Vec3b>(i, j);
			fifo_pixelR_T.write(Pixel[2]);
			fifo_pixelG_T.write(Pixel[1]);
			fifo_pixelB_T.write(Pixel[0]);
		}
	}

}
