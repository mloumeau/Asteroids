/*************************************************************
 * File: game.cpp
 * Author: Br. Burton
 *
 * Description: Contains the implementations of the
 *  method bodies for the game class.
 *
 * Please DO NOT share this code with other students from
 *  other sections or other semesters. They may not receive
 *  the same code that you are receiving.
 *************************************************************/

#include "game.h"

using namespace std;

#define OFF_SCREEN_BORDER_AMOUNT 5


/***************************************
 * GAME CONSTRUCTOR
 ***************************************/
Game::Game(Point tl, Point br)
    : topLeft(tl), bottomRight(br)
{
    for (int i = 0; i < 5; i++)
    {
        createInitialRocks();
        createRock();
    }
}

/****************************************
 * GAME DESTRUCTOR
 ****************************************/
Game :: ~Game()
{
  
}


/**********************************************************
 * Function: getClosestDistance
 * Description: Determine how close these two objects will
 *   get in between the frames.
 **********************************************************/
float Game::getClosestDistance(const FlyingObject& obj1, const FlyingObject& obj2) const
{
    // find the maximum distance traveled
    float dMax = max(abs(obj1.getVelocity().getDx()), abs(obj1.getVelocity().getDy()));
    dMax = max(dMax, abs(obj2.getVelocity().getDx()));
    dMax = max(dMax, abs(obj2.getVelocity().getDy()));
    dMax = max(dMax, 0.1f); // when dx and dy are 0.0. Go through the loop once.

    float distMin = std::numeric_limits<float>::max();
    for (float i = 0.0; i <= dMax; i++)
    {
        Point point1(obj1.getPoint().getX() + (obj1.getVelocity().getDx() * i / dMax),
            obj1.getPoint().getY() + (obj1.getVelocity().getDy() * i / dMax));
        Point point2(obj2.getPoint().getX() + (obj2.getVelocity().getDx() * i / dMax),
            obj2.getPoint().getY() + (obj2.getVelocity().getDy() * i / dMax));

        float xDiff = point1.getX() - point2.getX();
        float yDiff = point1.getY() - point2.getY();

        float distSquared = (xDiff * xDiff) + (yDiff * yDiff);

        distMin = min(distMin, distSquared);
    }

    return sqrt(distMin);
}

/***************************************
 * GAME :: ADVANCE
 * advance the game one unit of time
 ***************************************/
void Game::advance()
{
    advanceBullets();
    advanceLevel();
    advanceRock();
    if (ship.isAlive())
    {
        // advance the ship
        ship.advance();
        handleCollisions();
    }
    cleanUpZombies();
}

/***************************************
 * GAME :: ADVANCE BULLETS
 * Go through each bullet and advance it.
 ***************************************/
void Game::advanceBullets()
{
    // Move each of the bullets forward if it is alive
    for (vector<Bullet*>::iterator bulletIt = bullets.begin(); bulletIt != bullets.end(); bulletIt++)
    {
        if (*bulletIt != NULL)
        {
            if ((*bulletIt)->isAlive())
            {
                (*bulletIt)->advance();
                (*bulletIt)->fourtyFrames();                          //dies after 40 frames

                if ((*bulletIt)->xValue() < -200)                     //wrapping code
                    (*bulletIt)->setXValue(200);
                if ((*bulletIt)->xValue() > 200)
                    (*bulletIt)->setXValue(-200);
                if ((*bulletIt)->yValue() < -200)
                    (*bulletIt)->setYValue(200);
                if ((*bulletIt)->yValue() > 200)
                    (*bulletIt)->setYValue(-200);                                   
            }
        }
    }
}


