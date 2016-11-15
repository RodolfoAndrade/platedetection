#include "threshold.h"

void threshold::main_action() {
	const unsigned int mylength = 1; // storage capacity/burst length in words
	int mydata;
	simple_bus_status status;

	int count = 0;


	LENGTH_ROWS = i_ROWS.read();
	POSI_MAX = i_posi_max.read();
	AVERAGE = i_average.read();
	//cout << "Average: " << AVERAGE << endl;
	std::vector<int> vert;

	for (int i = 0; i < LENGTH_ROWS; i++)
	{
		vert.push_back(fifoVectorDifference.read());
	}
	n_inicio = -1;
	n_fim = -1;
	for (int i = 0; i < LENGTH_ROWS; i++)
	{
		//cout << "Threshold: " << i << endl;
		if (vert[i] < AVERAGE)
		{
			if (n_inicio != -1) {
				n_fim = i;

			}
			mydata = 0;
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
			while (sync.read() == true) wait();
			//fifoVectorDifferenceThreshold.write(0);
		}
		else {
			if (n_inicio == -1) {
				n_inicio = i;
			}
		}

		if ((n_inicio != (-1)) && (i == (LENGTH_ROWS - 1))) {
			n_fim = LENGTH_ROWS - 1;
		}

		if (n_inicio != (-1) && n_fim != (-1)) {
			
			if (!(POSI_MAX >= n_inicio && POSI_MAX <= n_fim))
			{
				for (int n = n_inicio; n <= n_fim; n++)
				{
					mydata = 0;
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
					while (sync.read() == true) wait();
					//fifoVectorDifferenceThreshold.write(0);
				}
			}
			else {
				for (int n = n_inicio; n <= n_fim; n++)
				{
					count++;
					//cout << "Vert[" << i << "]" << endl;
					mydata = vert[i];
					cout << "Vert: "<< vert[i] << endl;
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
					while (sync.read() == true) wait();
					//fifoVectorDifferenceThreshold.write(vert[i]);
				}
			}
			n_inicio = -1;
			n_fim = -1;
			
		}
		
	}
	cout << "Count: " << count << endl;

}