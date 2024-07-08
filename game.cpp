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
    bool onPlatform = player.isCollidingWithPlatform(platforms);

    if (!onPlatform) {
        std::cout << "Game Over: Player fell off the platform!" << std::endl;
        QMessageBox::information(nullptr, "Game Over", "Game Over: Player fell off the platform!");
        // Optionally, reset the game state or perform other actions upon game over
    }
}
void Game::handleVictory(){
    if (amountDistance == 700) { // Change 1000 to the specific distance you want to check for
        std::cout << "Congratulations! You won the game!" << std::endl;
        emit victory(); // Emit the victory signal
    }
}
