/*
** EPITECH PROJECT, 2019
** random.c
** File description:
** Simple description
*/

#include <stdlib.h>

int my_random(int min, int max)
{
    return (rand() % (max - min + 1) + min);
}
