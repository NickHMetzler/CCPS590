# Import Socket
from socket import *

# Connection Information
ADDRESS = "192.168.68.113"
PORT = 8675

# Set up Socket Server
serverSocket = socket(AF_INET, SOCK_STREAM)
serverSocket.bind((ADDRESS, PORT))
serverSocket.listen()
print(f"Server is running on address {ADDRESS} and port {PORT}")

# Run the server
while True:
    connectionSocket, addr = serverSocket.accept()
    # Decode and print request
    req = connectionSocket.recv(2048).decode()
    print("Request made\n" + req)
    # Figure out what the site needs and send it
    myReq = req[4:req.find(" ", 4) + 1]
    if 'index.html' in myReq:
        connectionSocket.send("HTTP/1.1 200 OK\r\n".encode())
        connectionSocket.send(b"Content-Type: text/html\r\n")
        html = open("index.html", "rb")
        css = open("style.css", "rb")
        connectionSocket.sendfile(html)
        connectionSocket.sendfile(css)
        html.close()
        css.close()
        connectionSocket.send("\r\n".encode())
    elif 'logo.png' in myReq:
        connectionSocket.send(f"HTTP/1.1 200 OK\r\n".encode())
        connectionSocket.send(f"Content-Type: image/png\r\n".encode())
        img = open("images/logo.png", "rb")
        r = img.read()
        img.close()
        connectionSocket.send(f"\r\n".encode())
        connectionSocket.send(r)
    elif 'Base_Model.png' in myReq:
        connectionSocket.send(f"HTTP/1.1 200 OK\r\n".encode())
        connectionSocket.send(f"Content-Type: image/png\r\n".encode())
        img = open("images/Base_Model.png", "rb")
        r = img.read()
        img.close()
        connectionSocket.send(f"\r\n".encode())
        connectionSocket.send(r)
    elif 'GTAm.jpg' in myReq:
        connectionSocket.send(f"HTTP/1.1 200 OK\r\n".encode())
        connectionSocket.send(f"Content-Type: image/jpg\r\n".encode())
        img = open("images/GTAm.jpg", "rb")
        r = img.read()
        img.close()
        connectionSocket.send(f"\r\n".encode())
        connectionSocket.send(r)
    elif 'Quad.png' in myReq:
        connectionSocket.send(f"HTTP/1.1 200 OK\r\n".encode())
        connectionSocket.send(f"Content-Type: image/png\r\n".encode())
        img = open("images/Quad.png", "rb")
        r = img.read()
        img.close()
        connectionSocket.send(f"\r\n".encode())
        connectionSocket.send(r)
    elif 'Stellantis.png' in myReq:
        connectionSocket.send(f"HTTP/1.1 200 OK\r\n".encode())
        connectionSocket.send(f"Content-Type: image/png\r\n".encode())
        img = open("images/Stellantis.png", "rb")
        r = img.read()
        img.close()
        connectionSocket.send(f"\r\n".encode())
        connectionSocket.send(r)
    elif 'Ti_Sport.png' in myReq:
        connectionSocket.send(f"HTTP/1.1 200 OK\r\n".encode())
        connectionSocket.send(f"Content-Type: image/png\r\n".encode())
        img = open("images/Ti_Sport.png", "rb")
        r = img.read()
        img.close()
        connectionSocket.send(f"\r\n".encode())
        connectionSocket.send(r)
    # If none of the conditions are met, there is an error
    # Most likely user did not do index.html
    else:
        connectionSocket.send(b"HTTP/1.1 404 Not Found\r\n")
        connectionSocket.send(b"Content-Type: text/html\r\n")
        connectionSocket.send((open("error.html", "r").read()).encode())
        connectionSocket.send("\r\n".encode())

    # Close connectionSocket
    connectionSocket.close()