/****************************************************************************
* GAME :: ADVANCE LEVEL
* When all asteroids are dead, more asteroids appear
*****************************************************************************/
void Game::advanceLevel()
{
    int counter = rocks.size();
    Velocity newVelocity;
    newVelocity.setDy(1);
    newVelocity.setDx(1);

    for (int i = 0; i < rocks.size(); i++)
    {
        if (!rocks[i]->isAlive())
        {
            counter--;                         //when there are no more rocks, a new level starts
        }
    }
    if (counter == 0 && level < 5)
    {
        level++;
        rocks.clear();                          //clears the rocks vector everytime there's a new level
        bullets.clear();                        //clears the bullets vector everytime there's a new level

        for (int i = 0; i <= (1 + level); i++)
        {
            createInitialRocks();
            createRock();
        }
        counter = rocks.size();
    }    
}
/**************************************************************************
 * GAME :: ADVANCE ROCK
 *
 * 1. If there is no rock, create one with some probability
 * 2. If there is a rock, and it's alive, advance it
 * 3. Check if the rock has gone of the screen, and if so, "kill" it
 **************************************************************************/
void Game::advanceRock()
{
    for (vector <Rock*> ::iterator it = rocks.begin(); it != rocks.end(); ++it)
        if (*it != NULL)
        {
            (*it)->advance();

            if ((*it)->xValue() < -220)                    //wrapping code ( a little more leeway for rocks) 
                (*it)->setXValue(220);
            if ((*it)->xValue() > 220)
                (*it)->setXValue(-220);
            if ((*it)->yValue() < -220)
                (*it)->setYValue(220);
            if ((*it)->yValue() > 220)
                (*it)->setYValue(-220);

            if (level == 4 || level == 5)
            {
                (*it)->kill();                            //no rocks for the win screen
            }
        }



}

/************************************************************************************
* GAME :: CREATE INITIAL ROCKS
* This function creates the start-up rocks (5 large asteroids)
*************************************************************************************/
void Game::createInitialRocks()
{
    Rock* newRock = NULL;

        int randomNum = random(0, 3);
        Point newPoint;
        float newAngle = random(0, 360);

        if (randomNum == 0)                                   //random spawn points that won't kill the ship immediately
            newPoint = Point(-100, random(-200, 200));
        if (randomNum == 1)
            newPoint = Point(100, random(-200, 200));
        if (randomNum == 2)
            newPoint = Point(random(-200, 200), -100);
        if (randomNum == 3)
            newPoint = Point(random(-200, 200), 100);

        newRock = new BigRock(newPoint);
        newRock->fire(newPoint, newAngle);
        rocks.push_back(newRock);
}


/**************************************************************************
 * GAME :: CREATE ROCK
 * Create a rock of a random type according to the rules of the game.
 **************************************************************************/
void Game::createRock()
{
    Rock* newRock = NULL;

    int randomNum = random(0, 11);
    float newAngle = random(0, 360);
    Point newPoint;

    switch (randomNum)                                 //random spawns that won't kill the ship immediately
    {
        case 0:
        newPoint = Point(-200, random(-200, 200));
        newRock = new BigRock(newPoint);
        break;
        
        case 1:
        newPoint = Point(200, random(-200, 200));
        newRock = new BigRock(newPoint);
        break;

        case 2:
        newPoint = Point(random(-200, 200), -200);
        newRock = new BigRock(newPoint);
        break;

        case 3:
        newPoint = Point(random(-200, 200), 200);
        newRock = new BigRock(newPoint);
        break;

        case 4:
        newPoint = Point(200, random(-200, 200));
        newRock = new MediumRock(newPoint);
        break;
    
        case 5:
        newPoint = Point(-200, random(-200, 200));
        newRock = new MediumRock(newPoint);
        break;

        case 6:
        newPoint = Point(random(-200, 200), 200);
        newRock = new MediumRock(newPoint);
        break;

        case 7:
        newPoint = Point(random(-200, 200), -200);
        newRock = new MediumRock(newPoint);
        break;
    
        case 8:
        newPoint = Point(-200, random(-200, 200));
        newRock = new SmallRock(newPoint);
        break;
    
        case 9:
        newPoint = Point(200, random(-200, 200));
        newRock = new SmallRock(newPoint);
        break;
    
        case 10:
        newPoint = Point(random(-200, 200), -200);
        newRock = new SmallRock(newPoint);
        break;
    
        case 11:
        newPoint = Point(random(-200, 200), 200);
        newRock = new SmallRock(newPoint);
        break;    
    }
    newRock->fire(newPoint, newAngle);
    rocks.push_back(newRock);
    return;
}

