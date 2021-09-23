# Morning Run

# What is it?
It's a web server (deployed on my Rasp Pi) and 4 web clients/ESP-32 microcontrollers (check out microcontrollers.png) system.

# Why?
These days I slam the snooze button 5-10 times before waking up. I needed something that would wake me up after one alarm...so I made "Morning Run".
I also wanted to try out more advanced projects that include hardware (microcontrollers) and learn more Arduino / C++.

# How does it work?
Each of the ESP-32s, which are scattered across my room, are responsible for sending GET requests to the web server for each number from 1-4 when the button is clicked. Every morning, the web server plays an alarm (alarm.mp3) and randomnly chooses a number from 1-4. If the GET request matches the randomnly chosen number, then the alarm will turn off.

This makes me run around my room each morning as fast as possible, pressing each button on each ESP-32, and race against the pressure of waking everyone in my family up.

# Does it work?
Yes and no. I learned that it comes down to me if I want to wake up, not my alarm. I need to be more strict with myself I guess :(
