#!/usr/bin/env python3
# -*- coding:utf-8 -*-

import socket


def main():
    while True:
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
            s.bind(('', 50007))
            s.listen(1)
            conn, addr = s.accept()
            with conn:
                print('Connected by', addr)
                data = conn.recv(1024)
                print(data.decode())
                conn.sendall("hello,port_client!\n".encode())
            s.close()


if __name__ == '__main__':
    main()
