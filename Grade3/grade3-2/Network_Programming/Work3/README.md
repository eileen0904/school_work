## Introduction

1. Design a user system with database, detail will show in Spec chapter.
2. Your program must contain at least following features.
    - including login/logout mechanisms,
    - mail mechanism so that user receive message offline.
    - group mechanism so that user can chat members in the same group that is like Line group.

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

### 2. Database

The database we choose **redis**.

[Link of Redis](https://redis.io)

**Redis Clients** : we using [**hiredis**](https://github.com/redis/hiredis)

It have a lot of example on github.
**Refer them**.

### 3. Login/Logout mechanisms

**Login format:**

Login: &lt;user name&gt;
Passowrd: &lt;password&gt;

![](https://i.imgur.com/O4RDyM8.png)

#### 1. To Accept condition

Please reload screen and show the command line prompt.

:bangbang: leave one space after **&#34;%&#34;** sign.

(user_name)%

![](https://i.imgur.com/hN1iJzh.png)


If user exist &amp; password error, please go to error conditon 1.

If user doesnot exist, go to error condition 2.


#### 2. error condition 1

**If user name exist and password error, please show `Password error !` then reload the login interface.**
:::warning
Password error !
:::

![](https://i.imgur.com/b7THzCm.png)

![](https://i.imgur.com/Mdmyfu0.png)

#### 3. error condition 2

User not found !
Create account or login again ? &lt;1/2&gt; : `your input`

1. adding a new user account

![](https://i.imgur.com/bsBH8Ko.png)

2. backing to login page

![](https://i.imgur.com/oqFKkw5.png)

**Register**

your user name: (input)
your password: (input)

If user name exist, please show a warning message. **User name already exist !**

Then prompt the input message again. **your user name:_**

![](https://i.imgur.com/KY6QNUC.png)

**:bangbang: After register, please show &#34;Create success !&#34;.**

### 4. Mail box mechanism

**A user has a mail account and the mail account is same as user name.**
**The mail account stores messages from other user sending.**

- The following commands are commands for a mail box that must be implemented.

- listMail
- mailto
- delMail

#### 1. `listMail`  : List all mails in your mail account

**Print format: follow below example.**
![](https://i.imgur.com/8Wmotbg.png)

If not mail exist, please show **&#34;empty !&#34;**

![](https://i.imgur.com/SlHqS6H.png)

#### 2. `mailto`

Format:
mailto &lt;user_name&gt; message

message is a string.

or

mailto &lt;user_name&gt; &lt; ls

this means redirect output from `ls` to &lt;user_name&gt;

If success:

![](https://i.imgur.com/yNOIyYT.png)

![](https://i.imgur.com/dd5AAkv.png)

If user name not found, please show **&#34;User not found !&#34;**

![](https://i.imgur.com/3RNf6b9.png)


#### 3. `delMail`

Format:
delMail &lt;mail_id&gt;

If success:

![](https://i.imgur.com/YwTHEXU.png)

If mail id not found, please show **&#34;Mail id unexist !&#34;**
![](https://i.imgur.com/8aprIHK.png)

### 5. Group mechanism

A user can belong to some groups.
All members in the same group can chat ine the same group that is like Line group chat.


- A user can join more than one group.
- A user can chat concurrently in more than one group.


- The following commands must be implemented for group mechanism.


- gyell
- createGroup
- delGroup
- addTo
- leaveGroup
- remove


In this case, you need provide commmand below.

#### `gyell`

This command same as `yell`, only different between two command, is `yell` broadcast to every users they are online and `gyell` broadcase to users on the same group.

gyell &lt;group_name&gt; &lt;message&gt;


message:
&lt;group_name:user_name&gt;: &lt;message&gt;


If group unexist, please show **&#34;Group not found !&#34;**

**Example:**

member in group:

![](https://i.imgur.com/GvOJXfw.png)

message:

![](https://i.imgur.com/0trUD5o.png)

![](https://i.imgur.com/9v75ksy.png)

![](https://i.imgur.com/QyPZyQH.png)

![](https://i.imgur.com/U79AsF8.png)

#### `createGroup`

Create a group.

Format:
createGroup &lt;group_name&gt;


If group exist. please show **&#34;Group already exist !&#34;**

![](https://i.imgur.com/hXKk5np.png)

If create success.

![](https://i.imgur.com/NocHxbQ.png)

#### `delGroup`

Delete a group.

**Only the owner can delete group !!**


Format:
delGroup &lt;group_name&gt;

If success, please show: **&#34;Group delete success !&#34;**

**Before delete:**

![](https://i.imgur.com/wzrbiNE.png)

![](https://i.imgur.com/bdD0PwW.png)

![](https://i.imgur.com/TI3kNF7.png)

![](https://i.imgur.com/XGEpH2I.png)

![](https://i.imgur.com/XQ9zevV.png)

**After delete:**

![](https://i.imgur.com/tlaxSLe.png)

![](https://i.imgur.com/Vmhaays.png)

![](https://i.imgur.com/ZY69xw9.png)

![](https://i.imgur.com/brhDbCG.png)

If group unexist. please show **&#34;Group not found !&#34;**

#### `addTo`

invite user come in group.

**Only the owner can invite other user !!**


Format:
addTo &lt;group_name&gt; &lt;user_name1&gt; &lt;user_name2&gt; ...

If user add success, please show **&#34;&lt;User_name&gt;... add success !&#34;**

&lt;user_name1&gt; &lt;user_name2&gt; ... add success !


If user unexist, please show:

&lt;user_name1&gt; &lt;user_name2&gt; ... not found !


If user already in group, please show **&#34;&lt;User_name&gt;... already in group !&#34;**

&lt;user_name1&gt; &lt;user_name2&gt; ... already in group !


**Example:**

![](https://i.imgur.com/1N2CDDk.png)

![](https://i.imgur.com/8U26jHy.png)

![](https://i.imgur.com/k1TUwBe.png)

If other user want access these group they don&#39;t have permission, please show **&#34;You don&#39;t have permission !&#34;**

![](https://i.imgur.com/IiZJHx7.png)

If group unexist, please show **&#34;Group not found !&#34;**

#### `leaveGroup`

Leave a group.

Format:
leaveGroup &lt;group name&gt;

If leave auccess.

![](https://i.imgur.com/pDEiFl1.png)

Otherwise. please show **“Leave fault !**

![](https://i.imgur.com/wolgpoL.png)

If group unexist, please show **&#34;Group not found !&#34;**

#### `listGroup`

List groups that you belong to.

Format:
listGroup


![](https://i.imgur.com/yrhuTNX.png)

![](https://i.imgur.com/5HzAUBf.png)

If no group you belong to, show **&#34;Empty !&#34;**

#### `remove`

Remove user from group.

**Only the group owner can remove a user !!**

Format:
remove &lt;group_name&gt; &lt;user_name&gt; &lt;user_name&gt; ...


If user is not in group, please show: **&#34;&lt;User_name&gt;... is not in group !&#34;**

&lt;user_name1&gt;, &lt;user_name2&gt;, ... is not in group.


If user remove success, please show **&#34;&lt;User_name&gt;... remove success !&#34;**

&lt;user_name1&gt; &lt;user_name2&gt; ... remove success !


If user unexist, please show: **&#34;&lt;User_name&gt;... not found !&#34;**

&lt;user_name1&gt; &lt;user_name2&gt; ... not found !


If group unexist, please show **&#34;Group not found !&#34;**

**Example:**

Group member before remove:

![](https://i.imgur.com/2to41zW.png)

After remove:

![](https://i.imgur.com/cWmL2so.png)

![](https://i.imgur.com/9aJmAVV.png)

![](https://i.imgur.com/gh569V4.png)

User is not in group.

![](https://i.imgur.com/nzPluhB.png)
