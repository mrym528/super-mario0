#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QGraphicsView>
#include <vector>
#include <QObject>
#include <QGraphicsScene>
#include "Position.h"
#include "player.h"
#include "decorator.h"
class Game : public QObject{
Q_OBJECT
public:
    QGraphicsView &view;
    QGraphicsScene &scene;
    std::vector <Platform> platforms;
    std::vector <Decorator> decorators;
    Player &player;
    int amountDistance;
public:
    Game (QGraphicsView &view, QGraphicsScene &scene, std::vector <Platform> platform, std::vector <Decorator> decorator, Player &player, int amountDistance);
    void handleGameOver();
    void handleVictory();
signals:
    void victory();
    void gameover();

};

#endif // GAME_H
