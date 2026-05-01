#!/usr/bin/env python3

import socket  # Socket module for network communication
import struct  # Struct module for packing and unpacking binary data

def main():
    # Setup UDP Socket
    sockfd = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)  # Create a UDP socket for IPv4
    server_address = ('0.0.0.0', 1025)  # Listen on all interfaces at port 1025
    try:
        sockfd.bind(server_address)  # Bind the socket so it can receive datagrams
    except OSError as e:
        print(f"Bind failed: {e}")
        return
    # Receive the 8-byte packet
    # data is the bytes object, addr is (ip, port) of the sender
    data, addr = sockfd.recvfrom(8)

    if len(data) < 8:
        print("Received incomplete packet")
        sockfd.close()
        return

    # Extract data using slicing
    # buffer[0:4] -> IP (4 bytes)
    # buffer[5:7] -> Port (2 bytes)
    ip_bytes = data[0:4]
    port_bytes = data[5:7]

    # Convert binary to human-readable format
    # '>I' = Unsigned Int (32-bit), Big-Endian
    # '>H' = Unsigned Short (16-bit), Big-Endian
    rec_ip_val = struct.unpack('>I', ip_bytes)[0]
    rec_port_val = struct.unpack('>H', port_bytes)[0]
    
    # Convert the 4 bytes directly to a dotted-decimal string and print
    ip_str = socket.inet_ntoa(ip_bytes)
    print(f"uint32 is {rec_ip_val}; IP is {ip_str}")
    print(f"uint16 is {rec_port_val}; Port is {rec_port_val}")

    sockfd.close()  # Close the UDP socket after processing the packet

if __name__ == "__main__":
    main()
