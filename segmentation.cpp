#include "segmentation.h"


void segmentation::process() {


	LENGTH_COLS = i_COLS.read();
	LENGTH_ROWS = i_ROWS.read();

	cv::Mat src;
	src.create(cv::Size(LENGTH_COLS, LENGTH_ROWS), CV_8UC3);

	for (int i = 0; i < LENGTH_ROWS; i++)
	{
		vert = fifoVectorDifferenceVertThreshold.read();
		for (int j = 0; j < LENGTH_COLS; j++)
		{
			r = fifo_pixelR.read();
			g = fifo_pixelG.read();
			b = fifo_pixelB.read();
			if (i == 0) {
				horz.push_back(fifoVectorDifferenceHorzThreshold.read());
			}

			if (vert != 0 && horz[j] != 0) {
				src.at<cv::Vec3b>(i, j) = cv::Vec3b(b, g, r);

			}
			else {
				src.at<cv::Vec3b>(i, j) = cv::Vec3b(0, 0, 0);
			}

		}
	}



	cv::imshow(this->name(), src);
	printf("Pressione qualquer tecla para continuar. . .\n");
	cv::waitKey(0);
}