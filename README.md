# Hello!
Hi! I'm [Allan](https://github.com/acmlira) This repository is focused in my **Computer Networks** socket understanding project. I'm about to graduate in computer engineering = I will **TRY** not to make mistakes :sweat_smile:

**Suggestions and bug fixes are welcome!**

# Project overview
The main objective of this project is understanding of **how the sockets work's**. For that, I proposed an **IoT application**: after hours of brainstorm and some :beer:, I get my electronic stuff, saw my ESP32, my TCS230 and think: "that's smells like :heart_eyes:". **TCS230 it's a low budget color sensor, but a badly color sensor**. It's very simple to use in red, green or blue recognition with *if and else* code like. I can **improve this color recognition**? I can combine it with the scoket communication approach? And that is the main concept to use a **classification model**. Yes.  Finally, I thought of a situation for this system to be applicable in a **web interface**: real life colorpicker called **Chameleon**.

### Requirements, user stories or something like this...

Chameleon dot com:
1. Bootstrap like;
2. Show the predict *color spectrum* name; 
3. Show the captured rgb;
4. Show the captured hex;
5. Copy buttons.

ESP32 (and TCS230):
1. Capture rgb(X,Y,Z) like with a button;
2. After capture and some manipulations, send by socket client to Python server ;
3. Start a webserver (Chameleon DOM);
4. Data transferency between ESP and served HTML with websockets.

The *Python Server* necessarily needs:
1. Database with color samples;
2. ML or classification model; 
3. Socket server binded at port XX;
4. Provides a response for each request. 

Clearly, in the communication process we have 3 internal actors:
1. **ESP32**: socket client and webserver (socket server)
2. ***Python Server***: socket server
3. **Web interface**: JS (socket client)

### Activity Diagram 
That's a WIP activity diagram, it's a bit of *main* activity for each actor

[![alt text](https://i.imgur.com/R22acvu.jpg)

# Goals, to do (WIP)
Can undergo more changes but:
[X] Foundation
[X] Python Server ready to release
[ ] ESP32 partially ready to release (Python Server)
[ ] Web page and ESP32 fully ready to release
[ ] First Release

# Like a boilerplate
You may have noticed that my files have specific characteristics, and they are:
 - **vscode** + **PlatformIO** (.workspace available)
 - My *labels* and *functions* are written in **English**
 - But, the *comments* and *descriptions*, they are written in **Brazilian Portuguese**

# Seeya!
Follow me at [![alt text][1.1]][1] 

[1.1]: http://i.imgur.com/wWzX9uB.png 

[1]: http://www.twitter.com/acmIira