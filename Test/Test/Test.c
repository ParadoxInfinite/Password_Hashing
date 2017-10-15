#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
char unamer[21], unamel[21], pass[17]; 
unsigned long h_pass[65];
void reg();
void login();
char* getpass();
int user_check();
int auth();
void write(char,char);
unsigned long hash(unsigned char *str)
{
	unsigned long hash = 5381;
	int c;
	while (c = *str++)
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
	return hash;
}
void main()
{
	int x;
	system("cls");
	for(;;)
	{
	printf("1.Register\n2.Login\n3.Exit\nEnter the operation to perform : ");
	scanf("%d",&x);
	switch (x)
	{
	case 1: reg();
		break;
	case 2: login();
		break;
	case 3: printf("Exiting the program!\n");
		getch();
		exit(0);
		break;
	default: printf("Invalid input!\n\n");
		break;
	}
	}
	getch();
}

void reg()
{
	printf("\nNOTE : All fields are case sensitive.\n\n");
	printf("Enter the username you would like to register : ");
	fflush(stdin);
	scanf("%20s", &unamer);
	if (user_check()==1) {
		printf("\nUser already exists, try logging in!\n");
		return;
	}
	printf("Enter the password : ");
	write(getpass(),unamer);
	printf("\nSuccessfully Registered!\n");
}

int user_check() 
{
	FILE *fa;
	int i = 0, x, j=0, uc = 0, user_exists = 0;
	char username[21] = { 0 }, password[17] = { 0 };
	fa = fopen("reg.crypt8", "r");
	if (fa)
	{
		while ((x = getc(fa)) != EOF)
		{
			if (x != ':' && uc != 1)
			{
				username[i++] = x;
			}
			if (x == ':')
			{
				uc = 1;
				continue;
			}
			if (uc == 1 && x != '\n')
			{
				password[j++] = x;
			}
			if (x == '\n')
			{
				if (strcmp(unamer, username) == 0)
				{
					user_exists = 1;
					return user_exists;
				}
				else
				{
					for (; i > 0; i--)
						username[i] = '\0';
					for (; j > 0; j--)
						password[j] = '\0';
					uc = 0;
					continue;
				}
			}
		}
	}
}

void login()
{
	printf("\nNOTE : All fields are case sensitive.\n\n");
	printf("Enter the username : ");
	fflush(stdin);
	scanf("%20s", &unamel);
	printf("Enter the password : ");
	getpass();
	printf("\n\n");
	if (auth())
	{
		printf("Access Granted! Welcome!\n");
		getch();
		exit(0);
	}
	else
		printf("Access Denied! Try registering!\n\n");
}

char* getpass()
{
	char ch;
	int i = 0;
	while (i < 16)
	{
		if (i < 0)
			i = 0;
		ch = getch();
		if (ch != 13)
			if (ch == '\b' && i > 0)
			{
				printf("\b \b");
				i--;
			}
			else if (ch == '\b'&&i == 0) {
			}
			else
			{
				printf("*");
				pass[i] = ch;
				i++;
			}
		else
			i = 17;
	}
	*h_pass = hash(&pass);
	return h_pass;
}

void write(char password[],char username[])
{
	FILE *f;
	f = fopen("reg.crypt8", "at");
	fprintf(f, "%s:%s\n", username, password);
	fclose(f);
}
int auth()
{
	FILE *fa;
	int i = 0, x, j = 0, uc = 0, access = 0;
	char username[21] = { 0 }, password[17] = { 0 };
	fa = fopen("reg.crypt8", "r");
	if (fa)
	{
		while ((x = getc(fa)) != EOF)
		{
			if (x != ':' && uc != 1)
			{
				username[i++] = x;
			}
			if (x == ':')
			{
				uc = 1;
				continue;
			}
			if (uc == 1 && x != '\n')
			{
				password[j++] = x;
			}
			if (x == '\n')
			{
				if (strcmp(unamel, username) == 0 && strcmp(h_pass, password) == 0)
				{
					access = 1;
					break;
				}
				else
				{
					for (; i > 0; i--)
						username[i] = '\0';
					for (; j > 0; j--)
						password[j] = '\0';
					uc = 0;
					continue;
				}
			}
		}
	}
	else
		printf("No users registered yet. Try again!\n");
	return access;
}