# Socket Examples - Network Programming Lab

This folder contains practical networking exercises and demonstrations for learning socket programming and network configuration concepts.

## Folder Structure

### socket_examples

This folder contains basic TCP and UDP socket programming examples in both C and Python, demonstrating client-server communication patterns.

- **TCP Examples**: Simple stream-based communication using TCP sockets
  - C implementations (`TCPclient.c`, `TCPserver.c`)
  - Python implementations (`TCPclient.py`, `TCPserver.py`)

- **UDP Examples**: Connectionless datagram communication
  - C implementations (`UDPclient.c`, `UDPserver.c`)
  - Python implementations (`UDPclient.py`, `UDPserver.py`)

- **IP Notation Examples**: Demonstrates binary IP and port packing/unpacking in network byte order
  - `ip_notation_clientUDP.*` and `ip_notation_serverUDP.*` (C and Python versions)
  - Useful for understanding network byte order conversions

- **Archive Transfer Examples**: Examples of sending file archives over TCP
  - `ar_client.py`, `ar_clientTCP.c`, `ar_client.sh`
  - Includes test scripts for validation

Each file is well-commented and includes usage examples. For detailed documentation, see the [README.md](./socket_examples/README.md) in the socket_examples folder.

### marionnet

This folder contains network simulation exercises created with **Marionnet**, a virtual network simulator. Each `.mar` file represents a complete virtual network topology with multiple devices and configurations.

**Topics covered:**
- **Wiring**: Basic network device connections and topology setup
- **VLAN**: Virtual LAN configuration and inter-VLAN routing
- **DHCP**: Dynamic Host Configuration Protocol server setup and client configuration
- **Routing**: Static and dynamic routing protocols, routing table configuration

Each `.mar` file can be opened in Marionnet to visualize and interact with the network topology. This folder provides hands-on practice with network configuration concepts in a safe, isolated simulation environment.

## Getting Started

1. **Socket Programming Examples**: Navigate to the `socket_examples` folder to compile and run C programs or execute Python scripts.

2. **Network Simulations**: Install Marionnet and open the `.mar` files to practice network configuration and troubleshooting.

## Notes

These exercises are part of a Computer Networks laboratory course and demonstrate practical implementations of fundamental networking concepts.
