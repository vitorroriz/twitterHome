# twitterHome
Controlling electrical equipaments in your house from your Twitter account.

In this simple smart house project we allow the user to control some electrical loads in a residence and to receive alerts from its alarm, all of it through his personal Twitter account.

The user can turn on/off electrical loads and even control the power rate of it via a dimmer installed. In the tests the load used as example is a simple lamp. The user can also turn on/off a presence detector alarm that sends a tweet (Twitter message) back to him when it detects some presence, informing when it has occurred. The video of a quick test can be watched in the following link: 

https://www.youtube.com/watch?v=UvIMFM22924

In this test we are:
1 - Turning the load on with 60% power rate.
2 - Turning the load on with 100% power rate.
3 - Turning the load off.
4 - Activating the alarm.
5 - Desactivating the alarm.
6 - Observing in my Twitter acount the alert messages received about the detection, while the alarm was activated.

# Content:

Two programs were developed. The first one is a hands-on approach in Python, which utilizes Tweepy (http://www.tweepy.org), to access the Twitter API. The python script access the Twitter account of the House and tracks tweets sent to it. If the tweet message contains specific commands (like activate the alarm) and it is from an authorized user (User's Twitter acount), the script sends this command through the computer's serial port to an Arduino, that makes the interface with the electrical equipaments. The script is also listening to the computer's serial port, to be aware of any detections from the alarm and to be able to send a Tweet to the User's personal account if it happens.

The second program is just an Arduino code that connects the Arduino to the computer's serial port, interprets the commands received from the python script and delivers it to the electrical equipaments.
