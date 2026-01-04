# Panoramix

Small multithreaded simulation where villagers drink potion made by a druid before going to battle.

## Build

Use the provided Makefile:

```sh
make
```

Clean:

```sh
make clean
make fclean
```

## Run

Usage (same as in src/main.c):

```sh
./panoramix <nb_villagers> <pot_size> <nb_fights> <nb_refills>
```

Example:

```sh
./panoramix 5 3 10 2
```

## What it does

- A druid thread (`druid_routine`) refills a communal pot.
- Multiple villager threads (`villager_routine`) take servings to fight.
- Synchronization is done with mutexes and semaphores.

See implementation entry point: `panoramix_core` (src/core.c).

## Important symbols

- Configuration and runtime state: `panoramix_t` (include/panoramix.h)
- Villager argument struct: `villager_args_t` (include/panoramix.h)
- Main entry: `main` (src/main.c)
- Core orchestration: `panoramix_core` (src/core.c)
- Druid worker: `druid_routine` (src/druid.c)
- Villager worker: `villager_routine` (src/villager.c)

## Project files

- Makefile — build rules
- .gitignore — ignored files
- panoramix — generated executable (after build)
- include/panoramix.h — public types & prototypes
- src/main.c — argument validation and startup
- src/core.c — initialization, thread creation, teardown
- src/druid.c — druid logic and refills
- src/villager.c — villager behavior

## Notes

- This project is probably still in use in the school so don't steal it.
- Used to initiate students to threads in C language for future group projects.

- The program uses POSIX threads and semaphores; build on Unix-like systems.
- Input values must be positive integers (validated in src/main.c).
