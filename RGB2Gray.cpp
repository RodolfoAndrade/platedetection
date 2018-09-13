#include "RGB2Gray.h"

void RGB2Gray::main_action() {

	const unsigned int mylength = 1; // storage capacity/burst length in words
	int mydata;
	simple_bus_status status;

	LENGTH_COLS = i_COLS.read();
	LENGTH_ROWS = i_ROWS.read();
	cols_o.write(LENGTH_COLS);
	rows_o.write(LENGTH_ROWS);

	//mydata[0] = LENGTH_COLS;
	//mydata[1] = LENGTH_ROWS;


	cv::Mat src;
	src.create(cv::Size(LENGTH_COLS, LENGTH_ROWS), CV_8UC1);
	for (int i = 0; i < LENGTH_ROWS; i++) {
		for (int j = 0; j < LENGTH_COLS; j++) {
			r = fifo_pixelR.read();
			g = fifo_pixelG.read();
			b = fifo_pixelB.read();

			//mydata[0] = LENGTH_COLS;
			//[1] = LENGTH_ROWS;
			mydata = (int)((4897 * r + 9617 * g + 1868 * b) >> 14);
			
			
			//while (receive.read() == 0 && i != 0 && j != 0);

			//send.write((sc_bit) 0);

			//wait();
			
			status = bus_port->burst_write(m_unique_priority, &mydata,
				m_address, mylength, m_lock);

			if (status == SIMPLE_BUS_OK)
			{
				//cout <<"SyncRGB: "<< sync << endl;
			}
			while (status == SIMPLE_BUS_ERROR) {
				//wait();
				cout << "ERROR!" << endl;
				status = bus_port->burst_write(m_unique_priority, &mydata,
					m_address, mylength, m_lock);
			 }
			sync.write(true); //avisar que escreveu
			//cout << "RGB!" << endl;
			//wait();
			while (sync.read() == true) wait();

			//send.write((sc_bit)1);

			//fifo_pixelGray.write((int)((4897 * r + 9617 * g + 1868 * b) >> 14));
			//src.at<uchar>(i, j) = (int)((4897 * r + 9617 * g + 1868 * b) >> 14);
		}
	}

	//cout << "Acabou RGB" << endl;


	//cv::imshow(this->name(), src);
	//cv::waitKey(0);
}