#ifndef			__ERROR_MSGS__
# define		__ERROR_MSGS__

/*
** Xfuncs Error macros.
*/
# define	READDIR_ERR	"readdir function failed\n"
# define       	OPENDIR_ERR	"opendir function failed\n"
# define       	KILL_ERR	"kill function failed\n"
# define       	WRITE_ERR	"Write function failed\n"
# define       	OPEN_ERR	"Couldn't open the requested file descriptor\n"
# define       	READ_ERR	"Couldn't read the requested file descriptor\n"
# define       	CLOSE_ERR	"Couldn't clode the requested file descriptor\n"
# define       	MALLOC_ERR	"Couldn't malloc the requested pointer\n"
# define	REALLOC_ERR	"Couldn't realloc the requested pointer\n"
# define	IOCTL_ERR	"Ioctl FAIL"
/*
** Lists Functions
*/
# define	KEY_NOT_FOUND	"The requested string was not found in the list"

/*
** Hashing functions
*/
# define	HASH_NOT_FOUND	"The requested string was not found" \
  " in the hash table"
# define	HASH_DEL_ERR	"The requested string to delete was not found"

/*
** History Functions
*/
# define	NO_REQ_LINK_AVAILABLE	"The requested link doesn't exist" \
					"Or isn't available\n"

/*
** Lexer Functions
*/
# define	HOME_ERROR		"No referencies to Home Directory" \
					"in the Shell env, please set one"
# define	INVALID_STRING_INTER	"The string given in params is either" \
					"NULL, or second interval is too high"

#endif	       	/* __ERROR_MSGS__ */