/****************************************************************************
* GAME :: SPAWN ROCKS
* When rocks get hit, smaller rocks spawn from them
*****************************************************************************/
void Game::spawnRocks(char type, Point point, Velocity velocity, float angle)
{
    if (type == 'B')
    {
        MediumRock* medRock = new MediumRock(point, velocity, random(0, 360), 'M');
        MediumRock* medRock1 = new MediumRock(point, velocity, random(0, 360), 'M');
        SmallRock* smallRock = new SmallRock(point, velocity, random(0, 360), 'S');

        medRock->getVelocity().setDy(velocity.getDy() + 1);
        medRock->getVelocity().setDy(velocity.getDy() - 1);
        smallRock->getVelocity().setDx(velocity.getDx() + 2);

        medRock->fire(point, random(0, 360));
        medRock1->fire(point, random(0, 360));
        smallRock->fire(point, random(0, 360));

        rocks.push_back(medRock);
        rocks.push_back(medRock1);
        rocks.push_back(smallRock);
    }
    if (type == 'M')
    {
        SmallRock* smallRock1 = new SmallRock(point, velocity, random(0, 360), 'S');
        SmallRock* smallRock2 = new SmallRock(point, velocity, random(0, 360), 'S');

        smallRock1->getVelocity().setDx(velocity.getDx() + 3);
        smallRock2->getVelocity().setDx(velocity.getDx() - 3);

        smallRock1->fire(point, random(0, 360));
        smallRock2->fire(point, random(0, 360));

        rocks.push_back(smallRock1);
        rocks.push_back(smallRock2);
    }
}


/**************************************************************************
 * GAME :: IS ON SCREEN
 * Determines if a given point is on the screen.
 **************************************************************************/
bool Game::isOnScreen(const Point& point)
{
    return (point.getX() >= topLeft.getX() - OFF_SCREEN_BORDER_AMOUNT
        && point.getX() <= bottomRight.getX() + OFF_SCREEN_BORDER_AMOUNT
        && point.getY() >= bottomRight.getY() - OFF_SCREEN_BORDER_AMOUNT
        && point.getY() <= topLeft.getY() + OFF_SCREEN_BORDER_AMOUNT);
}

/**************************************************************************
 * GAME :: HANDLE COLLISIONS
 * Check for a collision between a rock and a bullet.
 **************************************************************************/
void Game::handleCollisions()
{
    for (int i = 0; i < bullets.size(); i++)
    {
        if (bullets[i]->isAlive())
        {
            for (int j = 0; j < rocks.size(); j++)
            {
                if (rocks[j]->isAlive())
                {
                    if (rocks[j] != NULL)
                    {
                        if (getClosestDistance(*bullets[i], *rocks[j]) <= rocks[j]->getRadius())
                        {
                            spawnRocks(rocks[j]->getType(), rocks[j]->getPoint(), rocks[j]->getVelocity(), rocks[j]->getVelocity().getAngle());
                            bullets[i]->kill();
                            rocks[j]->kill();
                        }
                    }
                }
            }
        }
    }
    if (ship.isAlive())
    {
        for (int i = 0; i < rocks.size(); i++)
        {
            if (getClosestDistance(ship, *rocks[i]) <= ship.getRadius() + rocks[i]->getRadius())
            {
                spawnRocks(rocks[i]->getType(), rocks[i]->getPoint(), rocks[i]->getVelocity(), rocks[i]->getVelocity().getAngle());
                rocks[i]->kill();
                if (ship.getLives() > 0)
                {
                    ship.setLives(ship.getLives() - 1);
                    ship.kill();
                }
            }
        }
    }
}

