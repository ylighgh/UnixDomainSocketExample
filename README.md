# UnixDomainSocket

A tiny example for unix domain socket in Python and C

## Usage
### C
```
# Socket Version
cd c
make
./bin/socket

# Test
nc -U /tmp/yl_c.sock <<< "test"
```

### Python
```
# Port Version
cd python
./port_server.py

# Test
nc 127.0.0.1 50007 <<< "hello,port_server"

# Socket Version
cd python
./socket_server.py

# Test
nc -U /tmp/yl_python.sock <<< "hello,socket_server"
```