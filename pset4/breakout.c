//
// breakout.c
//
// Computer Science 50
// Problem Set 4
//
// Masatoshi Nishiguchi
// nishiguchi.masa@gmail.com
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

// height of bricks (can be changed)
#define BRICK_H 20

// colors of bricks (can be changed)
#define COLOR0 "YELLOW"
#define COLOR1 "RED"
#define COLOR2 "ORANGE"
#define COLOR3 "MAGENTA" 
#define COLOR4 "CYAN"

/*-------color choices--------------*/
/* BLUE, CYAN, DARK_GRAY, GRAY,
   GREEN, LIGHT_GRAY, MAGENTA,
   ORANGE, PINK, RED, WHITE, YELLOW */
/*----------------------------------*/

// radius of ball in pixels
#define RADIUS 10

// dimension of paddle in pixels (can be changed)
#define PDL_W 50
#define PDL_H 10

// initial Y-coordinate of paddle (can be changed)
#define PDL_Y 550 

// lives
#define LIVES 3

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
void messageScoreboard(GWindow window, GLabel label, char* msg);
GObject detectCollision(GWindow window, GOval ball);


int main(void)
{
    /************************************************/    
    /* INITIALIZING                                 */
    /************************************************/    
        
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
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;

    // ball's velocity initially
    double velocity_y = 3.0;
    double velocity_x = velocity_y + 2 * drand48() - 1;
    
    /************************************************/    
    /* MAIN PART OF THE GAME                        */
    /************************************************/    

    // click to start
    waitForClick();
    
    //keep playing until game over
    while (lives > 0 && bricks > 0)
    {       
        updateScoreboard(window, label, points); 
        
        /*==========================*/
        /* behavior of the paddle   */
        /*==========================*/       
       
        // The paddle responds to mouse movements
        // and follows the cursor along its x-axis   
  
        GEvent event = getNextEvent(MOUSE_EVENT);

        if (event != NULL)
        {
            if (getEventType(event) == MOUSE_MOVED)
            {
                // next location of paddle
                double x = getX(event) - PDL_W / 2;
                
                // in case at left edge of the window
                if (x <= 0) 
                {
                    x = 0;
                }
                // in case at right edge of the window
                if (x + PDL_W >= WIDTH)
                {
                    x = WIDTH - PDL_W;
                }
                
                // update location of paddle
                setLocation(paddle, x, PDL_Y);
            }
        }

        /*======================*/
        /* behavior of the ball */
        /*======================*/ 
             
        //the ball bounces off when hitting any object
         
        move(ball, velocity_x, velocity_y);

        // bounce off top edge of window
        if (getY(ball) <= 0)
        {
            velocity_y = -velocity_y;
        }
        
        // bounce off left edge of window
        else if (getX(ball) <= 0)
        {
            velocity_x = -velocity_x;
        }
        
        // bounce off right edge of window
        else if (getX(ball) + (2 * RADIUS) >= WIDTH)
        {
            velocity_x = -velocity_x;
        } 
        pause(10);
        
        /*===========================*/
        /* detect ball's collision   */
        /*===========================*/ 
        GObject collided = detectCollision(window, ball);

        if (collided != NULL)
        {
            if (strcmp(getType(collided), "GRect") == 0)
            {
                // collision with the paddle
                if (collided == paddle)
                {
                    if (velocity_y > 0)
                    {
                        velocity_y = -velocity_y;
                    }         
                }
                
                // collision with bricks 
                else if (0 < getY(collided) && getY(collided) < 200)
                {
                    // ball bounces off brick
                    velocity_y = -velocity_y;
                    
                    // brick disappears
                    removeGWindow(window, collided);
                    
                    // update award points
                    points++;
                }
            }
        }

        /*==========================================*/
        /* win the game if all the bricks are struck */
        /*==========================================*/ 
        
        if (points == (ROWS * COLS))
        {
            char msg1[] = "Congratulations!!!";
            setColor(label, "Blue");           
            messageScoreboard(window, label, msg1);
            waitForClick();
    
            char msg2[50];
            sprintf(msg2, "Your score : %i", points);    
            messageScoreboard(window, label, msg2);
            
            waitForClick();
            closeGWindow(window);
            return 0;
        }
        
        
        /*==========================================*/
        /* lose life if the ball reaches the bottom */
        /*==========================================*/ 
        
        if (getY(ball) >= (HEIGHT - 20))
        {
            lives--;
            if (0 < lives && lives <= LIVES)
            {
                
                char msg[50];
                sprintf(msg, "Lives: %i / %i", lives, LIVES);
                setColor(label, "Red");    
                messageScoreboard(window, label, msg);
                waitForClick();
                
                // reset the ball position                 
                setLocation(ball, WIDTH / 2 - RADIUS, 300);
                setLocation(paddle, WIDTH / 2 - PDL_W / 2, PDL_Y);
                
                // re-shuffle the ball's x-axis velocity
                velocity_x = velocity_y + 2 * drand48() - 1;
                waitForClick();              
            }
            else if (lives == 0) break;   
        }
    }
    
    
    /*=============*/
    /* Game over   */
    /*=============*/
    
    char msg1[] = "--------GAME OVER--------";
    setColor(label, "Red");  
    messageScoreboard(window, label, msg1);
    waitForClick();
    
    char msg2[50];
    sprintf(msg2, "Your score : %i", points);
    setColor(label, "MAGENTA");    
    messageScoreboard(window, label, msg2);
    waitForClick();
    
    closeGWindow(window);
    return 0;
}