/*************************************************************************************
* GAME :: IS COLLISION
* function returns a bool to see if it is a collision or not
***************************************************************************************/
bool Game::isCollision(FlyingObject& ob1, FlyingObject& ob2)
{
    bool collision = false;

    if (ob1.isAlive() && ob2.isAlive())
    {
        float diff = getClosestDistance(ob1, ob2);
        float tooClose = ob1.getRadius() + ob2.getRadius();

        if (diff < tooClose)
            collision = true;
    }
    return collision;
}

/**************************************************************************
 * GAME :: CLEAN UP ZOMBIES
 * Remove any dead objects (take bullets out of the list, deallocate bird)
 **************************************************************************/
void Game::cleanUpZombies()
{

    Point newPoint;
    newPoint.setX(300);
    newPoint.setY(300);
    // check for dead rock       
    for (vector<Rock*>::iterator rockIt = rocks.begin(); rockIt != rocks.end(); rockIt++)
    {
        Rock* pRock = *rockIt;
        if (!pRock->isAlive() && pRock != NULL)
        {
            pRock->setPoint(newPoint);
            //delete pRock;
            //pRock = NULL;
        }
    }
    // Look for dead bullets
    Bullet* pBullet = NULL;
    for (int i = 0; i < bullets.size(); i++)
    {
        pBullet = bullets[i];
        if (!bullets[i]->isAlive() /*&& bullets[i] != NULL*/)
        {
           // delete pBullet;
           // pBullet = NULL;
        }

    }
}
    


/***************************************
 * GAME :: HANDLE INPUT
 * accept input from the user
 ***************************************/
void Game::handleInput(const Interface& ui)
{
    if (ship.isAlive())
    {

        if (ui.isDown())
        {
            ship.applyThrustBottom();
        }

        if (ui.isLeft())
        {
            ship.applyThrustLeft();
        }

        if (ui.isRight())
        {
            ship.applyThrustRight();
        }
        if (ui.isUp())
        {
            ship.applyThrustTop();
        }
    }
    // Check for "Spacebar
    if (ui.isSpace() && ship.isAlive())
    {
        Bullet* newBullet = NULL;
        newBullet = new Bullet();
        newBullet->fire(ship.getPoint(), (ship.getAngle() - 90));
        bullets.push_back(newBullet);
        
        if (level == 5)
        {
            if (ui.isSpace() && ship.isAlive())        //spacebar will start chaos mode
            {
                level++;
                startChaosMode();
            }
        }
    }
    if (ui.isSpace() && !ship.isAlive() && ship.getLives() > 0)
    {
        Point newPoint;
        newPoint.setX(0);
        newPoint.setY(0);

        Velocity newVelocity;
        newVelocity.setDx(0);
        newVelocity.setDy(0);

        ship.setVelocity(newVelocity);
        ship.setPoint(newPoint);
        ship.setAlive(true);
        ship.draw();
    }

}

/*****************************************************
* GAME :: START CHAOS MODE
* Once the user has won, they will have the option for
* chaos mode (nearly unbeatable)
********************************************************/
void Game::startChaosMode()
{
    Velocity newVelocity;
    newVelocity.setDy(random(8, 12));            //fast rocks
    newVelocity.setDx(random(8, 12));

    float newAngle;

    for (int i = 0; i < 25; i++)                  //a lot of rocks
    {
        createRock();
    }
    for (int i = 0; i < rocks.size(); i++)
    {
        rocks[i]->setVelocity(newVelocity);
    }
    for (int i = 0; i < rocks.size(); i++)
    {
        newAngle = random(0, 360);
        rocks[i]->fire(rocks[i]->getPoint(), newAngle);
    }
}

/*********************************************
 * GAME :: DRAW
 * Draw everything on the screen
 *********************************************/
