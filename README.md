# Cybersecurity - Obfuscated Code

Authors : Hugo Steiger, Benjamin Izart  
Mentor : Guillaume Bonfante  
Full documentation (in French) : https://drive.google.com/drive/folders/16yg3gpRikzVpGzG4b20JTEvcYGvRzW8q?usp=sharing

-------------------------------------------------------------------------------------------------------------------------------------------------------------

This project was made during my last year at Mines Nancy, in the Computer Science Department. The corresponding course is entitled "Malware Attacks / Defense". The point of the project was to write hard-to-debug program, acting like "echo" at first glance. Thanks to debugging techniques, the other team had to tell whether the program had the same behaviour as "echo", or if there were exceptions. obfuscated.cpp does echo, but its behaviour was well hidden from the other team.

DISCLAIMER : "obfuscated.cpp" was compiled on a special Windows XP VM, whose firewall and antivirus are disabled. The IDA and PIN tools are also installed on this plateform. This XP version being quite unique, some function address deltas (that is to say the difference in bytes between two function addresses) in the libraries memory space might not work with a different Windows XP VM. 

/!\ THE COMPILED PROGRAM HAS AN AGRESSIVE BEHAVIOUR (random password adding, memory destruction) AND SHOULD BE HANDLED WITH CARE, ON A SEPARATE VM.

The process by which the program has eventually the same behaviour as echo is the following :

![explain1](https://user-images.githubusercontent.com/106969232/179614758-567457d1-28ae-49e4-8956-61c9a4e3e6b8.JPG)

This process was hidden using code obfuscation, anti-debug methods and aggressive code. Most of the code obfsucation was done making functions anonymous, encrypting constants and adding many return loops. This makes the code really hard to understand within the debugger scope. Different encrypting techniques were used for the constants. Here are two examples :

The "double helix encoding", used to decrypt the "Master key" used for all other decryptions :

![explain3](https://user-images.githubusercontent.com/106969232/179616178-24c27d8b-e184-4b8f-96a5-2094f5fa603d.JPG)

A XOR encoding technique where I is a string and K can be a string or a number :

![explain4](https://user-images.githubusercontent.com/106969232/179616205-6fee2bc6-8137-499b-8382-05a9c192ddb1.JPG)

All encoding techniques used to obfsucate the code are introduced in the 3.10 Python script "encrypting_rules.py", with example use. As regards the anti-debug process, it can be summed up with the illustration below. Checksums were also added regurlary in the code to check the integrity of the .exe itself, as well as the program flow.

![explain2](https://user-images.githubusercontent.com/106969232/179617182-dba675e0-6eae-42e7-983a-eaf62f837f3e.JPG)

Three categories of aggressive code were added, and activated if there were an incongruence as regards the checksums, or a detected debugger. The first step consists in simply shutting down the machine. The second step forces a password and restarts the computer. The third and final step destroys the system memory, starting with installed debugger locations.

-------------------------------------------------------------------------------------------------------------------------------------------------------------

HOW TO USE :
- git pull this repo.
- Start a compatible Windows XP Virtual Machine (tested with VMWare Workstation 16 emulator / Win10x64).
- Transfer the C++ code "obfsucated.cpp" in the VM system.
- Compile "obfuscated.cpp" (tested with Visual Studio 10.0).
- Close all potentially active debuggers.
- Test the program with the command line, it should always act as "echo", with a bit of delay because of the obfsucation computional cost.
- Test the program with all the 3 conditions met : the display should not change.
- Try to debug step by step the program : the previously introduced security measures will be activated (tested with WinDBG, IDA, Pin, Visual Studio 10.0).
