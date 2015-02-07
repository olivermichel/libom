Olli's C++ Library
==================

1 General
---------

A general purpose C++ library with a focus on systems and networking tasks.

[https://github.com/olivermichel/libom](https://github.com/olivermichel/libom)


2 Contributors
--------------

* [Oliver Michel](http://ngn.cs.colorado.edu/~oliver)  \<oliver dot michel at editum dot de\>
* [Matthew Monaco](http://ngn.cs.colorado.edu/~matt) \<matt at 0x01b dot net\>

3 Usage
-------

#### Integrate into Project

* Add a git submodule: `git submodule add https://github.com/olivermichel/libom.git`
* Add to your build environment:

```
$(OM_LIBS):
        $(MAKE) -C lib/libom # or whereever the library is located
```

#### Use Static Library

* Choose which sub-libraries you require

```
OM_LIBS  = lib/libom/libom-net.a lib/libom/libom-tools.a
```

* Add the static libraries as dependencies to your main executable

```
$(EXE): $(OBJS) $(OM_LIBS)
	$(CXX) -o $@ $(LDFLAGS) $^
```

#### Test

The library comes with a small set of tests (to be extended). To run tests, change into `/test` directory and simply run `make`. This will build and run all available test suites.

#### Examples

Examples for several parts of the library are located in the `/examples` directory.

4 List of Modules
-----------------

#### net
* DatagramSocket
* RawSocket
* StreamClient
* StreamListener
* StreamConnection
* TunnelDevice

#### tools
* dir
* file
* logger
* random
* string
* time

#### async
* EPollWrapper
* MultiplexInterface
* Multiplexer

#### ipc
* dbus::Connection
* dbus::Message

#### container
* RingBuffer
