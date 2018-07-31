#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ge = new gameEngine(ui->frm_main->x(), ui->frm_main->y(), ui->frm_next->x(), ui->frm_next->y());
    ge2 = new gameEngine(ui->frm2_main->x(), ui->frm2_main->y(), ui->frm2_next->x(), ui->frm2_next->y());
    timer = new QTimer();
    timer->setInterval(SLOW_TIME_INTERVAL);
    timer2= new QTimer();
    timer2->setInterval(SLOW_TIME_INTERVAL);
    connect(ui->btn_start, SIGNAL(clicked(bool)), this, SLOT(start_game()));
    connect(timer, SIGNAL(timeout()), this, SLOT(timer_start()));
    connect(timer2, SIGNAL(timeout()), this, SLOT(timer2_start()));
    connect(ui->btn_new, SIGNAL(clicked(bool)), this, SLOT(new_game()));
    setFocusPolicy(Qt::StrongFocus);
    game_is_started = false;
}

void MainWindow::keyReleaseEvent(QKeyEvent* event)
{
    int key = event->key();

    if(game_is_started)
    {
        switch (key)
        {
        case Qt::Key_S:
            timer->setInterval(SLOW_TIME_INTERVAL);
            break;

        case Qt::Key_W:
            if(ge->get_move_down_ok())
            {
                ge->rotate();
                update();
            }
            break;

        default:
            break;
        }

        switch (key)
        {
        case Qt::Key_Down:
            timer2->setInterval(SLOW_TIME_INTERVAL);
            break;

        case Qt::Key_Up:
            if(ge2->get_move_down_ok())
            {
                ge2->rotate();
                update();
            }
            break;

        default:
            break;
        }
    }
}

void MainWindow::keyPressEvent(QKeyEvent * event)
{
    if(ge->get_move_down_ok() && game_is_started)
    {
        int key = event->key();int i=-1;

        switch (key)
        {
        case Qt::Key_A:
            ge->move_left();i=i+1;
            break;

        case Qt::Key_D:
            ge->move_right();i=i+1;
            break;

        case Qt::Key_S:
            if(timer->interval() != FAST_TIME_INTERVAL)
                timer->setInterval(FAST_TIME_INTERVAL);
            break;

        default:
            break;
            if(i>=0)
            { timer->stop();timer2->stop();}
        }

        switch (key)
        {
        case Qt::Key_Left:
            ge2->move_left();
            break;

        case Qt::Key_Right:
            ge2->move_right();
            break;

        case Qt::Key_Down:
            if(timer2->interval() != FAST_TIME_INTERVAL)
                timer2->setInterval(FAST_TIME_INTERVAL);
            break;

        default:
            break;
        }
    }

    update();
}

void MainWindow::paintEvent(QPaintEvent *)
{
    int h = MAIN_BOARD_HEIGHT;
    int w = MAIN_BOARD_WIDTH;

    QPainter painter(this);

    for(int n = 0; n < NUM_OF_BOARDS; n++)
    {
        h = (n == MAIN_BOARD ? h : NEXT_BOARD_HEIGHT);
        w = (n == MAIN_BOARD ? w : NEXT_BOARD_WIDTH);

        for(int r = 0; r < h; r++)
        {
            for(int c = 0; c < w; c++)
            {
                //Draw a rectangle in the cell
                cell acell = (n == NEXT_BOARD ? ge->get_next_bd().get_a_cell(r, c) : ge->get_main_bd().get_a_cell(r, c));
                QPointF position = acell.get_position();
                QSizeF sizef(CELL_LENGTH, CELL_LENGTH);
                QRectF rectf(position, sizef);
                QColor color = acell.draw_cell_color();
                painter.fillRect(rectf, color);

                cell acell2 = (n == NEXT_BOARD ? ge2->get_next_bd().get_a_cell(r, c) : ge2->get_main_bd().get_a_cell(r, c));
                QPointF position2 = acell2.get_position();
                QSizeF sizef2(CELL_LENGTH, CELL_LENGTH);
                QRectF rectf2(position2, sizef2);
                QColor color2 = acell2.draw_cell_color();
                painter.fillRect(rectf2, color2);
            }
        }
    }
}

