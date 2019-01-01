import socket


print("trying to socket")
server_socket = socket.socket()
server_socket.bind(('', 5566))
print("server demareeeeee")

server_socket.listen()

print("a l ecouteeeeee")
connected_socket , address = server_socket.accept()
print("client conecteeeeeeee")

data = connected_socket.recv(1024)
data = data.decode("utf8")

f= open("copied.txt","a+")
f.write(data)
f.close()

print(data)


server_socket.close()