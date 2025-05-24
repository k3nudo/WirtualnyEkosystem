cmake_minimum_required(VERSION 3.29)
project(untitled)

set(CMAKE_CXX_STANDARD 20)

add_executable(untitled main.cpp
        Organizm.cpp
        Organizm.h
        generatorlosowy.cpp
        generatorlosowy.h
        mieszkaniec.cpp
        mieszkaniec.h
        nisza.cpp
        nisza.h
        osobniki.cpp
        osobniki.h
        sasiedztwo.cpp
        sasiedztwo.h
        srodowisko.cpp
        srodowisko.h
        ustawienia.h
        )
