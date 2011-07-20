//
// io_service_pool.cpp
// ~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2010 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "server.hpp"
#include <stdexcept>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>

namespace Hydra {

io_service_pool::io_service_pool(std::size_t pool_size) : m_next(0), m_size(pool_size){
	if (pool_size == 0)
		throw std::runtime_error("io_service_pool size is 0");

	// Give all the io_services work to do so that their run() functions will not
	// exit until they are explicitly stopped.
	for (std::size_t i = 0; i < pool_size; ++i)
	{
		io_service_ptr io_service(new boost::asio::io_service);
		work_ptr work(new boost::asio::io_service::work(*io_service));
		m_services.push_back(io_service);
		m_work.push_back(work);
	}
}

void io_service_pool::run()
{
	// Create a pool of threads to run all of the io_services.
	std::vector<boost::shared_ptr<boost::thread> > threads;
	for (std::size_t i = 0; i < m_size; ++i)
	{
		boost::shared_ptr<boost::thread> thread(new boost::thread(
					boost::bind(&boost::asio::io_service::run, m_services[i])));
		threads.push_back(thread);
	}

	// Wait for all threads in the pool to exit.
	for (std::size_t i = 0; i < threads.size(); ++i)
		threads[i]->join();
}

void io_service_pool::stop()
{
	// Explicitly stop all io_services.
	for (std::size_t i = 0; i < m_size; ++i)
		m_services[i]->stop();
}

boost::asio::io_service& io_service_pool::get_io_service()
{
	// Use a round-robin scheme to choose the next io_service to use.
	boost::asio::io_service& io_service = *m_services[m_next];
	++m_next;
	if (m_next == m_size)
		m_next = 0;
	return io_service;
}

}

