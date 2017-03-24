#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>
#include "conio.h"
char unamer[21], unamel[21],pass[17];
void reg();
void login();
char* getpass();
int auth();
void write(char,char);
void main()
{
	int x;
	system("cls");
	printf("1.Register\n2.Login\nEnter the operation to perform : ");
	scanf("%d", &x);
	switch (x)
	{
	case 1: reg();
		break;
	case 2: login();
		break;
	default: printf("Invalid input!\n");
	}
	getch();
}

void reg()
{
	printf("Enter the username you would like to register : ");
	fflush(stdin);
	scanf("%20s", &unamer);
	printf("Enter the password : ");
	getpass();
	write(pass,unamer);
}

void login()
{
	printf("Enter the username : ");
	fflush(stdin);
	scanf("%20s", &unamel);
	printf("Enter the password : ");
	getpass();
	printf("\n\n");
	if (auth())
		printf("Access Granted!");
	else
		printf("Access Denied!");
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
			else
			{
				printf("*");
				pass[i] = ch;
				i++;
			}
		else
			i = 17;
	}
	return pass;
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
	int i = 0, x;
	char username[21];
	fa = fopen("reg.crypt8", "r");
	while ((x = getc(fa)) != EOF)
		if (x != 58)
		{
			username[i] = x;
			i++;
		}
		else
			break;
	puts(username);
}
