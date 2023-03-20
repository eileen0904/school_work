## Introduction

This project is to implement a shell program with special piping mechanisms.

## Scenario of using shell

### A. Some important settings

1. The structure of the working directory

```c=
working_dir
    |
    |-- bin/         // put command
    |-- include/     // put your .h file
    |-- object/      // put your object file
    |-- src/         // put your source code
    |-- Makefile     // script for compile
    |-- `your shell` // this is executable 
```

### B. Scenario

#### Generel command

![](https://i.imgur.com/xh20xsg.png)

#### command with pipe

![](https://i.imgur.com/1UWJVqA.png)

![](https://i.imgur.com/b1v6wp5.png)

#### Number Pipe

![](https://i.imgur.com/XkWEF8S.png)

![](https://i.imgur.com/Xw1gLnL.png)

## Requirements and Hints

### A

In this project, the commands **number** are offered by TA. Please download it from E learning, and put the executables into the folder `working_dir`/bin/ .


Please don&#39;t execute number directly !!


### B

**ls** &amp; **cat** are usually placed in the folder /bin/ in UNIX-like systems. Please copy them into the folder `working_dir`/bin/ .

### C

During demo, TA will copy additional commands to bin/, which is under your working directory. Your shell program should be able to execute them.

### D


You can only implement the shell with C, other third-party libraries and **system()** command are **NOT allowed**.


## Specification

### A. Input

1. The length of a single-line input will not exceed 5000 characters.
2. Each command will not exceed 256 characters.
3. There must be one or more spaces between commands and symbols (or arguments), but **no spaces between pipe and numbers.**


No this command: cat hello.txt | 4

### B. Shell Behavior

1. Use **&#34;%&#34;** as the command line prompt. Notice that there is one space character after it.
2. The shell terminates after receiving the **quit** command.
3. Notice that you must handle the forked processes properly, or there might be zombie processes.


### C. setenv and printenv

1. The initial environment variable PATH should be set to **bin/** and **./** by default.

```
% printenv PATH
     bin:.
```

2. setenv usage: setenv [variable name] [value to assign]
3. printenv usage: printenv [variable name]

```
    % printenv QQ
        # Show nothing if the variable does not exist.
    % printenv LANG
        en_US.UTF-8
```

### D. Numbered-Pipes and Ordinary Pipe

1. **|N** means the STDOUT of the left hand side command should be piped to the first command of the next N-th line, where 1 ≤ N ≤ 128.


2. **|N** will only appear at the end of the line.


3. **|** is an ordinary pipe, it means the STDOUT of the left hand side command will be piped to the right hand side command. It will only appear between two commands, not at the beginning or at the end of the line.

4. The command number **:bangbang:&lt;font color=&#34;#FF0000&#34;&gt;should ignore unknown commands.&lt;/font&gt;**

```
    % ls |2
    % ctt
    Unknown command: [ctt].
    % ls
    bin/
    test.html
    % number
        1 bin/
        2 test.html
```

![](https://i.imgur.com/yepXaIA.png)

![](https://i.imgur.com/YpGxNBx.png)

5. setenv and printenv count as one command.

```
    % ls |2
    % printenv PATH
    bin:.
    % cat
        bin
        test.html
```

6. Empty line does not count.

```
    % ls |1
    % #press Enter
    % number
        1 bin/
        2 test.html
```

![](https://i.imgur.com/L0kh0km.png)

### E. Unknown Command

1. If there is an unknown command, print error message as the following format: **Unknown command: [command].**

```
    % ctt
    Unknown command: [ctt].
```

![](https://i.imgur.com/aaevJPh.png)

2. You don&#39;t have to print out the arguments.

```
    % ctt -n
    Unknown command: [ctt].
```

![](https://i.imgur.com/gq2rVkh.png)

3. The commands after unknown commands will still be executed.

```
     % ctt | ls
     Unknown command: [ctt].
     bin/
     test.html
```

![](https://i.imgur.com/dTBFw6K.png)

4. Messages piped to unknown commands will disappear.

```
     % ls | ctt
     Unknown command: [ctt].
```

![](https://i.imgur.com/4UGsBYZ.png)

## Number source code

```cpp=
#include &lt;fstream&gt;
#include &lt;iomanip&gt;
#include &lt;iostream&gt;
using namespace std;

int main(int argc, char* const argv[]) {
  ifstream file;
  if (argc == 2) {
    file.open(argv[1]);
    cin.rdbuf(file.rdbuf());
  } else if (argc &gt; 2) {
    cerr &lt;&lt; &#34;usage: &#34; &lt;&lt; argv[0] &lt;&lt; &#34; [filename]&#34; &lt;&lt; endl;
  }

  string line;
  int lineno = 0;
  while (getline(cin, line)) {
    cout &lt;&lt; setw(4) &lt;&lt; setfill(&#39; &#39;) &lt;&lt; ++lineno &lt;&lt; &#39; &#39; &lt;&lt; line &lt;&lt; endl;
  }
  return 0;
}
```
