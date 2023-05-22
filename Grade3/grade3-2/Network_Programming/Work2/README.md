## Introduction

1. Design a **Concurrent connection-oriented** server. This server allows client connect to it.
2. Design a server of the **chat-like systems**. In this system, users can communicate with other users.

**Your server must support all functions in project 1.**

## Scenario One

**You can use telnet to connect to your server.**

Example:
![](https://i.imgur.com/aDxnD95.png)

## Scenario Two

1. You are asked to design the following features in your server.
2. New built-in commands:

* who: show information of all users.
* tell: send a message to another user.
* yell: send a message to all users.
* name: change your name.

3. All commands in project 1.

**More details will defined in Spec chapter.**

## Spec

### 1. Working Directory

```c=
working_dir
    |
    |-- bin/         // put command
    |-- include/     // put your .h file
    |-- object/      // put your object file
    |-- src/         // put your source code
    |-- Makefile     // script for compile
    |-- `your service` // this is executable 
```

### 2. Format of the New Commands

#### `who`

**Show information of all users.**

Example:
![](https://i.imgur.com/1krBUC7.png)


**Your server should always assign the smallest unused id to a new user.**


#### `tell`

**Send the message to the specific user.**

**Format:** tell ```user id message```

The user will get the message with following format:


&lt;user(`id`) told you&gt;: ```message```


After send message, if success please send back accept message.


send accept!


Example:
![](https://i.imgur.com/kdkFzbK.png)

![](https://i.imgur.com/aaL2GQk.png)

#### `yell`

**Broadcast the message.**

All the users(including yourself) will get the message with the following format:


&lt;user(`id`) yelled&gt;: `message`


Example:

user0
![](https://i.imgur.com/SRJUfdo.png)

user1
![](https://i.imgur.com/TRFhrZJ.png)

#### `name`

**Change your name by this command.**


**Format :** name &#39;new name&#39;


After change user name, if success please send back accept message.


name change accept!


Example:
![](https://i.imgur.com/gyIwfvy.png)

![](https://i.imgur.com/XxY6ogh.png)

Notice that the name CAN NOT be the same as other users’ name, or you will get the following message:


User `new name` already exists !


Example:

![](https://i.imgur.com/g0vYNcp.png)

![](https://i.imgur.com/sFKpaec.png)
