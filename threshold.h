#pragma once
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <systemc.h>
#include <vector>
#include "simple_bus_types.h"
#include "simple_bus_blocking_if.h"

SC_MODULE(threshold)
{
	int n_inicio;
	int n_fim;

	// ports
	sc_in_clk clock;
	sc_port<simple_bus_blocking_if> bus_port;

	sc_inout<bool> sync;

	int LENGTH_ROWS, POSI_MAX, AVERAGE;

	sc_fifo_in<int> i_ROWS;
	sc_fifo_in<int> i_average;
	sc_fifo_in<int> i_posi_max;
	sc_fifo_in<int> fifoVectorDifference;

	//sc_fifo_out<int> fifoVectorDifferenceThreshold;

	SC_HAS_PROCESS(threshold);

	// constructor
	threshold(sc_module_name name_
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
