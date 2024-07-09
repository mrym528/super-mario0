#include "mainwindow.h"
#include <iostream>
#include <QMessageBox>
#include <vector>
#include <QString>
#include <QVBoxLayout>
#include <QKeyEvent>
#include <QTimer>
#include "platform.h"
#include "decorator.h"
#include "player.h"
#include "game.h"

// constructor
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), scene(new QGraphicsScene(this)), view(new QGraphicsView(scene)), player(nullptr)
{
    setupScene();
    setupGame();
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
}
//destructor
MainWindow::~MainWindow()
{
    delete view;
    delete scene;
    delete player;
    delete game;
}

void MainWindow::setupScene()
{
    if (!scene || !view) {
        std::cerr << "Scene or View initialization failed." << std::endl;
        return;
    }
    scene->setSceneRect(0, 0, 2000, 750);
    view->setFixedSize(2000, 750);
    // Add the view to the main window
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(view);
    QWidget *centralWidget = new QWidget;
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);
}

void MainWindow::drawObjects()
{
    if (!scene) {
        std::cerr << "Scene is not properly initialized." << std::endl;
        return;
    }
    // Draw decorations
    for (const auto &decorator : decorators)
    {
        decorator.draw(*scene);
    }
    // Draw platforms
    for (const auto &platform : platforms)
    {
        platform.draw(*scene);
    }
    // Draw player
    if (player)
    {
        player->draw(*scene);
    }

}

void MainWindow::setupGame()
{
    // Initialize platforms
    Platform platform1(200, 20, Position(0, 600), ":/platform/assets/platform.png");
    Platform platform2(100, 10, Position(600, 300), ":/platformSmallTall/assets/platformSmallTall.png");
    Platform platform3(200, 20, Position(650, 600), ":/platform/assets/platform.png");
    Platform platform4(200, 20, Position(1300, 600), ":/platform/assets/platform.png");
    platforms.push_back(platform1);
    platforms.push_back(platform2);
    platforms.push_back(platform3);
    platforms.push_back(platform4);

    // Initialize decorators
    Decorator decorator1(1000, 800, Position(0, 0), ":/background/assets/background.png");
    Decorator decorator2(100, 100, Position(800, 230), ":/hills/assets/hills.png");
    decorators.push_back(decorator1);
    decorators.push_back(decorator2);

    // Initialize player
    player = new Player(50, 50, Position(100, 550), 50); // Adjust as necessary
    scene->addItem(player);
    // Initialize game
    game = new Game(*view, *scene, platforms, decorators, *player, 1000); // Adjust as necessary

    connect(game, &Game::gameOver, this, &MainWindow::handleGameOver);
    connect(game, &Game::victory, this, &MainWindow::handleVictory);

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [=]() {
        if (player && view) {
            player->applyGravity();
            view->centerOn(player);
        }
    });

    timer->start(1000);
    // Start drawing objects
    drawObjects();
}

void MainWindow::handleGameOver()
{
    std::cout << "Game Over: Player fell off the platform!" << std::endl;
    QMessageBox::information(nullptr, "Game Over", "Game Over: Player fell off the platform!");

}

void MainWindow::handleVictory()
{
    std::cout << "Congratulations! You won the game!" << std::endl;
    QMessageBox::information(nullptr, "Victory", "Congratulations! You won the game!");
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (player)
    {
        switch (event->key())
        {
        case Qt::Key_Left:
            player->moveLeft();
            break;
        case Qt::Key_Right:
            player->moveRight();
            break;
        case Qt::Key_Space:
            player->jump();
            break;
        default:
            QMainWindow::keyPressEvent(event);
            break;
        }
    }
}
