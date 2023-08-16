#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include "utils.h"
#include "pieces.h"
#include "functionality.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace sf;
int main(){
    srand(time(0));
    RenderWindow window(VideoMode(320, 480), title);
    															//Load "frames.png","tiles.png" and "background.png" for Texture objects
    Texture obj1, obj2, obj3, obj4, obj5;
    obj1.loadFromFile("img/tiles.png");
    obj2.loadFromFile("img/b.jpg");
    obj3.loadFromFile("img/frame.png");
    obj4.loadFromFile("img/bomb5.png");                       //png for the bomb
    obj5.loadFromFile("img/b1.png");                          //blur backgroung

    Sprite sprite(obj1), background(obj2), frame(obj3), bomb(obj4), menu_back(obj5), brick(obj1);

    RectangleShape rectangle;                   //making rectangle for shadow
    rectangle.setSize(Vector2f (14,14) );
    rectangle.setOutlineColor(Color::White);
    rectangle.setOutlineThickness(1.2);
    rectangle.setFillColor( Color::Transparent);
   
    Music music;                                           //audio for game
    music.openFromFile("img/crystals1.ogg");
    music.play(); //plays music

    int alpha=0; 
    Font comic_sans;
    comic_sans.loadFromFile("img/cuphead.ttf");

    Text display_h, disp_level, display_h1, display_score, display_h2, display_sec, display_min, extra, display_h3, display_h4, display_h5, op1, op2, op3, op4;
    display_h.setFont(comic_sans);
    display_h.setString("Level:");
    display_h.setCharacterSize(15);
    disp_level.setFont(comic_sans);
    disp_level.setCharacterSize(15);
    display_h1.setFont(comic_sans);
    display_h1.setString("Score:");
    display_h1.setCharacterSize(15);
    display_score.setFont(comic_sans);
    display_score.setString(std::to_string(alpha));
    display_score.setCharacterSize(15);
    display_h2.setFont(comic_sans);
    display_h2.setString("Next Block");
    display_h2.setCharacterSize(15);
    display_sec.setFont(comic_sans);
    display_sec.setCharacterSize(15);
    display_min.setFont(comic_sans);
    display_min.setCharacterSize(15);
    extra.setFont(comic_sans);
    extra.setCharacterSize(15);
    extra.setString(":");
    display_h3.setFont(comic_sans);
    display_h3.setString("Elapsed Time:");
    display_h3.setCharacterSize(15);
    display_h4.setFont(comic_sans);
    display_h4.setString("CD Projeckt Red Presents");
    display_h4.setCharacterSize(20);
    display_h5.setFont(comic_sans);
    display_h5.setString("Retro Tetris");
    display_h5.setCharacterSize(25);
    op1.setFont(comic_sans);
    op1.setString("Press 1 to Start New Game");
    op1.setCharacterSize(15);
    op2.setFont(comic_sans);
    op2.setString("Press 2 to The Highest Scores");
    op2.setCharacterSize(15);
    op3.setFont(comic_sans);
    op3.setString("Press 3 for Help");
    op3.setCharacterSize(15);
    op4.setFont(comic_sans);
    op4.setString("Press 4 to Exit The Game");
    op4.setCharacterSize(15);

    Text help_h, info1, info2, ctrl1, ctrl2, ctrl3, ctrl4, ctrl5, ctrl6;
    help_h.setFont(comic_sans);
    help_h.setString("Game Help");
    help_h.setCharacterSize(20);
    info1.setFont(comic_sans);
    info1.setString("Game Walkthrough");
    info1.setCharacterSize(15);
    info2.setFont(comic_sans);
    info2.setString("Press Esc to go back to the main menu");
    info2.setCharacterSize(14);
    ctrl1.setFont(comic_sans);
    ctrl1.setString("Left and Right Arrow Keys Move the Block Horizontally");
    ctrl1.setCharacterSize(10);
    ctrl2.setFont(comic_sans);
    ctrl2.setString("Up Arrow Key Rotates the Block");
    ctrl2.setCharacterSize(10);
    ctrl3.setFont(comic_sans);
    ctrl3.setString("Down Arrow Key Increase the Speed of the Block");
    ctrl3.setCharacterSize(10);
    ctrl4.setFont(comic_sans);
    ctrl4.setString("Spacebar causes the Block to Move Downwards Instantly");
    ctrl4.setCharacterSize(10);
    ctrl5.setFont(comic_sans);
    ctrl5.setString("During Gameplay Press P for Pause Menu");
    ctrl5.setCharacterSize(10);
    ctrl6.setFont(comic_sans);
    ctrl6.setString("During Gameplay Press R for Resetting the Entire Game");
    ctrl6.setCharacterSize(10);

    Text score_h1, score_h2, score_h3, score_h4, score_h5, score_h6;
    score_h1.setFont(comic_sans);
    score_h1.setString("Tetris Hall of Famers");
    score_h1.setCharacterSize(20);
    score_h2.setFont(comic_sans);
    score_h2.setString("1. Mark Robers  1567");
    score_h2.setCharacterSize(15);
    score_h3.setFont(comic_sans);
    score_h3.setString("2. Ahmed Ryan  350");
    score_h3.setCharacterSize(15);
    score_h4.setFont(comic_sans);
    score_h4.setString("3. Arya Stark  289");
    score_h4.setCharacterSize(15);
    score_h5.setFont(comic_sans);
    score_h5.setString("4. Patrick Bateman  282");
    score_h5.setCharacterSize(15);
    score_h6.setFont(comic_sans);
    score_h6.setString("5. Zubair Adnan  60");
    score_h6.setCharacterSize(15);    

    Text pause_menu, p1, p2, p3, p4;
    pause_menu.setFont(comic_sans);
    pause_menu.setString("Pause Menu");
    pause_menu.setCharacterSize(20);
    p1.setFont(comic_sans);
    p1.setString("Press P to Resume game");
    p1.setCharacterSize(15);
    p2.setFont(comic_sans);
    p2.setString("Press R to Reset game");
    p2.setCharacterSize(15);
    p3.setFont(comic_sans);
    p3.setString("Press M to Go Back to Main Menu");
    p3.setCharacterSize(15);
    p4.setFont(comic_sans);
    p4.setString("Press E to Exit Game");
    p4.setCharacterSize(15);

    Text over_menu, total_time, o1, o2, o3;
    over_menu.setFont(comic_sans);
    over_menu.setString("Game Over");
    over_menu.setCharacterSize(20);
    total_time.setFont(comic_sans);
    total_time.setCharacterSize(15);
    o1.setFont(comic_sans);
    o1.setString("Press R to play game again");
    o1.setCharacterSize(15);    
    o2.setFont(comic_sans);
    o2.setString("Press M to go back to main menu");
    o2.setCharacterSize(15);
    o3.setFont(comic_sans);
    o3.setString("Press E to exit game");
    o3.setCharacterSize(15);

    int delta_x=0, colorNum, bombColor=rand()%7;
    float timer=0, delay=0.5, delay2=0.1, delay3=30.0;
    bool rotate=0, quick_drop1=0, quick_drop2=1, wait=0;
    bool reset = false, bomb_drop=false;
    int shadow[4][2]={}, next_block[4][2]={};
    int score=0, new_block_color= rand()%7 + 1, choice=4;
    int score_card[]={10,30,60,100}, level = 1;
    int bomb_p1[1][2]={}, row_limit=0;
    float level_delay = 0.5;
    float time;
    bool menu_display = true, game_start= false, help_display= false, score_display=false;
    bomb_maker(bomb_p1);
    first_block(next_block);
    intializer(point_1, next_block, shadow, new_block_color, colorNum, choice, row_limit);                //func to start the game with a random shape
    Clock clock, clock2, clock3, clock4;  					  	                //starts the clock
    float elapsed_time2=0, elapsed_time3=0;
    int elapsed_sec =0, elapsed_min =0, temp=0;
    int els=0, elm=0;
    //Time elapsed;
    while (window.isOpen()){

        while(menu_display)  //what to display as part of menu
        {
            window.clear(Color::Black);
            window.draw(menu_back);
            display_h4.setPosition(20,50);    //CD Projeckt Red
            display_h5.setPosition(75,90);    //Retro Tetris
            op1.setPosition(50,200);  //Press 1 to start new game
            op2.setPosition(50,230);  //Press 2 for the highest scores
            op3.setPosition(50,260);  //Press 3 for help
            op4.setPosition(50,290);  //Press 4 for exit
            window.draw(display_h4);
            window.draw(display_h5);
            window.draw(op1);
            window.draw(op2);
            window.draw(op3);
            window.draw(op4);
            window.display();
            Event menu;
            while (window.pollEvent(menu))
            {
                if (menu.type == Event::Closed)
                    window.close();
                if (menu.type == Event::KeyPressed)
                {
                    if (menu.key.code == Keyboard::Num1)
                    {
                        game_start = true;
                        menu_display = false;
                    }
                    else if(menu.key.code == Keyboard::Num2)
                    {
                        score_display = true;
                        menu_display = false;
                    }
                    else if(menu.key.code == Keyboard::Num3)
                    {
                        help_display = true;
                        menu_display = false;
                    }
                    else if(menu.key.code == Keyboard::Num4)
                        window.close();
                }
            }
        }

        while(score_display)    //what to display as part of high scorers
        {
            window.clear(Color::Black);
            window.draw(menu_back);
            display_h5.setPosition(70, 50);     //Retro Tetris
            score_h1.setPosition(50, 90);       //Tetris Hall of Famers
            score_h2.setPosition(30, 140);
            score_h3.setPosition(30, 170);
            score_h4.setPosition(30, 200);
            score_h5.setPosition(30, 230);
            score_h6.setPosition(30, 260);
            info2.setPosition(30,320);
            window.draw(display_h5);
            window.draw(score_h1);
            window.draw(score_h2);
            window.draw(score_h3);
            window.draw(score_h4);
            window.draw(score_h5);
            window.draw(score_h6);
            window.draw(info2);                //Press esc to go back to main menu
            window.display();
            Event help_menu;
            while(window.pollEvent(help_menu))
            {
                if(help_menu.type == Event::Closed)
                    window.close();
                if(help_menu.type == Event::KeyPressed)
                {
                    if(help_menu.key.code == Keyboard::Escape)
                    {
                        score_display = false;
                        menu_display = true;
                    }
                }
            }
        }

        while(help_display)   //what to display when help menu selected
        {   
            window.clear(Color::Black);
            window.draw(menu_back);
            display_h5.setPosition(70, 50);     //Retro Tetris
            help_h.setPosition(100,100);        //Game Help
            info1.setPosition(80,130);
            ctrl1.setPosition(10,170);
            ctrl2.setPosition(10, 190);
            ctrl3.setPosition(10, 210);
            ctrl4.setPosition(10, 230);
            ctrl5.setPosition(10, 250);
            ctrl6.setPosition(10, 270);
            info2.setPosition(20,300);
            window.draw(display_h5);
            window.draw(help_h);
            window.draw(info1);
            window.draw(ctrl1);
            window.draw(ctrl2);
            window.draw(ctrl3);
            window.draw(ctrl4);
            window.draw(ctrl5);
            window.draw(ctrl6);
            window.draw(info2);
            window.display();
            Event help_menu;
            while(window.pollEvent(help_menu))
            {
                if(help_menu.type == Event::Closed)
                    window.close();
                if(help_menu.type == Event::KeyPressed)
                {
                    if(help_menu.key.code == Keyboard::Escape)
                    {
                        help_display = false;
                        menu_display = true;
                    }
                }
            }
        }
        if(game_start)
        {
            reset = true;
        }
        while(game_start)
        {
            time = clock.getElapsedTime().asSeconds();              //gets the the elapsed time in secs
            clock.restart();  					                    //resets the clock for the next iteration
            timer+=time;      										//stores the total time elapsed 
		    if(elapsed_sec<0)                                       //reset the clock2 when entire game is reset
            {
                clock2.restart();
            }
            if(elapsed_time2<0)                                     //reset the clock3 when level is upgraded
            {
                clock3.restart();
            }
            if(elapsed_time3<0)                                     //reset the clock4 when game grid is shrinked
            {
                clock4.restart();
            }
            elapsed_sec = clock2.getElapsedTime().asSeconds();      
            elapsed_min = elapsed_sec / 60;                         //using data type manipluation to get seconds and minutes seperately
            elapsed_sec = elapsed_sec % 60;
            elapsed_time2 = clock3.getElapsedTime().asSeconds();     //get time for leveler
		    elapsed_time3 = clock4.getElapsedTime().asSeconds();     //get time for grid shrinker
            
            //initializing for the new iteration
		    delay = level_delay;
		
            //---Event Listening Part---//
            Event e;
            while (window.pollEvent(e))                         //Event is occurring - until the game is in running state
            {   
                if (e.type == Event::Closed)                    //If cross/close is clicked/pressed
                    window.close();                             //Opened window disposes
                if (e.type == Event::KeyPressed)                //If any other key (not cross) is pressed
                {
                    if (e.key.code == Keyboard::Up)             //Check if the other key pressed is UP key
                       rotate = true;                           //Rotation gets on
                    else if (e.key.code == Keyboard::Left)      //Check if the other key pressed is LEFT key
                       delta_x = -1;                            //Change in X-Axis - Negative
                    else if (e.key.code == Keyboard::Right)     //Check if the other key pressed is RIGHT key
                        delta_x = 1;
                    else if (e.key.code == Keyboard::Space)
                	    quick_drop1=1;                          //Change in X-Axis - Positive
                    else if (e.key.code == Keyboard::P)         //for pause menu
                        wait = !wait;   
                    else if(e.key.code == Keyboard::Down)       //reduce delay
                        delay=0.15;     
                    else if(e.key.code == Keyboard::R)          //reset the game
                    {    
                        reset = true;
                        wait = false;
                        temp = 0;
                        game_start = true;           //Resets the entire game
                        bomb_maker(bomb_p1);
                        first_block(next_block);
                        resetter(reset, point_1, next_block, shadow, alpha, colorNum, new_block_color, choice, 0, row_limit);
                        level = 1;
                        level_delay=0.5;
                        elapsed_sec = elapsed_time2 = elapsed_time3 = -1;

                    }
                    else if(e.key.code == Keyboard::M)          //go back to main menu
                    {
                        menu_display = true;
                        game_start = false;
                        wait = false;
                        temp = 0;           //Resets the entire game
                        resetter(reset, point_1, next_block, shadow, alpha, colorNum, new_block_color, choice, 0, row_limit);
                        level = 1;
                        level_delay=0.5;
                        elapsed_sec = elapsed_time2 = elapsed_time3 = -1;
                    }
                    else if(e.key.code == Keyboard::E)          //exit the game entirely
                        window.close();
                }
            }

            if(game_over())   //what to display when game over
            {
                if(temp==0)     //gets the last stored value of seconds timer before it is displayed
                {
                    els = elapsed_sec;
                    elm = elapsed_min;
                    ++temp;
                }
                window.clear(Color::Black);
                window.draw(menu_back);
                display_h5.setPosition(70,50);   //Retro Tetris
                window.draw(display_h5);
                over_menu.setPosition(80,90);   //Game over
                window.draw(over_menu);
                display_h1.setPosition(30,130);    //Score
                window.draw(display_h1);
                display_score.setString(std::to_string(alpha));   //displays the score
                display_score.setPosition(95,130);
                window.draw(display_score);
                total_time.setString("Total Time Played is: "+std::to_string(elm) + " : " + std::to_string(els));  //displays the total time game was played
                total_time.setPosition(30,170);
                window.draw(total_time);  
                o1.setPosition(30,210);  //Press R to play game again
                window.draw(o1);
                o2.setPosition(30,240);  //Press M to go back to main menu
                window.draw(o2);
                o3.setPosition(30,270);  //Press E to exit game
                window.draw(o3);
                //window.display();
            }
            else
            {
                if(wait)   //what to display when game is paused
                {
                    window.clear(Color::Black);
                    window.draw(menu_back); 
                    display_h5.setPosition(70,50);   //Retro Tetris
                    window.draw(display_h5);
                    pause_menu.setPosition(90,90);  //Pause Menu
                    window.draw(pause_menu);
                    display_h1.setPosition(30,130);    //Score
                    window.draw(display_h1);
                    display_score.setString(std::to_string(alpha));   //displays the score
                    display_score.setPosition(95,130);
                    window.draw(display_score);
                    display_h3.setPosition(30,160);   //Elapsed Time since beginning
                    window.draw(display_h3);
                    display_sec.setString(std::to_string(elapsed_sec));  //displays the time elapsed in sec
                    display_sec.setPosition(190,160);
                    window.draw(display_sec);
                    extra.setPosition(180, 160);  // :
                    window.draw(extra);
                    display_min.setString(std::to_string(elapsed_min)); //displays the time elapsed in min
                    display_min.setPosition(160, 160);
                    window.draw(display_min); 
                    p1.setPosition(30,200);    //Press P to resume game
                    window.draw(p1);
                    p2.setPosition(30,240);    //Press R to reset game
                    window.draw(p2);
                    p3.setPosition(30,280);    //Press M to go back to main menu
                    window.draw(p3);
                    p4.setPosition(30,320);    //Press E to exit game
                    window.draw(p4);
                }
        
                if(!wait && game_start)
                {
                    ///////////////////////////////////////////////
                    ///*** START CALLING YOUR FUNCTIONS HERE ***///
                    if(timer>delay)
                    {   
                        if(!bomb_drop) //when bomb is not dropping
                        {
                        score = fallingPiece(timer, delay, colorNum, new_block_color, shadow, next_block, bomb_drop, choice, row_limit);
                        if(score>-1)      
                            alpha += score_card[score];  //increase the total score by the score achieved during that instance        
                        }       
                    }
                    if(delta_x!= 0)  //for horizontal movement
                    {
                        hori_mvmt(delta_x, shadow, row_limit);
                    }
                    if(quick_drop1)  //for quick drop
                    {
                        nitro_drop(point_1, quick_drop1, row_limit);
                    }
                    if(rotate)  //for rotation
                    {
                        rotation(point_1, rotate, 1);
                        for(int i=0; i<4; ++i)   //updates the shadow of the new value
                        {
                            shadow[i][0] = point_1[i][0];
                            shadow[i][1] = point_1[i][1];
                        }
                        nitro_drop(shadow, quick_drop2, row_limit);   //updates the coordinates of shadow after the new orientation
                        quick_drop2 = 1;
                    }  
                    if(reset)   //for resetting game
                    {
                        bomb_maker(bomb_p1);
                        first_block(next_block);
                        resetter(reset, point_1, next_block, shadow, alpha, colorNum, new_block_color, choice, 0, row_limit);
                        level = 1;      //resets all variables to original values
                        level_delay=0.5;
                        elapsed_sec = elapsed_time2 = elapsed_time3 = -1;   //sets them to -1 so the relative clocks can be reset as well via conditional
                    }
                    if(elapsed_time2>=30.00)  //increases the level
                    {   
                        game_level(elapsed_time2, choice, level, level_delay);
                    }
                    if(elapsed_time3>=60.00)   //shrinks the grid
                    {
                        grid_shrinker(row_limit, elapsed_time3);
                    }
                    ///////////////////
                    //displaying the neccesary stuff during gameplay
                    window.clear(Color::Black);
                    window.draw(background);
                    display_h.setPosition(235,80);      //Level
                    window.draw(display_h);
                    disp_level.setString(std::to_string(level));   //level itself
                    disp_level.setPosition(235,105);
                    window.draw(disp_level);
                    display_h1.setPosition(235,130);  //Score: 
                    window.draw(display_h1);
                    display_score.setString(std::to_string(alpha));  //score itself
                    display_score.setPosition(235,155);
                    window.draw(display_score);
                    display_h2.setPosition(230,185);   //Next Block
                    window.draw(display_h2);
                    display_h3.setPosition(225,270);
                    display_h3.setCharacterSize(13);
                    window.draw(display_h3);           //Elapsed Time
                    display_sec.setString(std::to_string(elapsed_sec));
                    display_sec.setPosition(270,300);
                    window.draw(display_sec);           //seconds elapsed
                    extra.setPosition(260, 300);
                    window.draw(extra);                 // :
                    display_min.setString(std::to_string(elapsed_min));   //minutes elapsed
                    display_min.setPosition(240, 300);
                    window.draw(display_min);
                 
                    for (int i=0; i<4; i++)
                    {
                        sprite.setTextureRect(IntRect(new_block_color*18,0,18,18));
                        sprite.setPosition(next_block[i][0]*18 + 240,next_block[i][1]*18 + 215);  //draws the next block
                        window.draw(sprite);
                    }
                    for (int i=0; i<M; i++)
                    {
                        for (int j=0; j<N; j++){
                            if (gameGrid[i][j]==0)
                                continue;
                            sprite.setTextureRect(IntRect(gameGrid[i][j]*18,0,18,18));  //draws the filled game grid
                            sprite.setPosition(j*18,i*18);
                            sprite.move(31,28); //offset
                            window.draw(sprite);
                        }
                    }
                    if(row_limit>0)
                    {
                        for(int i=1; i<=row_limit; ++i )
                        { 
                            for(int j=0; j<N; ++j)
                            {
                                brick.setTextureRect(IntRect(18,0,18,18));   //draws the level that is bricked up and out of playable grid
                                brick.setPosition( j*18, (M-i)*18);
                                brick.move(31,28);
                                window.draw(brick);
                            }
                        }
                    }                    
                    if(!bomb_drop)
                    {
                        for (int i=0; i<4; i++){
                            sprite.setTextureRect(IntRect(colorNum*18,0,18,18));
                            sprite.setPosition(point_1[i][0]*18,point_1[i][1]*18);  //draws the tetris block itself
                            sprite.move(31,28);
                            window.draw(sprite);
                            rectangle.setPosition(shadow[i][0]*18, shadow[i][1]*18);  //draws the rectangle for the shadow
                            rectangle.move(31,28);
                            window.draw(rectangle);
                        }
                    }      
                    else
                    {
                        if(timer>delay2)  //timer is checked as per delay2 with respect to the bomb
                        {
                            int check = bomb_mover(bomb_p1, bomb_drop, bombColor, timer, row_limit);
                            if(check == 1)  //if 1 is returned means the bomb exploded and playable grid needs to be destroyed
                            {   int temp=-1;
                                first_block(next_block);
                                new_block_color = rand()%7 + 1;
                                resetter(reset, point_1, next_block, shadow, temp, colorNum, new_block_color, choice, 1, row_limit);
                                //level = 1;
                                //level_delay= 0.5;
                                elapsed_time2 = -1;
                            }
                            else if(check == 2)  //if 2 is returned means the bomb exploded and new tetris block to be initialized
                            {
                                intializer(point_1, next_block, shadow, new_block_color, colorNum, choice, row_limit);
                                colorNum=rand()%7+1;
                            }
                        }
                        bomb.setTextureRect(IntRect(bombColor*18,0,17,18));   //draws the bomb
                        bomb.setPosition(bomb_p1[0][0]*18,bomb_p1[0][1]*18);
                        bomb.move(31,28);
                        window.draw(bomb);
                    }
                    //---The Final on Which Everything is Drawn Over is Loaded---//
                    window.draw(frame);
                    //---The Window that now Contains the Frame is Displayed---//
                    //window.display();
                }
            }
            window.display();
        }
    }
    music.stop(); //stops music once window has been closed
    return 0;
}
