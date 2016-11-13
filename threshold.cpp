#include "threshold.h"

void threshold::process() {

	LENGTH_ROWS = i_ROWS.read();
	POSI_MAX = i_posi_max.read();
	AVERAGE = i_average.read();
	std::vector<int> vert;

	for (int i = 0; i < LENGTH_ROWS; i++)
	{
		vert.push_back(fifoVectorDifference.read());
	}
	n_inicio = -1;
	n_fim = -1;
	for (int i = 0; i < LENGTH_ROWS; i++)
	{
		if (vert[i] < AVERAGE)
		{
			if (n_inicio != -1) {
				n_fim = i;

			}
			fifoVectorDifferenceThreshold.write(0);
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
					fifoVectorDifferenceThreshold.write(0);
				}
			}
			else {
				for (int n = n_inicio; n <= n_fim; n++)
				{
					fifoVectorDifferenceThreshold.write(vert[i]);
				}
			}
			n_inicio = -1;
			n_fim = -1;
		}
	}


}