void Game::draw(const Interface& ui)
{
    if (ship.isAlive())
       ship.draw();

    if (!ship.isAlive() && ship.getLives() > 0)
    {
        Point textLevel;
        textLevel.setX(-100);
        textLevel.setY(0);

        const char* text = "PRESS SPACE TO RESPAWN SHIP!";

        drawText(textLevel, text);
    }

    // draw the rock
    for (int i = 0; i < rocks.size(); i++)
    {
        if (rocks[i] != NULL && rocks[i]->isAlive())
        {
           rocks[i]->draw();
        }
    }
    
    // draw the bullets, if they are alive
    for (int i = 0; i < bullets.size(); i++)
    {
        if (bullets[i] != NULL && bullets[i]->isAlive())
            bullets[i]->draw();       
    }

    if (ship.getLives() == 0)
    {
        const char* text = "LIVES: 0";
        Point levelText;
        levelText.setX(bottomRight.getX() - 55);
        levelText.setY(topLeft.getY() - 20);

        drawText(levelText, text);
    }

    if (ship.getLives() == 1)
    {
        const char* text = "LIVES: 1";
        Point levelText;
        levelText.setX(bottomRight.getX() - 55);
        levelText.setY(topLeft.getY() - 20);

        drawText(levelText, text);
    }

    if (ship.getLives() == 2)
    {
        const char* text = "LIVES: 2";
        Point levelText;
        levelText.setX(bottomRight.getX() - 55);
        levelText.setY(topLeft.getY() - 20);

        drawText(levelText, text);
    }

    if (ship.getLives() == 3)
    {
        const char* text = "LIVES: 3";
        Point levelText;
        levelText.setX(bottomRight.getX() - 55);
        levelText.setY(topLeft.getY() - 20);

        drawText(levelText, text);
    }

    if (level == 1)
    {
        const char* text = "LEVEL 1";
        Point levelText;
        levelText.setX(topLeft.getX() + 10);
        levelText.setY(topLeft.getY() - 20);

        drawText(levelText, text);
    }
    if (level == 2)
    {
        const char* text = "LEVEL 2";
        Point levelText;
        levelText.setX(topLeft.getX() + 10);
        levelText.setY(topLeft.getY() - 20);

        drawText(levelText, text);
    }
    if (level == 3)
    {
        const char* text = "LEVEL 3";
        Point levelText;
        levelText.setX(topLeft.getX() + 10);
        levelText.setY(topLeft.getY() - 20);

        drawText(levelText, text);
    }
     if (level == 4 || level == 5)           //win screen
    {

        Point levelText;
        levelText.setX(-35);
        levelText.setY(0);

        const char* text = "YOU WIN!";
        drawText(levelText, text);

        Point levelText1;
        levelText1.setX(-100);
        levelText1.setY(-15);

        const char* text1 = "PRESS SPACE FOR CHAOS MODE!";
        drawText(levelText1, text1);

        cout << level << endl;
    }

     if (level == 6)                                //chaos mode
     {
         const char* text = "CHAOS ! ! !";
         Point levelText;
         levelText.setX(topLeft.getX() + 10);
         levelText.setY(topLeft.getY() - 20);

         drawText(levelText, text);
     }
     if (level == 7)                              //ultimate win screen on the off chance someone beats chaos mode
     {
         const char* text = "CONGRATULATIONS !";
         Point levelText;
         for (int i = 0; i < 4; i++)
         {
             for (int j = 0; j < 35; j++)
             {
                 levelText.setX(topLeft.getX() + (i * 140));
                 levelText.setY(topLeft.getY() - (j * 12));

                 drawText(levelText, text);
             }
         }
     }

    if (!ship.isAlive() && ship.getLives() == 0)
    {
        const char* text = "GAME OVER";
        Point levelText;
        levelText.setX(-30);
        levelText.setY(0);

        drawText(levelText, text);
    }
}