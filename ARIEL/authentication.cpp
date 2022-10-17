#include "iauthentication.h"

/*************************/
/* FUNCTION DECLARATIONS */
/*************************/

Authentication_status signUp(char *, char *);
Authentication_status login(char *, char *);
Authentication_status removeUser(char *);
static Authentication_status saveNewUserAndPassword(char *, char *);
static Authentication_status checkLogin(char *, char *);
static int fileExist(void);
static int sanitizeUser(char *);
static int sanitizePassword(char *);
static unsigned char *encode(char *);
static unsigned int countMaxUsers(void);

/********************/
/* PUBLIC FUNCTIONS */
/********************/

Authentication_status
signUp(char *user, char *password)
{
	/* check if file exist */
	if (!fileExist())
		if (system("touch shadow"))
			return AU_ERROR;

	/* sanitize user and password */
	if (!sanitizeUser(user))
		return AU_SIGN_UP_ERROR;
	if (!sanitizePassword(password))
		return AU_SIGN_UP_ERROR;

	if (countMaxUsers() > MAX_USERS)
		return AU_MAX_USERS_REACHED;

	if (checkLogin(user, password) == AU_AUTHENTICATION_OK)
		return AU_USER_EXIST;

	/* save new user and password; final step */
	return saveNewUserAndPassword(user, password);
}

Authentication_status
login(char *user, char *password)
{
	/* sanitize user and password */
	if (!sanitizeUser(user))
		return AU_AUTHENTICATION_ERROR;
	if (!sanitizePassword(password))
		return AU_AUTHENTICATION_ERROR;

	return checkLogin(user, password);
}

Authentication_status
removeUser(char *user)
{
	char buffer[BUFFER_SIZE];
	char tmp_buffer[BUFFER_SIZE];
	char *find_user;
	FILE *login_file;
	FILE *tmp_file;

	login_file = fopen(LOGIN_FILE, "rw");
	tmp_file = fopen(TMP_LOGIN_FILE, "w");

	while (fgets(buffer, BUFFER_SIZE, login_file)) {
		strcpy(tmp_buffer, buffer);
		find_user = strtok(tmp_buffer, ":");
		if (strcmp(user, find_user))
			fprintf(tmp_file, "%s", buffer);
	}

	system("mv newshadow shadow");

	fclose(login_file);
	fclose(tmp_file);

	return AU_REMOVE_USER_OK;
}

/*******************/
/* LOCAL FUNCTIONS */
/*******************/

static Authentication_status
saveNewUserAndPassword(char *user, char *password)
{
	unsigned int i;
	unsigned char *encode_password;
	unsigned int sha256_length;
	char string_encode[BUFFER_SIZE];
	FILE *login_file;

	login_file = fopen(LOGIN_FILE, "a+b");

	if (!login_file)
		return AU_ERROR;	
	
	sha256_length = gcry_md_get_algo_dlen(GCRY_MD_SHA256);
	encode_password = encode(password);

	/* convert encode password to string */
	for (i = 0; i < sha256_length; i++)
		sprintf(string_encode+(i*2), "%02x", encode_password[i]);

	/* write on file */
	fprintf(login_file, "%s:%s:\n", user, string_encode);

	fclose(login_file);

	return AU_SIGN_UP_OK;
}

static Authentication_status
checkLogin(char *user, char *password)
{
	unsigned int i;
	unsigned char *encode_password;
	unsigned int sha256_length;
	char string_encode[BUFFER_SIZE];
	char buffer[BUFFER_SIZE];
	char *token;
	FILE *login_file;

	login_file = fopen(LOGIN_FILE, "r");

	sha256_length = gcry_md_get_algo_dlen(GCRY_MD_SHA256);
	encode_password = encode(password);

	/* convert encode password to string */
	for (i = 0; i < sha256_length; i++)
		sprintf(string_encode+(i*2), "%02x", encode_password[i]);

	while (fgets(buffer, sizeof(buffer), login_file)) {
		token = strtok(buffer, ":");
		if (!strcmp(user, token)) {
			token = strtok(NULL, ":");
			if (!strcmp(string_encode, token))
				return AU_AUTHENTICATION_OK;
		}
	}

	fclose(login_file);

	return AU_AUTHENTICATION_ERROR;	
}

/********************************* Create file ********************************/

static int
fileExist(void)
{
	struct stat st;
	if (!stat(LOGIN_FILE, &st))
		return 1;
	else
		return 0;
}

/****************************** Sanitize Input *******************************/

static int
sanitizeUser(char *user)
{
	regex_t regex;
	char regex_string[32] = ".*[A-Z].*";

	/* test length of user */
	if (strlen(user) < MIN_LEN_USER || strlen(user) > MAX_LEN_USER)
		return 0;

	/* compile regex; return 0 on success */
	if (regcomp(&regex, regex_string, REG_EXTENDED))
		return 0;

	/* execute regular expression; return 0 on success */
	if (regexec(&regex, user, 0, NULL, 0) != 0)
		return 0;

	/* free regex */
	regfree(&regex);

	return 1;
}

static int
sanitizePassword(char *password)
{
	regex_t regex;
	char regex_string[192] =
	"(.*[A-Z].*[0-9].*[!@#$%&*].*)|(.*[A-Z].*[!@#$%&*].*[0-9].*)|"
	"(.*[0-9].*[A-Z].*[!@#$%&*].*)|(.*[0-9].*[!@#$%&*].*[A-Z].*)|"
	"(.*[!@#$%&*].*[A-Z].*[0-9].*)|(.*[!@#$%&*].*[0-9].*[A-Z].*)";

	/* test length of password */
	if (strlen(password) < MIN_LEN_PW || strlen(password) > MAX_LEN_PW)
		return 0;

	/* compile regular expression */
	if (regcomp(&regex, regex_string, REG_EXTENDED))
		return 0;
	
	/* execute regular expression */
	if (regexec(&regex, password, 0, NULL, 0) != 0)
		return 0;

	/* free regex */
	regfree(&regex);

	return 1;
}


/******************************** Others **************************************/

static unsigned char *
encode(char *password)
{
	gcry_md_hd_t h;

	/* init context */
	gcry_md_open(&h, GCRY_MD_SHA256, GCRY_MD_FLAG_SECURE);
	/* generate hash */
	gcry_md_write(h, password, strlen(password));
	/* get result and return */
	return gcry_md_read(h, GCRY_MD_SHA256);
}


static unsigned int
countMaxUsers(void)
{
	FILE *login_file;
	int count;
	char buffer[1024];

	login_file = fopen(LOGIN_FILE, "r");

	count = 0;
	while (fgets(buffer, BUFFER_SIZE, login_file))
		count++;

	fclose(login_file);

	return count;
}
