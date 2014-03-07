//
// breakout.c
//
// Amir Kurtovic
// amirkurtovic@gmail.com
// 
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include "gevents.h"
#include "gobjects.h"
#include "gwindow.h"

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// paddle dimensions
#define PADDLEHEIGHT 10
#define PADDLEWIDTH 35
#define PADDLEY 550

// brick dimension
#define BRICKHEIGHT 10
#define BRICKWIDTH 35

// prototypes
GRect initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel score = initScoreboard(window);

    // number of bricks initially
    int brickCount = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;

    // keep playing until game over

   double verticalVelocity = 2.6;
   srand(time(NULL));
   double horizontalVelocity = drand48() + 1.2;
 
   // draw label below paddle
    GLabel about = newGLabel("BREAKOUT (by Amir Kurtovic)                       Click to start");
    setFont(about, "SansSerif-12");
    setColor(about, "BLACK");
    setLocation(about, 5, 590);
    add(window, about);
    
    // start game after click
    waitForClick();
    
    removeGWindow(window, about);
   
    while (lives > 0 && brickCount > 0)
    {
        
        GEvent mouse = getNextEvent (MOUSE_EVENT);
        
        if (mouse != NULL)
        {
            if (getEventType(mouse) == MOUSE_MOVED)
            {
            double paddleX = getX(mouse) - (PADDLEWIDTH/2);
            double paddleY = PADDLEY;
            setLocation(paddle, paddleX, PADDLEY);
            }
        }
        
        move(ball, horizontalVelocity, verticalVelocity);
        pause(8);
        
        
        //detect collisions around the window
        if (getX(ball) + getWidth(ball) >= WIDTH)
        {
            horizontalVelocity = -horizontalVelocity;
        }
        else if (getX(ball) <= 0)
        {
            horizontalVelocity = -horizontalVelocity;
        }
        
        if (getY(ball) + getWidth(ball) >= HEIGHT)
        {
            pause(2000);
            setLocation(ball, (WIDTH/2-10), (HEIGHT/5));
            lives -= 1;
            waitForClick();
        }
        else if (getY(ball) <= 0)
        {
            verticalVelocity = -verticalVelocity;
        }
        
        // detect collisions with other objects
        GObject object = detectCollision(window, ball);
        
        if (object != NULL)
        {
            if (object == paddle)
            {
                verticalVelocity = -verticalVelocity;
               // horizontalVelocity = drand48();
            }
            
            if (strcmp(getType(object), "GRect") == 0)
            {
                if (object != paddle)
                {
                brickCount -= 1;
                points += 1;
                updateScoreboard(window, score, points);
                removeGWindow (window, object);
                verticalVelocity = -verticalVelocity + 0.05;
                }
            }
        } 
    }
    
    removeGWindow(window, ball);
    removeGWindow(window, score);
    removeGWindow(window, paddle);
    
    //game over
    GLabel gameOver = newGLabel("GAME OVER");
    setFont(gameOver, "SansSerif-48");
    setColor(gameOver, "RED");
    double x = (getWidth(window) - getWidth(gameOver)) / 2;
    double y = (getHeight(window) - getHeight(gameOver)) / 2;
    setLocation(gameOver, x, y);
    add(window, gameOver);
    
    // wait for click before exiting
    waitForClick();
    pause(5000);

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
GRect initBricks(GWindow window)
{
    for(int i=0, x=0; i<COLS; i++)
    {
        for(int j=0, y=5; j<ROWS; j++)
        {
            GRect brick = newGRect(x+2, y+2, BRICKWIDTH, BRICKHEIGHT);
            setFilled(brick, true);
            
            switch (j)
            {
            case 0:
                setColor(brick, "BLACK");
                break;
            case 1:
                setColor(brick, "BLUE");
                break; 
            case 2:
                setColor(brick, "DARK_GRAY");
                break;
            case 3:
                setColor(brick, "BLUE");
                break;
            case 4:
                setColor(brick, "LIGHT_GRAY");
                break;
            }
            add(window, brick);
            y += 15;
        }
        x += 40;
    }
    return NULL;
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    GOval ball = newGOval((WIDTH/2-10), (HEIGHT/2), 20, 20);
    setFilled(ball, true);
    setColor(ball, "RED");
    add(window, ball);
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    // draw paddle centered at bottom of screen
    GRect paddle = newGRect((WIDTH/2-(PADDLEWIDTH/2)), PADDLEY, PADDLEWIDTH, PADDLEHEIGHT);
    setFilled(paddle, true);
    setColor(paddle, "BLUE");
    add(window, paddle);
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    GLabel score = newGLabel("0");
    setFont(score, "SansSerif-28");
    setColor(score, "RED");
    double x = (getWidth(window) - getWidth(score)) / 2;
    double y = (getHeight(window) - getHeight(score)) / 2;
    setLocation(score, x, y);
    add(window, score);
    return score;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
