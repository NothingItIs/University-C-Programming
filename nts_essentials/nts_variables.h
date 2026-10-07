#ifndef ESSENTIALS_H_FUNCS
#define ESSENTIALS_H_FUNCS

#define RESET "\033[0m"
#define BOLD "\033[1m"
#define UNDERLINE "\033[4m"
#define REVERSED "\033[7m"

#define LIGHT_RED "\033[1;31m"
#define RED "\033[31m"
#define DARK_RED "\033[2;31m"

#define LIGHT_GREEN "\033[1;32m"
#define GREEN "\033[32m"
#define DARK_GREEN "\033[2;32m"

#define LIGHT_YELLOW "\033[1;33m"
#define YELLOW "\033[33m"
#define DARK_YELLOW "\033[2;33m"

#define LIGHT_BLUE "\033[1;34m"
#define BLUE "\033[34m"
#define DARK_BLUE "\033[2;34m"
#define LIGHT_MAGENTA "\033[1;35m"
#define MAGENTA "\033[35m"
#define DARK_MAGENTA "\033[2;35m"

#define LIGHT_CYAN "\033[1;36m"
#define CYAN "\033[36m"
#define DARK_CYAN "\033[2;36m"


#define LIGHT_WHITE "\033[1;37m"
#define WHITE "\033[37m"
#define DARK_WHITE "\033[2;37m"

#define LIGHT_BLACK "\033[1;30m"
#define BLACK "\033[30m"
#define DARK_BLACK "\033[2;30m"

#define LIGHT_GRAY "\033[1;37m"
#define GRAY "\033[37m"
#define DARK_GRAY "\033[2;37m"

#define LIGHT_ORANGE "\033[1;33m"
#define ORANGE "\033[33m"
#define DARK_ORANGE "\033[2;33m"

#define LIGHT_PURPLE "\033[1;35m"
#define PURPLE "\033[35m"
#define DARK_PURPLE "\033[2;35m"

#define LIGHT_BROWN "\033[1;33m"
#define BROWN "\033[33m"
#define DARK_BROWN "\033[2;33m"

#define clear() printf("\033[H\033[J")

#define LEN(x) (sizeof(x) / sizeof(x[0]))

#endif