void MainWindow::timer_start()
{
    if(ge->get_move_down_ok())
    {
        ge->move_down();
    }
    else
    {
        if(ge->num_rows_cld() > 0)
        {
            int score = ge->compute_score();
            warning1(score);
            score += ui->lbl_score->text().toInt();
            ge->clear_rows();
            ge->rows_move_down();
            ui->lbl_score->setText(QString::number(score));
        }
        ge->main_place_a_shape();
        ge->get_next_bd().clear_board();
        ge->next_place_a_shape();
    }
    update();
}

void MainWindow::timer2_start(){
    if(ge2->get_move_down_ok())
    {
        ge2->move_down();
    }
    else
    {
        if(ge2->num_rows_cld() > 0)
        {
            int score = ge2->compute_score();
            warning2(score);
            score += ui->lbl2_score->text().toInt();
            ge2->clear_rows();
            ge2->rows_move_down();
            ui->lbl2_score->setText(QString::number(score));
        }
        ge2->main_place_a_shape();
        ge2->get_next_bd().clear_board();
        ge2->next_place_a_shape();
    }
    update();
}

void MainWindow::warning1(int score){
    if(score>1){
        int num=sqrt(score);
        ui->lbl2_warning->setStyleSheet("color:red;");
        ui->lbl2_warning_num->setStyleSheet("color:red;");
        ui->lbl2_warning_num->setText(QString::number(num));
        ui->lbl2_warning->show();
        ui->lbl2_warning_num->show();
        tim = new QTimer(this);
        mapper = new QSignalMapper();
        connect(tim,SIGNAL(timeout()),mapper,SLOT(map()));
        mapper->setMapping(tim,num);
        tim->start(num*WAITTIME);
        connect(mapper,SIGNAL(mapped(int)),this,SLOT(rows_up(int)));
    }
}

void MainWindow::warning2(int score){
    if(score>1){
        int num=sqrt(score);
        ui->lbl_warning->setStyleSheet("color:red;");
        ui->lbl_warning_num->setStyleSheet("color:red;");
        ui->lbl_warning_num->setText(QString::number(num));
        ui->lbl_warning->show();
        ui->lbl_warning_num->show();
        tim = new QTimer(this);
        mapper = new QSignalMapper();
        connect(tim,SIGNAL(timeout()),mapper,SLOT(map()));
        mapper->setMapping(tim,num);
        tim->start(num*WAITTIME);
        connect(mapper,SIGNAL(mapped(int)),this,SLOT(rows2_up(int)));
    }
}

void MainWindow::rows_up(int num){
    ge2->rows_move_up(num);
    ui->lbl2_warning->hide();
    ui->lbl2_warning_num->hide();
    if(tim->isActive()){
        tim->stop();
    }
}

void MainWindow::rows2_up(int num){
    ge->rows_move_up(num);
    ui->lbl_warning->hide();
    ui->lbl_warning_num->hide();
    if(tim->isActive()){
        tim->stop();
    }
}

void MainWindow::start_game()
{
    ge->next_place_a_shape();
    ge->main_place_a_shape();
    ge->get_next_bd().clear_board();
    ge->next_place_a_shape();
    update();

    ge2->next_place_a_shape();
    ge2->main_place_a_shape();
    ge2->get_next_bd().clear_board();
    ge2->next_place_a_shape();
    update();
    ui->btn_start->setEnabled(false);
    timer->start();
    timer2->start();
    game_is_started = true;
}

void MainWindow::new_game()
{
    game_is_started = false;
    timer->stop();
    timer2->stop();

    delete ge;
    ge = NULL;

    ge = new gameEngine(ui->frm_main->x(), ui->frm_main->y(), ui->frm_next->x(), ui->frm_next->y());
    //ge2
    delete ge2;
    ge2 = NULL;

    ge2 = new gameEngine(ui->frm2_main->x(), ui->frm2_main->y(), ui->frm2_next->x(), ui->frm2_next->y());
    ui->lbl_score->setText("0");
    ui->lbl2_score->setText("0");
    ui->btn_start->setEnabled(true);

    update();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete ge;//ge2
    delete ge2;
    ui = NULL;
    ge = NULL;
}
