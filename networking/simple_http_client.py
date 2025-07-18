'''
Dieses Programm stellt eine einfache TCP-Verbindung zu www.google.com auf Port 80 her,
sendet eine HTTP-GET-Anfrage, um die Startseite abzurufen,
und gibt die empfangene HTTP-Antwort als Text auf der Konsole aus.
Es demonstriert die Grundlagen der Socket-Programmierung in Python.
'''

import socket

HOST = 'www.google.com'  
PORT = 80                

client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM) #adresse family and kid socket
server_address = (HOST, PORT)
client_socket.connect(server_address)

request_header = b'GET / HTTP/1.0\r\nHost: www.google.com\r\n\r\n'
client_socket.sendall(request_header)

response = ''
while True:
    recv = client_socket.recv(1024)
    if not recv:
        break
    response += recv.decode('utf-8', errors='replace')
        
print(response)
client_socket.close()
