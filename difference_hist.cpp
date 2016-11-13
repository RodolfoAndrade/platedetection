#include "difference_hist.h"

void difference_hist::process() {

	sum = 0;
	max_vert = 0;
	total_sum = 0;
	difference = 0;
	maximum = 0;
	average = 0;
	n = 0;
	m = 0;

	LENGTH_COLS = i_COLS.read();
	LENGTH_ROWS = i_ROWS.read();
	o_ROWS.write(LENGTH_ROWS);

	for (int i = 0; i < LENGTH_ROWS; i++)
	{
		sum = 0;
		for (int j = 1; j < LENGTH_COLS; j++)
		{
			if (i == 0 && j == 0) {
				n = fifo_pixelDilate.read();
			}
			m = fifo_pixelDilate.read();
			difference = abs(n - m);
			if (difference > 25) {
				sum = sum + difference;
			}
			n = m;
		}
		vert.push_back(sum);

		if (sum > maximum)
		{
			max_vert = i;
			maximum = sum;
		}
		total_sum = total_sum + sum;
	}
	o_average.write(total_sum / LENGTH_ROWS);
	o_posi_max.write(max_vert);

	for (int i = 0; i < 20; i++)
	{
		fifoVectorDifference.write(vert[i]);
	}

	for (int i = 20; i < LENGTH_ROWS - 20; i++)
	{
		sum = 0;
		for (int j = i - 20; j <= i + 20; j++) {
			sum = sum + vert[j];
		}
		fifoVectorDifference.write(sum / 41);
	}

	for (int i = LENGTH_ROWS - 20; i < LENGTH_ROWS; i++)
	{
		fifoVectorDifference.write(vert[i]);
	}
}