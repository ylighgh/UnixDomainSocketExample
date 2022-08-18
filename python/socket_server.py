#!/usr/bin/env python3
# -*- coding:utf-8 -*-

import socket
import os


def main():
    while True:
        with socket.socket(socket.AF_UNIX, socket.SOCK_STREAM) as s:
            try:
                os.remove("/tmp/yl_python.sock")
            except OSError:
                pass
            s.bind("/tmp/yl_python.sock")
            s.listen(1)
            conn, addr = s.accept()
            with conn:
                data = conn.recv(1024)
                print(data.decode())
                conn.sendall("Hello!This is Python Socket Server!\n".encode())
            s.close()


if __name__ == '__main__':
    main()
