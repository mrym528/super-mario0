#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QVBoxLayout>
#include <vector>
#include <QTimer>
#include "platform.h"
#include "decorator.h"
#include "player.h"
#include "game.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
    void keyPressEvent(QKeyEvent *event) override;
private:
    QGraphicsScene *scene;
    QGraphicsView *view;
    std::vector<Platform> platforms;
    std::vector<Decorator> decorators;
    Player *player;
    Game *game;
    void setupScene();
    void drawObjects();
    void setupGame();

private slots:
    void handleGameOver();
    void handleVictory();
};

#endif // MAINWINDOW_H
