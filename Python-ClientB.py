# Import statements
import socket
from datetime import date

# Constant decalarations
PORT = 6969
FORMAT = 'utf-8'
DISCONNECTMSG = '!STOP'
SERVER = socket.gethostbyname(socket.gethostname())
ADDRESS = (SERVER, PORT)
CLIENTMSG = '[CLIENT] : '
MSGSIZE = 1024

# Set up client to connect to ADDRESS
client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect(ADDRESS)

# send a message to the server
def send(msg):
    # Encode the message and send it to the server
    client.send(msg.encode(FORMAT))

# Main function
def start():
    # Prompt the client to enter the Name
    studentName = input(f"{CLIENTMSG}Please input Student Name: ")
    while len(studentName) <= 0:
        studentName = input(f"{CLIENTMSG}ERROR, no name was provided\nPlease input Student Name: ")

    # Prompt the client to enter a valid student ID
    studentID = input(f"{CLIENTMSG}Please input StudentID: ")
    while len(studentID) <= 8 or len(studentID) >= 10:
        studentID = input(f"{CLIENTMSG}ERROR, student ID of incorrect length was inputted\nPlease input StudentID: ")

    # Concatenate the information to send in one message to the server
    msgStr = studentName + "\n" + studentID + "\n" + str(date.today())
    send(msgStr)
    print(f"{CLIENTMSG}Successfully sent\n'{msgStr}'\nto server...")

    # Print the returned message in all uppercase from the server, then disconnect
    print(f"\n{client.recv(MSGSIZE).decode(FORMAT)}")
    print(f"\n{CLIENTMSG}Disconnecting from server and closing client...")
    send(DISCONNECTMSG)

# Print client starting and start client
print(f"{CLIENTMSG}[STARTING CLIENT...]")
start()
