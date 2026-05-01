#!/usr/bin/env python3

import socket  # Provides socket creation and network methods
import sys     # Used to read command-line arguments

HOST = '127.0.0.1'               # Localhost address to bind the server to
PORT = int(sys.argv[1])          # Server port taken from command line

with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as s:  # Create a UDP socket
    s.bind((HOST, PORT))  # Bind the socket to the local address and port
    data, addr = s.recvfrom(1024)  # Receive up to 1024 bytes and capture sender address
    print('Here is the message: %s' % data.decode('utf-8'))  # Decode and print the received message
    s.sendto('I got your message'.encode('utf-8'), addr)  # Send a reply back to the sender

