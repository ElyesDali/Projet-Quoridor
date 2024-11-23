cmake_minimum_required(VERSION 3.29)
project(quoridor C)

set(CMAKE_C_STANDARD 11)

add_executable(quoridor menu.c
        Barriere.c
        Plato.c
        deplacement.c
        deplacement.h
        Plato.h
        Barriere.h
        Main.c
        menu.h
        Player.h
        AfficheurPersonnaliser.h
        AfficheurPersonnaliser.c
        Victoire.c
        Victoire.h
        gameLoop.c
        gameLoop.h
)
