#!/usr/bin/env python3

import socket  # Socket module provides low-level networking functions
import sys     # Sys module for command-line arguments and program exit
import os      # OS module for file system operations such as stat

def create_header(filename):
    """Creates the 60-byte ar header for a given file."""
    try:
        # Get file stats from the filesystem to determine file size
        st = os.stat(filename)
        name = (filename[:15] + "/").ljust(16) # Name: 16 bytes, left-aligned, space-padded, ending in /
        # Meta: Timestamp(12), UID(6), GID(6), Mode(8), Size(10)
        mtime = "0".ljust(12)  # Use a placeholder timestamp
        uid   = "0".ljust(6)   # Use a placeholder user id
        gid   = "0".ljust(6)   # Use a placeholder group id
        mode  = "644".ljust(8) # File permissions in octal-like format
        size  = str(st.st_size).ljust(10)  # File size as a 10-byte field
        terminator = "`\n"  # Header terminator that ends the ar header
        
        # Combine all header fields into one 60-byte string and encode to ASCII bytes
        header_str = f"{name}{mtime}{uid}{gid}{mode}{size}{terminator}"
        return header_str.encode('ascii')
    except OSError as e:
        print(f"Error accessing {filename}: {e}")
        return None

def main():
    if len(sys.argv) < 4:
        print(f"Usage: {sys.argv[0]} <server_ip> <port> <file1> [<file2> ...]")
        sys.exit(1)

    server_ip = sys.argv[1]  # Server IP address from the command line
    port = int(sys.argv[2]) # Server port number converted to integer
    files = sys.argv[3:]    # Remaining arguments are file paths to include in the archive
    try:
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            # Create a TCP socket using IPv4
            s.connect((server_ip, port))
            # Send the ar archive global header to start the archive stream
            s.sendall(b"!<arch>\n")
            for filename in files:
                header = create_header(filename)
                if header is None:
                    continue
                # Send the generated 60-byte file header first
                s.sendall(header)
                # Send file content in chunks to avoid reading the whole file into memory
                with open(filename, "rb") as f:
                    while True:
                        chunk = f.read(4096)
                        if not chunk:
                            break
                        s.sendall(chunk)
                # Send padding newline if the file size is odd to maintain archive alignment
                if os.path.getsize(filename) % 2 != 0:
                    s.sendall(b"\n")
    except ConnectionRefusedError:
        print("Error: Could not connect to the server.")
    except Exception as e:
        print(f"An error occurred: {e}")

if __name__ == "__main__":
    main()
