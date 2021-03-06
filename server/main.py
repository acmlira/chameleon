#
#   Author: Allan César (@acmlira or /acmlira) 
#    
#   Since: 05/05/2019
#   
#   Description: The server routine script 
#
import pandas as pd
import sklearn

from socket import socket, AF_INET, SOCK_STREAM
from sklearn.linear_model import LogisticRegression

# Import train and test data
train = pd.read_csv('/home/acmlira/Documents/Code/chameleon/server/data/colors.csv', sep=',',header=0)  
test = pd.read_csv('/home/acmlira/Documents/Code/chameleon/server/data/colors.csv', sep=',',header=0)

# Make train set 
y_train = train.iloc[:, 5]  
X_train = train.iloc[:, 1:4]

# Make test set
y_test = test.iloc[:, 5] 
X_test = test.iloc[:, 1:4]

# Create the predictive model (Logistic Regression) and show the accuracy 
LR = LogisticRegression(random_state=0, solver='lbfgs', multi_class='multinomial').fit(X_train, y_train)  
LR.predict(X_test)
print(round(LR.score(X_test,y_test), 4))

def adjust(rgb):
  if rgb[0][0] < 0 or rgb[0][1] < 0 or rgb[0][2] < 0:
    most_negative = rgb[0][0]
    if rgb[0][1] < most_negative:
      most_negative = rgb[0][1]
    if rgb[0][2] < most_negative:
      most_negative = rgb[0][2] 
    
    rgb[0][0] = rgb[0][0] - most_negative
    rgb[0][1] = rgb[0][1] - most_negative
    rgb[0][2] = rgb[0][2] - most_negative
  return [[rgb[0][0],rgb[0][1],rgb[0][2]]]

def to_hex(rgb):
  return str(hex(rgb[0][0])[2:] + hex(rgb[0][1])[2:] + hex(rgb[0][2])[2:])

# # # # # # # # # # # # # # # # # # # # # #
#                                         #
# UNDERSTANDING COMMUNICATION BY SOCKETS  # 
#                                         #
# # # # # # # # # # # # # # # # # # # # # #

# Create the TCP socket server
socket = socket(AF_INET,SOCK_STREAM)

# We will use the ‘0.0.0.0’ IP, which will bind the socket to all the IP addresses on the machine
# and we will use port 8090
socket.bind(('0.0.0.0', 8090))

# After the binding, we need to make our server start listening to connections. We can pass the 
# value 0 because not involve multiple clients. 
socket.listen(0)                 
 
while True:
  # To start receiving the actual connections, we need to call the accept method on our socket 
  # object, this method returns a pair with a new socket object and the address of the client.
  #  
  # We can then use this new socket object to establish the communication with the connected 
  # client.
  print("Waiting for connection...")
  client, addr = socket.accept()
  while True:
    # Basically recv get the data from the client, it's like a request. In Python 3.x.x return 
    # byte type (b'xyzw')
    content = client.recv(32)
    if len(content) == 0:
      break
    # decode is used for reshape content as str
    string = content.decode()
    print("Predictable data: " + string)
    # Transform the data into happy data
    rgb = adjust([[int(i) for i in string.split(",")]])
    hex_of_rgb = to_hex(rgb)
    # THE PREDICT
    color_spectrum = LR.predict(rgb)
    # Send the response to client
    client.sendall((str(color_spectrum[0])+"\n").encode())
    client.sendall(("rgb("+ str(rgb[0][0])+","+str(rgb[0][1])+","+str(rgb[0][2])+")\n").encode())
    client.sendall(("#" + str(hex_of_rgb)+"\n").encode())
  print("Closing connection\n")
  client.close()
client.close()