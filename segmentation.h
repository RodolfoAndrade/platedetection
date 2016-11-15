#pragma once
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <systemc.h>
#include <vector>
#include "simple_bus_types.h"
#include "simple_bus_blocking_if.h"

SC_MODULE(segmentation) {
	int vert;
	std::vector<int> horz;

	// ports
	sc_in_clk clock;
	sc_port<simple_bus_blocking_if> bus_port;

	sc_inout<bool> sync_vert;
	sc_inout<bool> sync_horz;

	int r, g, b;
	int LENGTH_COLS, LENGTH_ROWS;
	sc_fifo_in<int> i_COLS, i_ROWS;
	//sc_fifo_in<int> fifoVectorDifferenceVertThreshold;
	//sc_fifo_in<int> fifoVectorDifferenceHorzThreshold;
	sc_fifo_in<int> fifo_pixelR;
	sc_fifo_in<int> fifo_pixelG;
	sc_fifo_in<int> fifo_pixelB;

	SC_HAS_PROCESS(segmentation);

	// constructor
	segmentation(sc_module_name name_
		, unsigned int unique_priority
		, unsigned int address_vert
		, unsigned int address_horz
		, bool lock
		, int timeout)
		: sc_module(name_)
		, m_unique_priority(unique_priority)
		, m_address_vert(address_vert)
		, m_address_horz(address_horz)
		, m_lock(lock)
		, m_timeout(timeout)
	{
		// process declaration
		SC_THREAD(main_action);
		sensitive << clock.pos();
		//sensitive << sync;
		//sensitive << receive;
	}
	// process
	void main_action();

private:
	unsigned int m_unique_priority;
	unsigned int m_address_vert;
	unsigned int m_address_horz;
	bool m_lock;
	int m_timeout;

}; // end class simple_bus_master_blocking
