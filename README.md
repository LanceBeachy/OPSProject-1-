# OPSProject-1-

How to run:

1). download file onto codespace

2). in terminal, write the command:

    gcc shell.c -o shell

    then to run

    ./shell

3). After the shell is running try any of the commands:

    C: file1 file2 copies file1 to file2

    D: file deletes a file

    E: comment prints text to the screen

    H: displays the help menu

    L: shows the current directory and file listing

    M: file opens a file in nano

    P: file displays file contents using more

    Q: quits the shell

    W: clears the screen

    X: program executes a program

4). Functions in shell

    main()- is the main shell, in charger of internal commands, processes, and waits to be completed

    parseCommand()- splits the input line into command tokens and fills stores value in argv

    printPrompt()- displays shell prompt

    readCommand()- reads one line of the input from the user

    printHelp()- prints the shell help menu

    runListCommand()- in charge of running the "L" command 

5). Sources for project

    Class notes 

    Project slides 

    https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf
    (Did not copy code)