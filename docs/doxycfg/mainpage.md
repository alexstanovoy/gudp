# A simple UDP client-server library for Game Networking

### Abstract

It's known real-time games require UDP protocol for game networking for several reasons. This library helps to build networking infrastructure for your game by implementing a thin layer between OS sockets and your infrastructure.

### Requirements

This library needs only `meson` build system for building. Also, for contributing you'll need `doxygen`, `clang-format` and `clang-tidy`. For details, read `BUILDING.md` in the root directory of the project.

### What are the basic knowledge required?

There are quite a little things to know about the library to work with it.

Firstly, you should know the following things:

* Functions of the library return `RETCODE` - it's an integer that equal to SUCCESS (or 0) in case of success and >0 when any error occurs. You should check whether function returned successfully and handle errors in other cases.
* Every structure (say `SomeGudpStruct`) is created in your stack, then initialized by the functions with `RETCODE SomeGudpStructInit(GudpStruct* ptr)` name and freed by `void SomeGudpStructDestroy(GudpStruct* ptr)` function. It's guaranteed every `Init` function will not leave any memory in heap in unsuccessful initialization and `Destroy` will work correctly with the structure that was unsuccessfully initialized.
* Functions guaranteed not to modify passed data in any error occurs.
* Some macros defined in `include/common/macro.h` for your conveniance:
  - `RAII(DestroyerName)` macro helps to deal with object allocations. It's equvalent to `__attribute__((cleanup(DestroyerName)))`.
  - `THROW_OR_CONTINUE(RETCODE)` macro helps to throw error further when any error occurs.

Let's take a look at a simple example of usage:

```c
// Creates server and binds a destroyer
RAII(ServerDestroy) Server my_server;

// Creates address and binds a destroyer
RAII(AddressDestroy) Address addr;

// Tries to initialize address, and if an error occurs, returns
// an error code from function. Don't forget: RAII does cleanup
// for us and if initializing was unsuccessful, it won't give
// us any error!
THROW_OR_CONTINUE(
  AddressInit(&addr, some_ip, some_port)
);

// The same
THROW_OR_CONTINUE(
  ServerInit(&my_server, &addr)
);

// Using the structures
...

// There is no need in manual cleanup!
```

### How is it working?

Nextly, the player is an entity who has his unique ID connected with his IP address and port.

There are two main entities: `Server` and `Client`. Also, there are `Address` structure that provides incapsulation for address (IP and port when IPv4) and `Response` with ID of player and data that was received or to be sent.

The core functions of `Server` are:

* `ServerInit` initializes the server and binds it to the specified port.
* `ServerDestroy` disconnects and destroys 
* `ServerReceive` receives exactly one `Response` from server socket. Returned `Response` has information about the ID of client and data sent. If it's first time player sent packet, he's added to the list of players and automatically assigned an ID.
* `ServerSendTo` sends `Response` to the specified player.
* `ServerSend` sends `Response` to all of the players connected on the moment.

The core functions of `Client` are:

* `ClientInit` initializes the client and connects to the specified `Address`.
* `ClientDestroy` destroys the client.
* `ClientReceive` receives one `Response` from the server.
* `ClientSend` sends one `Response` to the server.

### How to use the library?

You can find examples in `tests/` directory.