/****************************************************/
/* FUNCTIONS                                        */
/****************************************************/   

/*===========================================*/
/* Initializes window with a grid of bricks. */
/*===========================================*/
void initBricks(GWindow window)
{    
    // position of first brick
    double x = 2;
    double y = 50;
    
    // draw bricks
    for (int i = 0; i < ROWS; i++)
    {  
        for (int j = 0; j < COLS; j++)
        {
            GRect brick = newGRect(x, y, 35, BRICK_H);
            
            // change colors every row
            switch(i)
            {
                case 0: setColor(brick, COLOR0); break;
                case 1: setColor(brick, COLOR1); break;
                case 2: setColor(brick, COLOR2); break;
                case 3: setColor(brick, COLOR3); break;
                case 4: setColor(brick, COLOR4); break;
            }
            setFilled(brick, true);
            add(window, brick);
            
            // set x-coordinate of next brick
            x += 40;
        }
        // go back to first column
        x = 2;
        
        // set y-coordinate of next row 
        y += BRICK_H + 5; 
    }
}

/*=========================================*/
/* Instantiates ball in center of window   */
/*=========================================*/

GOval initBall(GWindow window)
{
    GOval circle = newGOval(WIDTH / 2 - RADIUS, 300, 
                            2 * RADIUS, 2 * RADIUS);
    setFilled(circle, true);
    setColor(circle, "BLACK");
    
    // put a ball on window
    add(window, circle);
    
    return circle;
}

/*=================================================*/
/* Instantiates paddle in bottom-middle of window. */
/*=================================================*/
GRect initPaddle(GWindow window)
{
    GRect rect = newGRect(WIDTH / 2 - PDL_W / 2, PDL_Y,    
                          PDL_W, PDL_H);
    setFilled(rect, true);
    setColor(rect, "BLUE");

    // put paddle on window
    add(window, rect);
    
    return rect;
}

/*=============================================================*/
/* Instantiates, configures, and returns label for scoreboard. */
/*=============================================================*/
 
GLabel initScoreboard(GWindow window)
{    
    GLabel label = newGLabel("The Breakout");
    
    setFont(label,"Arial-50");
    setColor(label, "Red");
    setFilled(label, true);
    add(window, label);
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
    
    return label;
}

/*============================================================*/
/* Updates scoreboard's label */
/*============================================================*/

void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "Your score : %i", points);
    setFont(label,"Arial-30");
    setColor(label, "Green");
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/*============================================================*/
/* Displays message on scoreboard */
/*============================================================*/

void messageScoreboard(GWindow window, GLabel label, char* msg)
{
    // update label
    char s[100];
    sprintf(s, "%s", msg);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/*=============================================================*/
/* Detects whether ball has collided with some object in window
   by checking the four corners of its bounding box (which are
   outside the ball's GOval, and so the ball can't collide with
   itself).  Returns object if so, else NULL.                  */
/*=============================================================*/

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
