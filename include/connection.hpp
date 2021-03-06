//
// connection.hpp
// ~~~~~~~~~~~~~~
//
// Copyright (c) 2011-2011 Richard J. Whitehouse (richard at richardwhiuk dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef HYDRA_FILE_CONNECTION_HPP
#define HYDRA_FILE_CONNECTION_HPP

#include "request.hpp"
#include "response.hpp"

#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

namespace Hydra {

class Connection : public boost::enable_shared_from_this<Connection> {

public:

	typedef boost::shared_ptr<Connection> pointer;

	static pointer Create(std::string tag);
	~Connection();

	Request& request();
	Response& response();

	const std::string& tag();

	void bind_finish(boost::function<void(Hydra::Connection*)>);

private:

	Connection(std::string tag);

	Request m_request;
	Response m_response;

	std::string m_tag;

	boost::function<void(Hydra::Connection*)> m_finish;

};

}

#endif

