# Import statements
import socket
import threading

# Constant decalarations
PORT = 6969
SERVER = socket.gethostbyname(socket.gethostname())
ADDRESS = (SERVER, PORT)
FORMAT = 'utf-8'
DISCONNECTMSG = '!STOP'
SERVERMSG = '[SERVER] : '
MSGSIZE = 1024

# Set up server to connect to ADDRESS
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind(ADDRESS)

# Make any string uppercase
def makeUpperCase(str):
    return str.upper()

# Handler for the client
def clientHandler(connection, address):
    # Show newly established connection
    print(f"{SERVERMSG}[NEW CONNECTION ESTABLISHED] : {address} connected")

    # While loop while the client is active
    connected = True    
    while connected:
        # Get the message length to weed out the connection message
        
        # Get the message
        msg = connection.recv(MSGSIZE).decode(FORMAT)
            
        # Check if client wants to disconnect
        if msg == DISCONNECTMSG:
            connected = False
            print(f"{SERVERMSG}[{address}] Client disconnected...")
            break
        
        print(f"{SERVERMSG}[{address}] Message:\n'{msg}'")
        # Send capitalized message back to the Client
        connection.send((SERVERMSG + "\n" + makeUpperCase(msg)).encode(FORMAT))
    # CLose the connection
    connection.close()

# Main function
def start():
    # Listen for client connections
    server.listen()
    print(f"{SERVERMSG}[LISTENING] Server is listening on {SERVER}")
    while True:
        # Accept connection and make thread with clientHandler
        connection, address = server.accept()
        thread = threading.Thread(target = clientHandler, args = (connection, address))
        thread.start()
        print(f"{SERVERMSG}[ACTIVE CONNECTIONS] : {threading.activeCount() - 1}")

# Print server starting and start server
print(f"{SERVERMSG}[STARTING SERVER...]")
start()