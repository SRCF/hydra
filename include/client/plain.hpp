//
// plain.hpp
// ~~~~~~~~~
//
// Copyright (c) 2011-2011 Richard J. Whitehouse (richard at richardwhiuk dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "client.hpp"
#include "config.hpp"

#include "connection.hpp"

#include <string>

#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>

namespace Hydra {

namespace Client {

class Plain : public Base {

public:

	Plain(std::string name, Config::Section config, Daemon& hydra);
	virtual ~Plain();

	virtual void run(boost::asio::io_service& io_service);

	class Connection : public boost::enable_shared_from_this<Connection> {

	public:

		typedef boost::shared_ptr<Connection> pointer;

		static pointer Create(boost::asio::io_service& io_service, Daemon& hydra);
		~Connection();

		void start();
	
		boost::asio::ip::tcp::socket& socket();
	
	private:

		Connection(boost::asio::io_service& io_service, Daemon& hydra);

		void read();

		void handle_read(const boost::system::error_code& e, std::size_t bytes_transferred);

		void write();

		void handle_write(const boost::system::error_code& e, std::size_t bytes_transferred);

		void finish();

		void handle_finish(const boost::system::error_code& e, std::size_t bytes_transferred);

		Hydra::Connection::pointer m_connection;

		Daemon& m_hydra;

		boost::array<char, 8192> m_buffer_in;

		std::string m_buffer_out;

		boost::asio::ip::tcp::socket m_socket;
	
	};

private:

	void accept();

	void handle(Connection::pointer connect, const boost::system::error_code& error);

	boost::asio::ip::tcp::acceptor* m_accept;

};

}

}

