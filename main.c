/*
** EPITECH PROJECT, 2025
** B-CCP-400-LYN-4-1-panoramix-hugo.cathelain
** File description:
** main
*/

///////////////////////////////////////////////////////////////////////////////
/// Dependencies
///////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

///////////////////////////////////////////////////////////////////////////////
int check_args(int argc, char **argv)
{
    if (argc != 5) {
        printf(
            "Usage: %s <nb_villagers> <pot_size> <nb_fights> <nb_refills>\n",
            argv[0]);
        return (84);
    }
    if (atoi(argv[1]) <= 0 || atoi(argv[2]) <= 0 ||
        atoi(argv[3]) <= 0 || atoi(argv[4]) <= 0) {
        printf("Values must be >0.\n");
        return (84);
    }
    return (0);
}

///////////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv)
{
    int error_chack = check_args(argc, argv);

    if (error_chack == 84) {
        return (84);
    }
    return (0);
}
