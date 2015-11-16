import socket

SIZE=1024
IP=socket.gethostname()

#decide the src file
while True: 
    src=raw_input("Enter name of file you want to send: ")
    try:
        f=open(src,"rb")
        break
    except IOError:
        print "File not found."

#create the socket
sock=socket.socket()
port=int(raw_input("Enter port no: "))
sock.bind((IP,port))
sock.listen(5)

#handshake 
c,addr=sock.accept()

#sending the file @1024bytes
try:
    byte=f.read(SIZE)
    while byte!="":
        c.send(byte)
        byte=f.read(SIZE)
finally:
    print "File has been sent from server!"
    c.send(byte)
    
f.close()
c.close()
sock.close()
