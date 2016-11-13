#pragma once
#ifndef __simple_bus_master_blocking_h
#define __simple_bus_master_blocking_h

#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <systemc.h>
#include "simple_bus_types.h"
#include "simple_bus_blocking_if.h"

SC_MODULE(RGB2Gray) {

	// ports
	sc_in_clk clock;
	sc_port<simple_bus_blocking_if> bus_port;


	int r, g, b;
	int LENGTH_COLS, LENGTH_ROWS;
	sc_fifo_in<int> i_COLS, i_ROWS;
	sc_fifo_in<int> fifo_pixelR;
	sc_fifo_in<int> fifo_pixelG;
	sc_fifo_in<int> fifo_pixelB;
	sc_inout<bool> sync;
	//sc_out<sc_bit> send;
	//sc_in<sc_bit> receive;

	SC_HAS_PROCESS(RGB2Gray);

	//sc_fifo_out<int> o_COLS, o_ROWS;
	//sc_fifo_out<int> fifo_pixelGray;

	// constructor
	RGB2Gray(sc_module_name name_
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
		sensitive << clock.pos();
		//sensitive << sync;
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

#endif