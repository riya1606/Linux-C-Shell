# Linux-C-Shell

## Overview

This shell is a complete working linux shell. It supports most linux shell functionalities including semicolon separated commands, piping, redirection, and all basic linux commands etc. Foreground and Background processes can also be executed.
The commands that are supported are as follows :

* pwd : prints the present working directory.

* cd  : changes the directory based on the flags given.

  * ``` bash
    cd
    cd .
    cd ..
    cd ~
    cd <directory>
    ```

* ls : lists the contents of a particular directory based on the flags given.

  * ```bash
    ls
    ls -a
    ls -l
    ls -al
    ls -la
    ls <directory>
    ```

* echo : prints a message on the terminal

  * ```bash
    echo <"Hello World">
    ```

* pinfo : lists the details of a particular process (may be based on a process ID that is given).
  
  * ```bash
    pinfo
    pinfo <pid>
    ```

* Foreground Processes: Processes that require the terminal to halt until their completion. Example:
  
  * ```bash
    vi
    emacs
    ```

* Background Processes: Processes that run simultaneuosly without interrupting the terminal. Example:

  * ```bash
    emacs &
    ```

* Input output redirection : Redirects input or output to appropriate files. Example:

  * ```bash
    cat file1.txt > file2.txt
    sort < sort.txt > sorted.txt
    ```

* Piping commands : Pipes two or more commands together. Example:

  * ```bash
    cat test.txt | grep a
    ```

* Piping with redirection : Example :

  * ```bash
    sort < sort.txt  | grep a | wc > lines.txt
    ```

* setenv : setting new environment variables. Example :

  * ```bash
    setenv a 15
    ```

* unsetenv : unsetting an environment variable

  * ```bash
    unsetenv a
    ```

* jobs : prints all the  background jobs

  * ```bash
    jobs
    ```

* kjob : Sends a signal to  a particular job number

  * ```bash
    kjob 1 9
    ```

* fg : brings a running or a stopped background job with given job number to foreground.

  * ```bash
    fg 1
    ```

* bg : changes a stopped background job to a running background job.

  * ```bash
    bg 1
    ```

* overkill : kills all background process at once.

  * ```bash
    overkill
    ```

* The terminal also supports

  * CTRL + C

## Running the Shell

In order to run the shell run the following command.

```bash
    make
    ./a.out
```

## Exiting From the shell

To exit from the shell, use the command

```bash
quit
```

## Pseudo Home

If the executable is being run from a different directory, specify the corresponding path. <br>
The "Pseudo Home" directory for the shell will be the directory in which the executable ./a.out resides.

## Code Files and Files

* main.c:

  * prompt(): function to print th shell promt.

  * loop(): runs the main loop of the code for the continuous execution of the shell.

  * extract_command(): take the string parsed as input and returns the extracted command as a command array. 

  * piping(): checks for piping in the command. 

  * red_flag_check(): checks for redirections flag check.

* pwd.c:

  * pwd(): function that prints the present working directory.

* ls.c:
  * The flags -a, -l, -la, -al can be used. Complete or absolute path of a directory can also be provided to list the contents of that directory.
  
  * ls_a(): lists files and directories including hidden files.

  * ls_l(): lists all information about files and directories excluding hidden files.

  * ls_al(): lists all information about files and directories including hidden files.

  * ls_basic(): simply lists all files and directories.

  * ls_call(): driver function to choose amongst the above functions.

  * flag_check(): takes in the command as input and return the correct flag given in the command

* cd.c:
  
  * cd (): Absolute or relative path of a directory must provided. The directory will then be changed the argument provided.

* echo.c:

  * echo_func(): Prints a string argument on the terminal. Handles cases with and without quotes.

* pinfo.c():

  * pinfo(): Provides details about currently active/running processes. A particular process ID can also be provided as an argument to obtain its details.

* foreground.c:

  * foreground(): Forks the existing process and runs a child process in the foreground. The parent process resumes once the child terminates and waits till then.

* background.c:

  * background(): Forks the existing process and runs a child process in the background. The parent process continues to run alongside the child process. Once the child terminates, the exit satus of the child process prints on the screen.

  _background processes for built in commands are not supported_

* history.c:

  * update_hist(): Every time a new command is given to the shell, the command is added to the array to be printed later.

  * print_hist(): Prints the history upto 10 commands earlier.
