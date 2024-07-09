#include "Game.h"
#include <iostream>
#include <QMessageBox>
#include <vector>
#include "platform.h"
#include "player.h"
#include "decorator.h"

Game::Game(QGraphicsView &view, QGraphicsScene &scene, std::vector<Platform> platform, std::vector<Decorator> decorator, Player &player, int amountDistance)
    : view(view), scene(scene), platforms(std::move(platform)), decorators(std::move(decorator)), player(player), amountDistance(amountDistance) {}
void Game::handleGameOver(){
   /* bool onPlatform = player.isCollidingWithPlatform(platforms);

    if (!onPlatform) {
        std::cout << "Game Over: Player fell off the platform!" << std::endl;
        QMessageBox::information(nullptr, "Game Over", "Game Over: Player fell off the platform!");
        emit gameOver();
    }*/
}
void Game::handleVictory(){
    if (amountDistance == 1500) {
        std::cout << "Congratulations! You won the game!" << std::endl;
        emit victory();
    }
}