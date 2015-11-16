import socket

SIZE=1024
IP=socket.gethostname()


#get the 'save as' name
while True: 
    dest=raw_input("Save as: ")
    try:
        f=open(dest,"wb")
        break
    except IOError:
        print "Unable to save file."
    
#create the socket
sock=socket.socket()
port=int(input("Enter portno of server: "))
sock.connect((IP,port))

#Receiving from server @1024bytes
print "Receiving from server..."
byte= sock.recv(SIZE)
while byte!="":
    f.write(byte)
    byte= sock.recv(SIZE)    
print "File has been succesfully received!"

#cleaning up the shizz
f.close()
sock.close()
