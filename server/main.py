import socket
import pandas as pd  
import sklearn as sk   
from sklearn import svm 
from sklearn.linear_model import LogisticRegression 
from sklearn.ensemble import RandomForestClassifier  
from sklearn.neural_network import MLPClassifier

vowel_train = pd.read_csv('data/colors.csv', sep=',',header=0)  
vowel_test = pd.read_csv('data/colors.csv', sep=',',header=0)

y_tr = vowel_train.iloc[:, 5]  
X_tr = vowel_train.iloc[:, 1:4]

y_test = vowel_test.iloc[:, 5] 
X_test = vowel_test.iloc[:, 1:4]

LR = LogisticRegression(random_state=0, solver='lbfgs', multi_class='multinomial').fit(X_tr, y_tr)  
LR.predict(X_test)  
print(round(LR.score(X_test,y_test), 4))

prediction = [[180,120,94]]

print(LR.predict(prediction))

socket = socket.socket()

socket.bind(('0.0.0.0', 8090))
socket.listen(0)                 
 
while True:
    client, addr = socket.accept()
    while True:
        content = client.recv(32)
        if len(content) == 0:
           break

        string = content.decode()
        to_predict = [[float(i) if '.' in i else int(i) for i in string.split(",")]]
        prediction = LR.predict(to_predict)

        client.sendall(prediction.encode())   

    print("Closing connection")
    client.close()
client.close()