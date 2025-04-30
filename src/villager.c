/*
** EPITECH PROJECT, 2025
** B-CCP-400-LYN-4-1-panoramix-hugo.cathelain
** File description:
** villager
*/

///////////////////////////////////////////////////////////////////////////////
/// Dependencies
///////////////////////////////////////////////////////////////////////////////
#include "panoramix.h"

///////////////////////////////////////////////////////////////////////////////
static void announce_battle_start(villager_args_t *villager)
{
    printf("Villager %d: Going into battle!\n", villager->id);
}

static int request_potion(villager_args_t *villager, panoramix_t *data)
{
    int need_to_wake_druid = 0;

    pthread_mutex_lock(&data->pot_mutex);
    printf("Villager %d: I need a drink... I see %d servings left.\n",
        villager->id, data->servings_left);
    if (data->servings_left == 0) {
        need_to_wake_druid = 1;
        pthread_mutex_unlock(&data->pot_mutex);
        printf("Villager %d: Hey Pano wake up! We need more potion.\n",
            villager->id);
        sem_post(&data->pot_empty_sem);
        sem_wait(&data->pot_filled_sem);
        pthread_mutex_lock(&data->pot_mutex);
    }
    return need_to_wake_druid;
}

static int drink_and_fight(villager_args_t *villager, panoramix_t *data,
    int need_to_wake_druid, int fights_left)
{
    if (data->servings_left > 0) {
        data->servings_left--;
        pthread_mutex_unlock(&data->pot_mutex);
        if (need_to_wake_druid) {
            need_to_wake_druid = 0;
            sem_post(&data->pot_filled_sem);
        }
        printf("Villager %d: Take that roman scum! Only %d left.\n",
            villager->id, fights_left - 1);
        fights_left--;
    } else {
        pthread_mutex_unlock(&data->pot_mutex);
    }
    return fights_left;
}

static void finish_villager_work(villager_args_t *villager, panoramix_t *data)
{
    pthread_mutex_lock(&data->pot_mutex);
    data->villager_left--;
    pthread_mutex_unlock(&data->pot_mutex);
    sem_post(&data->pot_empty_sem);
    printf("Villager %d: I'm going to sleep now.\n", villager->id);
}

void *villager_routine(void *arg)
{
    villager_args_t *villager = (villager_args_t *)arg;
    panoramix_t *data = villager->data;
    int fights_left = data->nb_fights;
    int need_to_wake_druid = 0;

    announce_battle_start(villager);
    while (fights_left > 0) {
        usleep(rand() % 55);
        need_to_wake_druid = request_potion(villager, data);
        fights_left = drink_and_fight(villager, data, need_to_wake_druid,
            fights_left);
        if (data->servings_left == 0 && need_to_wake_druid == 0)
            break;
    }
    finish_villager_work(villager, data);
    return NULL;
}
