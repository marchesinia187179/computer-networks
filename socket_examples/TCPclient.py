#!/usr/bin/env python3

import socket  # Provides network socket functionality
import sys     # Allows reading command-line arguments

HOST = sys.argv[1]            # Remote server host or IP address from command line
PORT = int(sys.argv[2])       # Remote server port number converted to integer

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:  # Create a TCP socket using IPv4
    s.connect((HOST, PORT))  # Establish a TCP connection to the server
    msg = input('Please enter the message: ')  # Prompt the user for a message
    s.sendall(msg.encode('utf-8'))  # Send the entered text encoded as UTF-8 bytes
    data = s.recv(1024)  # Receive up to 1024 bytes from the server
    s.close()  # Close the socket connection explicitly

print('Received: %s' % data.decode('utf-8'))  # Decode received bytes and print the server response
