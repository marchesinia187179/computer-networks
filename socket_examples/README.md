# prof Socket Examples

This folder contains simple socket programming examples in C and Python, demonstrating TCP and UDP client/server communication, plus a few utility files for archive-based transfer tests.

## File Overview

### TCP examples

- `TCPclient.c`
  - A C TCP client that connects to a server using hostname and port, sends a user-provided message, and prints the server reply.
  - Uses `socket()`, `connect()`, `write()`, and `read()`.

- `TCPserver.c`
  - A C TCP server that listens on a user-specified port, accepts one incoming connection, reads a message from the client, and replies with a fixed string.
  - Uses `socket()`, `bind()`, `listen()`, `accept()`, `read()`, and `write()`.

- `TCPclient.py`
  - A Python TCP client equivalent that connects to a server, sends a typed message, receives the response, and prints it.
  - Uses Python's `socket` module and `sendall()` / `recv()`.

- `TCPserver.py`
  - A Python TCP server that accepts a connection, receives a message from a client, prints it, and sends a fixed acknowledgement back.

### UDP examples

- `UDPclient.c`
  - A C UDP client that resolves a hostname, sends a message to a remote UDP server with `sendto()`, then waits for and prints the response with `recvfrom()`.
  - Demonstrates connectionless message delivery and address handling.

- `UDPserver.c`
  - A C UDP server that binds to a local port, receives a single datagram from a client, prints the received text, and replies to the sender.
  - Uses `recvfrom()` and `sendto()`.

- `UDPclient.py`
  - A Python UDP client that binds a UDP socket and sends a user message to a server address, then receives and prints the reply.

- `UDPserver.py`
  - A Python UDP server that binds to localhost and a specified port, receives a single UDP message, prints it, and sends a response.

### IP notation UDP examples

- `ip_notation_clientUDP.c`
  - A C UDP client that takes an IP and port as command-line arguments, converts them into network-byte-order binary format, creates an 8-byte packet, and sends it to a fixed UDP server address.
  - Demonstrates `inet_aton()`, `htons()`, and manual packet construction.

- `ip_notation_serverUDP.c`
  - A C UDP server that listens on port 1025, receives an 8-byte packet, extracts the embedded IP and port fields, converts them back to human-readable form, and prints the values.

- `ip_notation_clientUDP.py`
  - A Python UDP client equivalent that packs an IP and port into an 8-byte packet and sends it to `127.0.0.1:1025`.
  - Uses `socket.inet_aton()` and `struct.pack()`.

- `ip_notation_serverUDP.py`
  - A Python UDP server that receives the same 8-byte packet structure and unpacks the binary IP and port values for display.

### Archive transfer examples

- `ar_client.py`
  - A Python TCP client that builds a simple Unix `ar`-style archive stream from provided files and sends it to a server.
  - It constructs 60-byte file headers and transmits file contents in chunks.

- `ar_clientTCP.c`
  - A C version of an archive sender that connects to a server and sends an archive global header followed by file headers and file contents.
  - Demonstrates manual header assembly, file I/O, and TCP socket writes.

- `ar_client.sh`
  - A shell script that builds a temporary `ar` archive from provided files and sends it to a server using `nc` (netcat).
  - It cleans up the temporary archive after sending.

- `test_ar_client.sh`
  - A shell script that sets up a local listener, creates a sample archive, invokes a specified client (`client.py` or another executable), and validates the received archive structure.
  - It compares data using `ar` and `md5sum` and reports whether the archive contents match.

### Support files

- `Makefile`
  - Contains build rules and targets for compiling the C example programs.
  - Use this file to compile sources with a single command if configured for this project.

- `fear.txt`
  - A plain-text sample file used by the archive transfer tests or examples.

- `prayer.txt`
  - Another sample text file used by the archive transfer tests or examples.

## Usage Notes

- C programs typically require compilation before running. Example:
  ```sh
  gcc TCPserver.c -o TCPserver
  gcc TCPclient.c -o TCPclient
  ```

- Python scripts are executable with `python3`:
  ```sh
  python3 TCPclient.py 127.0.0.1 3000
  ```

- UDP examples use `sendto()` / `recvfrom()` for connectionless communication, while TCP examples use `connect()` / `accept()` for stream-oriented communication.

- The `ip_notation_*` examples illustrate how to pack and unpack IP and port values in network byte order.

## Notes

This README is intended to document the purpose of each file in the `prof` folder for GitHub and to help you understand the structure of the socket programming examples.
