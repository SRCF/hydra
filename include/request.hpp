//
// request.hpp
// ~~~~~~~~~~~
//
// Copyright (c) 2003-2010 Christopher M. Kohlhoff (chris at kohlhoff dot com)
// Copyright (c) 2011-2011 Richard J. Whitehouse (richard at richardwhiuk dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef HYDRA_FILE_REQUEST_HPP
#define HYDRA_FILE_REQUEST_HPP

#include <string>
#include <vector>
#include "header.hpp"

namespace Hydra {

/// A request received from a client.
struct Request {
	std::string method;
	std::string uri;
	int http_version_major;
	int http_version_minor;
	std::vector<Header> headers;
};

}

#endif

