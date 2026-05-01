#!/usr/bin/env python3

import socket  # Provides network socket operations
import sys     # Used for command-line arguments and exit handling
import struct  # Used for packing and unpacking binary data

def main():
    if len(sys.argv) != 3:
        print(f"Usage: {sys.argv[0]} <IP> <Port>")
        sys.exit(1)

    target_ip_str = sys.argv[1]  # Target IP address given on the command line
    target_port_val = int(sys.argv[2])  # Target port number converted to integer

    # Convert IP to 32-bit network format (4 bytes)
    try:
        ip_net = socket.inet_aton(target_ip_str)  # Convert dotted-quad string to 4-byte binary form
    except socket.error:
        print("Invalid IP address")
        sys.exit(1)

    # Convert Port to 16-bit network format (2 bytes)
    # 'H' is unsigned short (16-bit), '>' is Big-Endian (Network Order)
    port_net = struct.pack('>H', target_port_val)
    # Construct the packet: IP (4) + \0 (1) + Port (2) + \0 (1)
    # We use byte concatenation to build the 8-byte buffer
    packet = ip_net + b'\x00' + port_net + b'\x00'

    # Info print
    # To get the uint32 value from network bytes:
    ip_uint32 = struct.unpack('>I', ip_net)[0]
    print(f"IP is {target_ip_str}; uint32 is {ip_uint32}")
    print(f"Port is {target_port_val}; uint16 is {target_port_val}")

    # Send packet via UDP
    server_address = ('127.0.0.1', 1025)  # Using localhost as the destination
    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as sock:
        sock.sendto(packet, server_address)  # Send the 8-byte packet to the target server

if __name__ == "__main__":
    main()
