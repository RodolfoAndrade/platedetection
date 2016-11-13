#include "generateImage.h"


void generateImage::process() {

	src = imread("arquivos/carro0.bmp");

	//TESTE
	//src_gray.create(src.size(), CV_8UC1);





	for (int i = 0; i < src.rows; i++)

	{

		for (int j = 1; j < src.cols; j++)

		{

			pixel = src.at<Vec3b>(i, j);

			//Transforma em grayscale

			output.write((int)((4897 * pixel[2] + 9617 * pixel[1] + 1868 * pixel[0]) >> 14));

		}

	}
}