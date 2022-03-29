# Import socket module
import socket
import struct            
 
# Create a socket object
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)        
 
# Define the port on which you want to connect
port = 22000              
 
# connect to the server on local computer
s.connect(('127.0.0.1', port))
 
data = "Hello Server!";
data_bytes = bytes(data, 'UTF-8')
data_encoded = struct.pack('10s', data_bytes)

s.send(data_encoded);

# close the connection
s.close()    
     