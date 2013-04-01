Hydra
=====

Distributed under the GNU General Public License, Version 2.0 - see accompanying file `LICENSE.txt` or copy at `http://www.gnu.org/licenses/gpl-2.0.txt`.

This daemon is designed to multiplex between different HTTP servers distinguished by the `Host:` header.

Usage
-----

```
$ hydra [config file]
```

With no configuration file it expects it to be in `/etc/hydra.conf`.

Building
--------

```
$ cd build
$ cmake ..
$ make
$ sudo make install
```

At this point, there is a copy of the `hydra` daemon installed in `/usr/local/sbin/hydra`.

Configuration
-------------

Hydra is configured by providing a configuration file.

A sample configuration file can be found in `samples/etc.conf`. This should be edited and placed in `/etc/hydra.conf` by default.

A sample Upstart init file can be found in `samples/upstart.conf`. This should be copied to `/etc/init/`.

Sample Apache2 configuration files can be found in `samples/apache2/`.
A child config file should be created for each Apache2 server desired using the `child.conf` as a example.
Base configuration can be done in the supplied `base.conf` file.

### hydra.conf

`hydra.conf` is separated into sections. Each section is demarcated by a pair of square brackets. Each section name consists of
a type, followed by a name. Valid types are: `default`, `client` and `server`.

`default` specifies default values for one of the connectors. The name should be the name of the connector, e.g. apache2.

`client` specifies a client connection, specified by a address, a port and what connections should be tagged with.

`server` specifies a server connection, specified by a server, a port, and a list of hostnames it will handle and a list of tags it accepts.

Each section contains properties in a `key=value` format. Additionally, some properties may be specified by tag, by specifying them in a `key:tag=value` format.

#### Tags

Tags in Hydra provide a mechanism for routing requests based on which client connection they arrive on. This can allow request routing based on whether a
request is made over SSL or not by tagging SSL clients with a different tag to those which arrive on plain HTTP clients.

#### Clients

Two types of client are supported, `plain` and `ssl`. Plain provides for HTTP connections, SSL for HTTPS connections.

#### Servers

The following server types are supported:

- `apache2` - Apache2 server, spawned on demand.
- `nginx` - Nginx server, spawned on demand.
- `proxy` - Proxy to a backend server over HTTP.
- `sslproxy` - Proxy to a backend server over HTTPS.
- `redirect` - Redirect the user to a different URL.

Developing
----------

Suggested build environment is Debian/Ubuntu Linux.

For Debian:

* `libboost-dev`
* `libboost-thread-dev`
* `libboost-system-dev`
* `cmake`
* `git`
* `libssl-dev`

