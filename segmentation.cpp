#include "segmentation.h"


void segmentation::main_action() {


	LENGTH_COLS = i_COLS.read();
	LENGTH_ROWS = i_ROWS.read();

	const unsigned int mylength = 1; // storage capacity/burst length in words
	int mydata_vert;
	int mydata_horz;
	simple_bus_status status;
	bool entrou = false;

	cv::Mat src;
	src.create(cv::Size(LENGTH_COLS, LENGTH_ROWS), CV_8UC3);

	for (int i = 0; i < LENGTH_ROWS; i++)
	{
		//cout << "Segmentation: " << i << endl;
		while (sync_vert.read() == false) wait();
		
		status = bus_port->burst_read(m_unique_priority, &mydata_vert,
			m_address_vert, mylength, m_lock);
		while (status == SIMPLE_BUS_ERROR) {
			status = bus_port->burst_read(m_unique_priority, &mydata_vert,
				m_address_vert, mylength, m_lock);
		}

		vert = mydata_vert;
		cout << "Vert: " << vert<<endl;
		sync_vert.write(false);

		//vert = fifoVectorDifferenceVertThreshold.read();
		for (int j = 0; j < LENGTH_COLS; j++)
		{
			while (sync_horz.read() == false) wait();
			r = fifo_pixelR.read();
			g = fifo_pixelG.read();
			b = fifo_pixelB.read();
			if (i == 0) {
				//while (sync_horz.read() == false) wait();
				status = bus_port->burst_read(m_unique_priority, &mydata_horz,
					m_address_horz, mylength, m_lock);
				while (status == SIMPLE_BUS_ERROR) {
					status = bus_port->burst_read(m_unique_priority, &mydata_horz,
						m_address_horz, mylength, m_lock);
				}

				horz.push_back(mydata_horz);
				cout << "Hor: " << mydata_horz << endl;
				sync_horz.write(false);
				//sync_horz.write(false);
				//horz.push_back(fifoVectorDifferenceHorzThreshold.read());
			}

			if (vert != 0 && horz[j] != 0) {
				src.at<cv::Vec3b>(i, j) = cv::Vec3b(b, g, r);
				entrou = true;

			}
			else {
				src.at<cv::Vec3b>(i, j) = cv::Vec3b(0, 0, 0);
			}

		}
		//sync_vert.write(false);
		//cout << "Segmentation:  " << i << endl;
		
	}

	if (entrou) {
		cout << "Entrou!!" << endl;
	}

	cv::imshow(this->name(), src);
	printf("Pressione qualquer tecla para continuar. . .\n");
	cv::waitKey(0);
}