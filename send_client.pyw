import socket

host,port = ('localhost' , 5566)

client_socket = socket.socket()
connected = False
while not connected:
    try:
        client_socket.connect((host,port))
        connected = True
    except Exception as e:
        pass #Do nothing, just try again



f = open("C:\\Users\\Ethan\\Desktop\\C\\TroySous_ETHAN\\hack.txt", 'r')
data = f.read()
data = data.encode("utf8")
client_socket.sendall(data)
f.close()

client_socket.close()