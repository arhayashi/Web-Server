#ifndef _CONSTANTS_H_

#define _CONSTANTS_H_

#define SERVER_ERR  (-1)
#define SERVER_WARN (0)
#define SERVER_SUCC (1)

/* turns x into a string */

#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

#endif
