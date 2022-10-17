#ifndef IAUTHENTICATION_H
#define IAUTHENTICATION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <regex.h>
#include <sys/stat.h>
#include <gcrypt.h>

#define MIN_LEN_USER 8
#define MAX_LEN_USER 32
#define MIN_LEN_PW   8
#define MAX_LEN_PW   32
#define MAX_USERS    5
#define BUFFER_SIZE  1024

#define LOGIN_FILE     "shadow"
#define TMP_LOGIN_FILE "newshadow"

/* enumerations */
typedef enum authentication_system {
	AU_AUTHENTICATION_OK = 0,
	AU_AUTHENTICATION_ERROR = 1,
	AU_SIGN_UP_OK = 2,
	AU_SIGN_UP_ERROR = 3,
	AU_REMOVE_USER_OK = 4,
	AU_REMOVE_USER_ERROR = 5,
	AU_USER_EXIST = 6,
	AU_USER_DOES_NOT_EXIST = 7,
	AU_MAX_USERS_REACHED = 8,
	AU_PERMISSION_DENIED = 9,
	AU_ERROR = 99
} Authentication_status;

/* visible functions */
Authentication_status signUp(char *, char *);
Authentication_status login(char *, char *);
Authentication_status removeUser(char *);

#endif
