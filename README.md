# Password Hashing [![GitHub release](https://img.shields.io/github/release/paradoxinfinite/password_hashing.svg)](https://github.com/ParadoxInfinite/Password_Hashing/releases)
A User authentication program which hashes the entered password and writes to a file for further logins. 
Code written, compiled and tested on Visual Studio 2017

### Technique used :
Password hashing command line program uses DJB2 hashing algorithm implementation to hash the information. The information is never decrypted, thus avoiding any leaking of plaintext.

### Function used by DJB2 for hashing :
```c
unsigned long hash(unsigned char *str)
{
	unsigned long hash = 5381;
	int c;
	while (c = *str++)
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
	return hash;
}
```

### Tested By : 
@OsmanDsilva

### Using this code : 
This code can be modified/redistributed by anyone without any prior permission. Any suggestions are welcome!
Have fun!

### Reporting bugs : 
Please open an issue on this repository so that I can look into any error that may have occurred. Be as descriptive as possible and if and when necessary add a screenshot.
