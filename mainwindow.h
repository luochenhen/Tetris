#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "public.h"
#include "ui_mainwindow.h"
#include "game_engine.h"
#include "board.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void paintEvent(QPaintEvent *) override;
    void keyReleaseEvent(QKeyEvent * event) override;
    void keyPressEvent(QKeyEvent * event) override;
    ~MainWindow();

public slots:
    void start_game();
    void timer_start();
    void timer2_start();
    void warning1(int);
    void warning2(int);
    void new_game();
    void rows_up(int);
    void rows2_up(int);

private:
    Ui::MainWindow *ui;
    gameEngine* ge;
    gameEngine* ge2;
    QTimer* timer;
    QTimer* timer2;
    bool game_is_started;
    QTimer* tim;
    QTimer* tim2;
    QSignalMapper *mapper;
};

#endif // MAINWINDOW_H
