#pragma once

#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <systemc.h>
#include <queue>
#include "simple_bus_types.h"
#include "simple_bus_blocking_if.h"


using namespace std;

SC_MODULE(sysDilate) {
	// ports
	sc_in_clk clock;
	sc_port<simple_bus_blocking_if> bus_port;

	queue<int> L0;
	queue<int> L1;
	int p1, p2, p3, p4, p5, temp;
	int LENGTH_COLS, LENGTH_ROWS;

	//sc_fifo_in<int> i_COLS, i_ROWS;
	//sc_fifo_in<int> fifo_pixelGray;

	sc_fifo_out<int> o_COLS, o_ROWS;
	sc_fifo_out<int> fifo_pixelDilate;
	//sc_in<sc_bit> receive;
	//sc_out<sc_bit> send;
	sc_inout<bool> sync;

	SC_HAS_PROCESS(sysDilate);

	sysDilate(sc_module_name name_
		, unsigned int unique_priority
		, unsigned int address
		, bool lock
		, int timeout)
		: sc_module(name_)
		, m_unique_priority(unique_priority)
		, m_address(address)
		, m_lock(lock)
		, m_timeout(timeout)
	{
		// process declaration
		SC_THREAD(main_action);
		//sensitive << sync;
		sensitive << clock.pos();
		//sensitive << receive;
	}
	// process
	void main_action();

private:
	unsigned int m_unique_priority;
	unsigned int m_address;
	bool m_lock;
	int m_timeout;

}; // end class simple_bus_master_blocking
