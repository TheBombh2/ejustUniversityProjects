# CSC 121 - Sheet 3 - Problem 4

Your task is to implement memory management system using linked lists. You have two functions to implement: `allocate` and `deallocate`, both functions lie in `mem.cpp`. Your implementation should match the behaviour described in the next section. 

The memory is represented as a linked list, and each segment in the memory is represented as a node in this list. The following is the definition of the `Segment`:

```cpp
struct Segment {
	int pid; // if pid = -1, then the Segment represents a hole, otherwise the Segment is allocated to the process with the pid
	unsigned int start;
	unsigned int size; // size in bytes
	Segment* prev;
	Segment* next;
};
```

The definition lies in the file `mem.hpp`. **It's important that you don't modify this definition**. 

## Illustration 

Assume the size of the memory is 50 B. At first, the memory is empty, so the list is as follows:
```
[Hole, start = 0, size = 48]
```

If we call the function `allocate(*list, 1, 8)` (allocate 8 bytes to process 1), the memory should be modified to be:
```
[Process 1, start = 0, size = 8] -> [Hole, start = 8, size = 40]
```

If at any point the memory was:
```
[Hole, start = 0, size = 4] -> [Process 4, start = 4, size = 2] -> [Hole, start = 6, size = 16] -> [Process 4, start = 22, size = 16] -> [Hole, start = 38, size = 10]
```

And then we call `allocate(*list, 7, 16)`, you should find the first hole big enough to take 16 bytes, and take space from it:
```
[Hole, start = 0, size = 4] -> [Process 4, start = 4, size = 2] -> [Process 7, start = 6, size = 16] -> [Process 4, start = 22, size = 16] -> [Hole, start = 38, size = 10]
```

In this case, the hole was exactly the same size we wanted, so we allocated the whole hole to the process. If we then call `deallocate(*list, 4)`, the list should be as follows:
```
[Hole, start = 0, size = 6] -> [Process 7, start = 6, size = 16] -> [Hole, start = 22, size = 26]
```

Notice that we deleted the segments allocated to process 4, and merged them with adjacent holes (if they exist). If we finally call `deallocate(*list, 7)`, we will have this list:
```
[Hole, start = 0, size = 48]
```

Notice that the new hole was merged with both the left and the right holes.

## Tips

* You can call `dump(std::cout, head)` to print the list starting at `head`

## Setting Up Your Development Environment

You will need to have `git`, `make`, and `gcc` on your machine before you go on with the task. The installation process differs based on the operating system you're using. This document contains instructions for Windows and Linux. If you use MacOS, you will have to do your own research.

### Windows

First, make sure you have `Windows PowerShell` installed. We will use [scoop](https://scoop.sh/) package manager to install the programs. Feel free to use another package manager if you wish, but the instructions are tailored for `scoop`.

To install `scoop`, run the following commands on powershell:

```powershell
Set-ExecutionPolicy RemoteSigned -Scope CurrentUser
irm get.scoop.sh | iex
```

You might have some of them installed. To make sure, run each command on powershell and see if the output indicates that you have it. For example, this is the output if you run `git` when it's not installed:

```
git : The term 'git' is not recognized as the name of a cmdlet, function, script file, or operable program. Check the spelling of the name, or if a path was included, verify that the path
is correct and try again.
At line:1 char:1
+ git
+ ~~
    + CategoryInfo          : ObjectNotFound: (git:String) [], CommandNotFoundException
    + FullyQualifiedErrorId : CommandNotFoundException
```

Use the following command to install the programs:

```powershell
scoop install git make gcc
```

If everything goes fine, you're done with the installation phase.

### Linux

This will differ based on the distro you're using, but there is a chance that you have all these programs installed by default on your machine, so before proceeding with the installation, try using them first and see if they exist.

For Ubuntu, run:

```sh
sudo apt-get install build-essential git
```

For Arch, run:

```sh
sudo pacman -S base-devel git
```

For other distros, the process is roughly the same.

## Clone the Project

First, you need to clone (create a local copy) the project:

```
git clone https://github.com/salmanjnr/ejust-csc121-lab.git
```

This will create a folder with the name `ejust-csc121-lab` in your current directory. Go into the directory with the following command:

```
cd ejust-csc121-lab
```

Then run the following command:

```
git checkout lab3
```

## Compile and Run

To compile and run you project, enter the command `make run` in Windows PowerShell.

To test your program, run the command `make grade`. This will compile your program and test it over predefined testcases and output your score. The same test cases will be used to grade your project, so make sure you get an acceptable score before submission.

## Submission

After finishing the lab, run the following commands:

```
git add .
git commit -m "Lab 3 done"
make archive
```

This will create a file named `ejust-csc121-lab3.zip` in the project directory. This is the file that you will submit.
