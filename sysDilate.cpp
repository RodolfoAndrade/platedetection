#include "sysDilate.h"


void sysDilate::main_action() {

	LENGTH_COLS = i_COLS.read();
	LENGTH_ROWS = i_ROWS.read();
	const unsigned int mylength = 1; // storage capacity/burst length in words
	int mydata;
	simple_bus_status status;
	
	

	cv::Mat src;

	
	for (int i = 0; i < LENGTH_COLS; i++) {
		//while (receive.read() == 0);
		//send.write((sc_bit)0);
		//wait(); //espera escrever
		while (sync.read() == false) wait();
		status = bus_port->burst_read(m_unique_priority, &mydata,
			m_address, mylength, m_lock);
		while (status == SIMPLE_BUS_ERROR) {
			status = bus_port->burst_read(m_unique_priority, &mydata,
				m_address, mylength, m_lock);
		}
		
		
		//send.write((sc_bit)1);
		L0.push(0);
		L1.push(mydata);

		//cout << "Sync Sys: " << sync << endl;
		

		/*if (i >= mydata[0]) {
			break;
		}*/
		sync.write(false); //avisar que leu

		
	}
	/*
		|p4|		   posições equivalentes         	 |0|1|0|
	 |p3|p2|p1|   =    para a operação de dilate   =>    |1|1|1|
		|p5|		   seguindo a ideia das fifos		 |0|1|0|
	*/

	//cout << mydata[0] << endl;
	//cout << mydata[1] << endl;

	o_COLS.write(LENGTH_COLS);
	o_ROWS.write(LENGTH_ROWS);
	//int cols = mydata[0];
	//int rows = mydata[1];
	
	src.create(cv::Size(LENGTH_COLS, LENGTH_ROWS), CV_8UC1);



	for (int i = 0; i < LENGTH_ROWS; i++) {
		for (int j = 0; j < LENGTH_COLS; j++) {
			
			
			//send.write((sc_bit)0);
			sync.write(false); //avisar que leu
			//wait();
			if (i < LENGTH_ROWS - 1) {
				while (sync.read() == false) wait();

				//cout << "sysDilate!" << endl;
				status = bus_port->burst_read(m_unique_priority, &mydata,
					m_address, mylength, m_lock);
				while (status == SIMPLE_BUS_ERROR) {
					cout << "Deu merda 2" << endl;
					status = bus_port->burst_read(m_unique_priority, &mydata,
						m_address, mylength, m_lock);
				}
			}
			
			//send.write((sc_bit)1);
			if (i == 0 && j == 0) {
				p4 = L0.front();
				L0.pop();
				p3 = L0.back();
				p2 = L1.front();
				L1.pop();
				p1 = L1.front();
				L0.push(p2);
				p5 = mydata;
				L1.push(p5);
			}
			else if (i == 0 && j == LENGTH_COLS - 1) {
				p4 = L0.front();
				L0.pop();
				p3 = L0.back();
				p2 = L1.front();
				L1.pop();
				p1 = 0;
				L0.push(p2);
				p5 = mydata;
				L1.push(p5);
			}
			else if (j == 0 && i == LENGTH_ROWS - 1) {
				p4 = L0.front();
				L0.pop();
				p3 = L0.back();
				p2 = L1.front();
				L1.pop();
				p1 = L1.front();
				L0.push(p2);
				p5 = 0;
				L1.push(p5);
			}
			else if (j == LENGTH_COLS - 1 && i == LENGTH_ROWS - 1) {
				p4 = L0.front();
				L0.pop();
				p3 = L0.back();
				p2 = L1.front();
				L1.pop();
				p1 = 0;
				L0.push(p2);
				p5 = 0;
				L1.push(p5);
			}
			else if (i == 0) {
				p4 = L0.front();
				L0.pop();
				p3 = L0.back();
				p2 = L1.front();
				L1.pop();
				p1 = L1.front();
				L0.push(p2);
				p5 = mydata;
				L1.push(p5);
			}
			else if (j == 0) {
				p4 = L0.front();
				L0.pop();
				p3 = 0;
				p2 = L1.front();
				L1.pop();
				p1 = L1.front();
				L0.push(p2);
				p5 = mydata;
				L1.push(p5);
			}
			else if (j == LENGTH_COLS - 1) {
				p4 = L0.front();
				L0.pop();
				p3 = L0.back();
				p2 = L1.front();
				L1.pop();
				p1 = 0;
				L0.push(p2);
				p5 = mydata;
				L1.push(p5);
			}
			else if (i == LENGTH_ROWS - 1) {
				p4 = L0.front();
				L0.pop();
				p3 = L0.back();
				p2 = L1.front();
				L1.pop();
				p1 = L1.front();
				L0.push(p2);
				p5 = 0;
				L1.push(p5);
			}
			else {
				p4 = L0.front();
				L0.pop();
				p3 = L0.back();
				p2 = L1.front();
				L1.pop();
				p1 = L1.front();
				L0.push(p2);
				p5 = mydata;
				L1.push(p5);
			}

			temp = max(p1, p2);
			temp = max(temp, p3);
			temp = max(temp, p4);
			fifo_pixelDilate.write((int)max(temp, p5));
			src.at<uchar>(i, j) = (int)max(temp, p5);
			
		}
		//cout << "Eita!! " << i << endl;
	}

	//cout << "Eita2!!" << endl;

	cv::imshow(this->name(), src);
	cv::waitKey(0);

}