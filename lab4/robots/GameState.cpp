/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 */

#include "GameState.h"
#include "utilities.h"
#include "constants.h"
#include <iostream>

GameState::GameState(){}

GameState::GameState(int numberOfRobots) {
    for (int i = 0; i < numberOfRobots; i++) {
        Robot* robot = new Robot();

        while(!isEmpty(*robot)) {
            delete robot;
            robot = new Robot();
        }
        robots.push_back(robot);
    }
    teleportHero();
}

GameState::~GameState() {
    for (auto robot : robots) {
        delete robot;
    }
}

GameState::GameState(const GameState &other) {
    copyOther(other);
}

GameState& GameState::operator=(const GameState& other) {
    if (this != &other) {

        for (auto robot : robots) {
            delete robot; // Free memory
        }
        robots.clear();
        copyOther(other);
    }
    return *this;
}

void GameState::copyOther(const GameState &other) {
    hero = other.hero;
    for (auto robot : other.robots) {
        robots.push_back(robot->clone());
    }
}

void GameState::draw(QGraphicsScene *scene) const {
    scene->clear();
    for (size_t i = 0; i < robots.size(); ++i)
        robots[i]->draw(scene);
    hero.draw(scene);
}

void GameState::teleportHero() {
    do hero.teleport();
    while (!isEmpty(hero));
}

void GameState::moveRobots() {
    for (unsigned int i = 0; i < robots.size(); i++)
        robots[i]->moveTowards(hero);
}

int GameState::countCollisions() {
    int numberDestroyed = 0;
    unsigned int i = 0;
    while (i < robots.size()) {
        if (!robots[i]->isJunk() && countRobotsAt(*robots[i]) > 1) {
            Robot* new_junk = new Junk(*robots[i]);
            delete robots[i];
            robots[i] = new_junk;
            numberDestroyed++;
        }
        ++i;
    }
    return numberDestroyed;
}

bool GameState::anyRobotsLeft() const {
    for (Robot* robot : robots) {
        if (!robot->isJunk())
            return true;
    }
    return false;
}

bool GameState::heroDead() const {
    return !isEmpty(hero);
}

bool GameState::isSafe(const Unit& unit) const {
    for (unsigned int i = 0; i < robots.size(); i++)
        if (robots[i]->attacks(unit)) return false;
    return true;
}

void GameState::moveHeroTowards(const Point& dir) {
    hero.moveTowards(dir);
}

Hero GameState::getHero() const {return hero;}

/*
 * Free of robots and junk only
 */
bool GameState::isEmpty(const Unit& unit) const {
    return (countRobotsAt(unit) == 0);
}

/*
 * How many robots are there at unit?
 */
int GameState::countRobotsAt(const Unit& unit) const {
    int count = 0;
    for (size_t i = 0; i < robots.size(); ++i) {
        if (robots[i]->at(unit))
            count++;
    }
    return count;
}
