#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <systemc.h>
#include "lerImagem.h"
#include "RGB2Gray.h"
#include "sysDilate.h"
#include "difference_hist.h"
#include "threshold.h"
#include "segmentation.h"
#include "simple_bus_master_blocking.h"
#include "simple_bus_master_non_blocking.h"
#include "simple_bus_master_direct.h"
#include "simple_bus_slow_mem.h"
#include "simple_bus.h"
#include "simple_bus_fast_mem.h"
#include "simple_bus_arbiter.h"
//#include "simple_bus_test.h"

int sc_main(int argc, char *argv[]) {
	cv::Mat src = cv::imread(path_frame);
	sc_clock C1;
	sc_signal <bool, SC_MANY_WRITERS> syncbus;
	sc_signal <bool, SC_MANY_WRITERS> syncbusT;
<<<<<<< HEAD
	sc_signal <bool, SC_MANY_WRITERS> syncVert;
	sc_signal <bool, SC_MANY_WRITERS> syncHorz;
=======
>>>>>>> 10bccc3c8bd711bf3b6ec6d56ff7d9dea0fedb96

	sc_fifo <int> rowsRGB2dilate;
	sc_fifo <int> colsRGB2dilate;

	sc_fifo <int> rowsRGB2dilate_T;
	sc_fifo <int> colsRGB2dilate_T;

	sc_fifo <int> lerToGrayR(src.cols*src.rows);
	sc_fifo <int> lerToGrayG(src.cols*src.rows);
	sc_fifo <int> lerToGrayB(src.cols*src.rows);
	sc_fifo <int> lerToGrayROWS(1);
	sc_fifo <int> lerToGrayCOLS(1);

	sc_fifo <int> lerToGrayR_T(src.cols*src.rows);
	sc_fifo <int> lerToGrayG_T(src.cols*src.rows);
	sc_fifo <int> lerToGrayB_T(src.cols*src.rows);
	sc_fifo <int> lerToGrayROWS_T(1);
	sc_fifo <int> lerToGrayCOLS_T(1);

	sc_fifo <int> lerToGrayR_S(src.cols*src.rows);
	sc_fifo <int> lerToGrayG_S(src.cols*src.rows);
	sc_fifo <int> lerToGrayB_S(src.cols*src.rows);
	sc_fifo <int> lerToGrayROWS_S(1);
	sc_fifo <int> lerToGrayCOLS_S(1);

	sc_fifo <int> grayToDilatePixel(src.cols*src.rows);
	sc_fifo <int> grayToDilateROWS(1);
	sc_fifo <int> grayToDilateCOLS(1);


	sc_fifo <int> grayToDilatePixel_T(src.cols*src.rows);
	sc_fifo <int> grayToDilateROWS_T(1);
	sc_fifo <int> grayToDilateCOLS_T(1);

	sc_fifo <int> DilateToHistogramPixel(src.cols*src.rows);
	sc_fifo <int> DilateToHistogramROWS(1);
	sc_fifo <int> DilateToHistogramCOLS(1);

	sc_fifo <int> DilateToHistogramPixel_T(src.cols*src.rows);
	sc_fifo <int> DilateToHistogramROWS_T(1);
	sc_fifo <int> DilateToHistogramCOLS_T(1);

	sc_fifo <int> DifferenceVect(src.rows);
	sc_fifo <int> DifferenceVectROWS(1);
	sc_fifo <int> DifferenceVectAverage(1);
	sc_fifo <int> DifferenceVectPosiMax(1);

	sc_fifo <int> DifferenceHorz(src.cols);
	sc_fifo <int> DifferenceHorzROWS(1);
	sc_fifo <int> DifferenceHorzAverage(1);
	sc_fifo <int> DifferenceHorzPosiMax(1);

	sc_fifo <int> DifferenceVectThreshold(src.rows);
	sc_fifo <int> DifferenceHorzThreshold(src.cols);

	simple_bus_arbiter arbiter("arbiter");
	simple_bus_slow_mem mem_slow("mem_slow", 0x00, 0xff, 1);
	simple_bus bus("bus");
	bus.clock(C1);
	bus.arbiter_port(arbiter);
	bus.slave_port(mem_slow);
	mem_slow.clock(C1);

		

	lerImagem lerImagem("lerImagem");
	lerImagem.fifo_pixelR(lerToGrayR);
	lerImagem.fifo_pixelG(lerToGrayG);
	lerImagem.fifo_pixelB(lerToGrayB);
	lerImagem.fifo_pixelR_T(lerToGrayR_T);
	lerImagem.fifo_pixelG_T(lerToGrayG_T);
	lerImagem.fifo_pixelB_T(lerToGrayB_T);
	lerImagem.fifo_pixelR_S(lerToGrayR_S);
	lerImagem.fifo_pixelG_S(lerToGrayG_S);
	lerImagem.fifo_pixelB_S(lerToGrayB_S);
	lerImagem.o_COLS(lerToGrayCOLS);
	lerImagem.o_ROWS(lerToGrayROWS);
	lerImagem.o_COLS_T(lerToGrayCOLS_T);
	lerImagem.o_ROWS_T(lerToGrayROWS_T);
	lerImagem.o_COLS_S(lerToGrayCOLS_S);
	lerImagem.o_ROWS_S(lerToGrayROWS_S);

<<<<<<< HEAD
	RGB2Gray RGB2Gray_T("RGB2Gray_T", 1, 0x4c, false, 300);
=======
	RGB2Gray RGB2Gray_T("RGB2Gray_T", 3, 0x4c, false, 300);
>>>>>>> 10bccc3c8bd711bf3b6ec6d56ff7d9dea0fedb96
	RGB2Gray_T.clock(C1);
	RGB2Gray_T.bus_port(bus);
	RGB2Gray_T.sync(syncbusT);
	//RGB2Gray_I.send(valid2fpga);
	//RGB2Gray_I.receive(req2fpga);
	RGB2Gray_T.fifo_pixelR(lerToGrayR_T);
	RGB2Gray_T.fifo_pixelG(lerToGrayG_T);
	RGB2Gray_T.fifo_pixelB(lerToGrayB_T);
	//RGB2Gray_I.fifo_pixelGray(grayToDilatePixel);
	RGB2Gray_T.i_COLS(lerToGrayCOLS_T);
	RGB2Gray_T.i_ROWS(lerToGrayROWS_T);
	RGB2Gray_T.cols_o(colsRGB2dilate_T);
	RGB2Gray_T.rows_o(rowsRGB2dilate_T);
	//RGB2Gray_I.o_COLS(grayToDilateCOLS);
	//RGB2Gray_I.o_ROWS(grayToDilateROWS);

<<<<<<< HEAD
	RGB2Gray RGB2Gray_I("RGB2Gray_I", 2, 0x2c, false, 300);
=======
	RGB2Gray RGB2Gray_I("RGB2Gray_I", 4, 0x2c, false, 300);
>>>>>>> 10bccc3c8bd711bf3b6ec6d56ff7d9dea0fedb96
	RGB2Gray_I.clock(C1);
	RGB2Gray_I.bus_port(bus);
	RGB2Gray_I.sync(syncbus);
	//RGB2Gray_I.send(valid2fpga);
	//RGB2Gray_I.receive(req2fpga);
	RGB2Gray_I.fifo_pixelR(lerToGrayR);
	RGB2Gray_I.fifo_pixelG(lerToGrayG);
	RGB2Gray_I.fifo_pixelB(lerToGrayB);
	//RGB2Gray_I.fifo_pixelGray(grayToDilatePixel);
	RGB2Gray_I.i_COLS(lerToGrayCOLS);
	RGB2Gray_I.i_ROWS(lerToGrayROWS);
	RGB2Gray_I.cols_o(colsRGB2dilate);
	RGB2Gray_I.rows_o(rowsRGB2dilate);
	//RGB2Gray_I.o_COLS(grayToDilateCOLS);
	//RGB2Gray_I.o_ROWS(grayToDilateROWS);

	/*RGB2Gray RGB2Gray_T("RGB2Gray_T");
	RGB2Gray_T.fifo_pixelR(lerToGrayR_T);
	RGB2Gray_T.fifo_pixelG(lerToGrayG_T);
	RGB2Gray_T.fifo_pixelB(lerToGrayB_T);
	RGB2Gray_T.fifo_pixelGray(grayToDilatePixel_T);
	RGB2Gray_T.i_COLS(lerToGrayCOLS_T);
	RGB2Gray_T.i_ROWS(lerToGrayROWS_T);
	RGB2Gray_T.o_COLS(grayToDilateCOLS_T);
	RGB2Gray_T.o_ROWS(grayToDilateROWS_T);*/
	
<<<<<<< HEAD
	sysDilate sysDilate_I("sysDilate_I", 2, 0x2c, false, 300);
=======
	sysDilate sysDilate_I("sysDilate_I", 4, 0x2c, false, 300);
>>>>>>> 10bccc3c8bd711bf3b6ec6d56ff7d9dea0fedb96
	sysDilate_I.clock(C1);
	sysDilate_I.bus_port(bus);
	sysDilate_I.sync(syncbus);
	//sysDilate_I.fifo_pixelGray(grayToDilatePixel);
	sysDilate_I.fifo_pixelDilate(DilateToHistogramPixel);
	//sysDilate_I.i_COLS(grayToDilateCOLS);
	//sysDilate_I.i_ROWS(grayToDilateROWS);
	sysDilate_I.o_COLS(DilateToHistogramCOLS);
	sysDilate_I.o_ROWS(DilateToHistogramROWS);
	sysDilate_I.i_COLS(colsRGB2dilate);
	sysDilate_I.i_ROWS(rowsRGB2dilate);
	//sysDilate_I.receive(valid2fpga);
	//sysDilate_I.send(req2fpga);


<<<<<<< HEAD
	sysDilate sysDilate_T("sysDilate_T", 1, 0x4c, false, 300);
=======
	sysDilate sysDilate_T("sysDilate_T", 3, 0x4c, false, 300);
>>>>>>> 10bccc3c8bd711bf3b6ec6d56ff7d9dea0fedb96
	sysDilate_T.clock(C1);
	sysDilate_T.bus_port(bus);
	sysDilate_T.sync(syncbusT);
	//sysDilate_I.fifo_pixelGray(grayToDilatePixel);
	sysDilate_T.fifo_pixelDilate(DilateToHistogramPixel_T);
	//sysDilate_I.i_COLS(grayToDilateCOLS);
	//sysDilate_I.i_ROWS(grayToDilateROWS);
	sysDilate_T.o_COLS(DilateToHistogramCOLS_T);
	sysDilate_T.o_ROWS(DilateToHistogramROWS_T);
	sysDilate_T.i_COLS(colsRGB2dilate_T);
	sysDilate_T.i_ROWS(rowsRGB2dilate_T);
	//sysDilate_I.receive(valid2fpga);
	//sysDilate_I.send(req2fpga);

	difference_hist vect("vect");
	vect.fifo_pixelDilate(DilateToHistogramPixel);
	vect.fifoVectorDifference(DifferenceVect);
	vect.i_COLS(DilateToHistogramCOLS);
	vect.i_ROWS(DilateToHistogramROWS);
	vect.o_ROWS(DifferenceVectROWS);
	vect.o_average(DifferenceVectAverage);
	vect.o_posi_max(DifferenceVectPosiMax);

	difference_hist horz("horz");
	horz.fifo_pixelDilate(DilateToHistogramPixel_T);
	horz.fifoVectorDifference(DifferenceHorz);
	horz.i_COLS(DilateToHistogramCOLS_T);
	horz.i_ROWS(DilateToHistogramROWS_T);
	horz.o_ROWS(DifferenceHorzROWS);
	horz.o_average(DifferenceHorzAverage);
	horz.o_posi_max(DifferenceHorzPosiMax);

	threshold threshold_vect("threshold_vect", 4, 0x6c, false, 300);
	threshold_vect.clock(C1);
	threshold_vect.sync(syncVert);
	threshold_vect.bus_port(bus);
	threshold_vect.fifoVectorDifference(DifferenceVect);
	//threshold_vect.fifoVectorDifferenceThreshold(DifferenceVectThreshold);
	threshold_vect.i_ROWS(DifferenceVectROWS);
	threshold_vect.i_average(DifferenceVectAverage);
	threshold_vect.i_posi_max(DifferenceVectPosiMax);

	threshold threshold_horz("threshold_horz", 4, 0x9c, false, 300);
	threshold_horz.clock(C1);
	threshold_horz.sync(syncHorz);
	threshold_horz.bus_port(bus);
	threshold_horz.fifoVectorDifference(DifferenceHorz);
	//threshold_horz.fifoVectorDifferenceThreshold(DifferenceHorzThreshold);
	threshold_horz.i_ROWS(DifferenceHorzROWS);
	threshold_horz.i_average(DifferenceHorzAverage);
	threshold_horz.i_posi_max(DifferenceHorzPosiMax);

	segmentation segmentation("segmentation", 4, 0x6c, 0x9c, false, 300);
	segmentation.clock(C1);
	segmentation.sync_horz(syncHorz);
	segmentation.sync_vert(syncVert);
	segmentation.bus_port(bus);
	//segmentation.fifoVectorDifferenceVertThreshold(DifferenceVectThreshold);
	//segmentation.fifoVectorDifferenceHorzThreshold(DifferenceHorzThreshold);
	segmentation.i_ROWS(lerToGrayROWS_S);
	segmentation.i_COLS(lerToGrayCOLS_S);
	segmentation.fifo_pixelR(lerToGrayR_S);
	segmentation.fifo_pixelG(lerToGrayG_S);
	segmentation.fifo_pixelB(lerToGrayB_S);
	syncbus = false;
	syncbusT = false;
<<<<<<< HEAD
	syncHorz = false;
	syncVert = false;
=======
>>>>>>> 10bccc3c8bd711bf3b6ec6d56ff7d9dea0fedb96
	sc_start();

	return 0;
}