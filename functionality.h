// ;
void first_block(int next_block[][2]);
void nitro_drop(int point_1[][2], bool& quick_drop, int row_limit);;
void intializer(int point_1[][2], int next_block[][2], int shadow[][2], int& next_block_color, int& colorNum, int choice, int row_limit);
void hori_mvmt(int& delta, int shadow[][2], int row_limit);
void rotation(int point_1[][2], bool& rotate, int n);
int row_deleter(int row);
void resetter(bool& reset, int point_1[][2], int next_block[][2], int shadow[][2], int& score, int& colorNum, int& new_block_color, int& choice, int alpha, int& row_limit);
void bomb_maker(int bomb_loc[][2]);
int bomb_mover(int bomb_p1[][2],bool& bomb_drop, int& bombColor, float& timer, int row_limit);
bool bomb_anomaly(int bomb_p1[][2], int row_limit);
bool bomb_destroyer(int bomb_p2[][2], int bombColor, int row_limit);
void bomb_clearer(int row, int column, int n, int row_limit);
void grid_shrinker(int& row_limit, float& elapsed_time3);
bool game_over();
int fallingPiece(float& timer, float& delay, int& colorNum, int& next_block_color, int shadow[][2], int next_block[][2], bool& bomb_drop, int choice, int row_limit)
{
    int score=-1;
    if (timer>delay)
    { 
      for (int i=0;i<4;i++)
      {
      	point_2[i][0]=point_1[i][0];
        point_2[i][1]=point_1[i][1];
        point_1[i][1]+=1;                   //How much units downward
    	}
      if (!anomaly(row_limit))  //anomaly to check the block is at its final possible place or not
      {
      	for(int i=0; i<4;++i)
        {
        	gameGrid[point_2[i][1]][point_2[i][0]] = colorNum;
        }
        score = row_deleter(19 - row_limit);
        colorNum=rand()%7+1;
        if(colorNum == 2 || colorNum == 4)
        {
          bomb_drop = true;
        }
        else
        {
          intializer( point_1, next_block, shadow, next_block_color, colorNum, choice, row_limit);
        }
      }
      timer=0;
    }
  return score;
}

/////////////////////////////////////////////
///*** FUNCTIONS START HERE ***///
void first_block(int next_block[][2])    //function to initialize the next block
{
  int n = rand()%4;                      //only selects the shape from the first four choice
  for(int i=0; i<4; ++i)
  {
    next_block[i][0] = BLOCKS[n][i] / 2;
    next_block[i][1] = BLOCKS[n][i] % 2;
  }
}
void nitro_drop(int point_1[][2], bool& quick_drop, int row_limit)       //function to quick drop
{                                                                         
	if(quick_drop)
  { 
    int point_2[4][2]={};                          
    for(int i=0; i<4; ++i)
    {
      point_2[i][1] = 1 + point_1[i][1];            //temporary array to store the next location, y axis offset
      point_2[i][0] = point_1[i][0];                //x axis offset remains the same
      if(gameGrid[point_2[i][1]][point_2[i][0]] || point_2[i][1]>=(M-row_limit) )    //checks if the next location is free and in the row limit
      {
        return;    //next location is already filled or out of row limit, the recursive function rolls back, centennail condition
      }
    }
    nitro_drop(point_2, quick_drop, row_limit);     //recursive calling
    for(int i=0; i<4; ++i)
    {
      point_1[i][1] = point_2[i][1];                //updates the point 1 of the block wiht the max possibile y offset after repeated checks
    }
    quick_drop = false;                             
  }
}
void intializer(int point_1[][2], int next_block[][2], int shadow[][2], int& next_block_color, int& colorNum, int choice, int row_limit)   //func to start the game with a random shape
{
	int n=rand()%choice;                   //initially only first 4 shapes open later ob 7 become available
  colorNum = next_block_color;           //color of the current block
  next_block_color = rand()%7 + 1;       //color for the upcoming block
	for(int i=0; i<4; i++)                   
	{
		point_1[i][0] = next_block[i][0];    //initializes the tetris being displayed at the moment 
  	point_1[i][1] = next_block[i][1];
    shadow[i][0] = point_1[i][0];        //shadow has the same shape as the tetris being dropped
    shadow[i][1] = point_1[i][1];
    next_block[i][0] = BLOCKS[n][i] / 2;    //next block stores the next shape of the upcoming tetris block
    next_block[i][1] = BLOCKS[n][i] % 2;
  }
	int x= rand()%7;
	for(int i=0; i<4; ++i)                 //random x axis offset
	{
  	point_1[i][0]+=x;
    shadow[i][0]+=x;
	}
  bool quick_drop=1;       
  nitro_drop(shadow, quick_drop, row_limit); //concept of quick drop utilized for finding the position of the shadow as the shadow must have max y axis offset
}
void rotation(int point_1[][2], bool& rotate, int n)       //function for rotation
{
	if(rotate)
	{
		int pivot_x = point_1[n][0];       //sets the x and y pivots as per the value in the selected index of the point 
		int pivot_y = point_1[n][1]; 
		int temp[4][2]={};      
		int org[4][2]={};
		for(int i=0; i<4; ++i)
		{
			org[i][0] = point_1[i][0];       //temp array to check the feasibility of rotation
			org[i][1] = point_1[i][1];	
		}
		for(int i=0; i<4; ++i)
		{
			org[i][0] = org[i][0] - pivot_x;    //converts the coordinates of the block into a new coordinate system as per the selected pivots
			org[i][1] = org[i][1] - pivot_y;
			temp[i][0]=org[i][0];               //interchanges the x and y coordinates of the block
			temp[i][1]=org[i][1];
			org[i][0]= -temp[i][1]; 
			org[i][1]=temp[i][0];
		  org[i][0] = org[i][0] + pivot_x;       //converts the coordinates back into the original coordinate system as per the selected pivots
			org[i][1] = org[i][1] + pivot_y;
		}
		for(int i=0; i<4; ++i)
		{
			if(org[i][0]>=N  || org[i][0]<0 || gameGrid[org[i][1]][org[i][0]]!=0) //if any of the new coord is out of bound or interferes with an already set block 
			{
			 if(n<3)  //centennial conditon can't have pivot point greater then 4, since the block array has max index till 3
			  {
					rotation(point_1, rotate, n+1);   //recursive calling, moves the pivot point by 1
				}
        rotate = false;   //incase the pivot is out of bound and the new coords are out of bound, doesnt update the point_1 of the tetris block 
        return;
			}
		}
    for(int i=0; i<4; ++i)     //if the new coord are in bound, updates the point_1 of the tetris blocks
		{
			point_1[i][0] = org[i][0];
			point_1[i][1] = org[i][1];	
		}
		rotate = false;
	}
}
void hori_mvmt( int& delta, int shadow[][2], int row_limit)    //function for horizontal movement
{ 
  bool mvmt = true;   //suppose movement is possible
	if(delta==1)        //check for left or right movement
	{
    for(int i=0; i<4; ++i)
    {
      if(point_1[i][0]>=N-1 || gameGrid[point_1[i][1]][point_1[i][0]+1] !=0 )   //checks if the movement is possible
      {
        mvmt = false;      //if the tetris block is at edge or if the next space is already filled then block doesnt move
      }
    }
    if(mvmt)   //if movement possible updates the x coordinates of the entire tetris block
		{
			for(int i=0; i<4; ++i)
			{
				point_1[i][0]+=1;
        shadow[i][0]+=1;
        shadow[i][1]=point_1[i][1];         //upadting the coordinates of the shadow as per the movement of the tetris block
			}
      bool quick_drop=1;
      nitro_drop(shadow, quick_drop, row_limit);     //calling nitro_drop func to update the coordinates of the new shadow
		}
	}
	else if(delta==-1)
	{
    for(int i=0; i<4; ++i)
    {
      if(point_1[i][0]<=0 || gameGrid[point_1[i][1]][point_1[i][0]-1]!=0)
      {
        mvmt = false;   //again if the tetris block is at edge or if the next space is already filled then block doesnt move
      }
    }
    if(mvmt)
		{
			for(int i=0; i<4; ++i)
			{
				point_1[i][0]-=1;
        shadow[i][0]-=1;
        shadow[i][1]=point_1[i][1];
			}
      bool quick_drop=1;
      nitro_drop(shadow, quick_drop, row_limit);    //calling nitro_drop func to update the coordinates of the new shadow
		}
	}
  delta =0;
}
int row_deleter(int row)   //function for row deletion and point scoring due to row deletion
{                    //function returns int value which is utilized to get the correct score
  int score=-1;      //since it is an int function it must retrun something, incase the score is not chnaged it returns -1, signifying no change in overall score
	if(row==0)         //centennial condition, if the function reaches 0th row, its rolls back
  {
    return score;          
  }
  else
  {
    bool flag = true;       //suppose the entire row is filled
    for(int i=0; i<10; ++i)   
    {
      if(gameGrid[row][i]==0)  //if any entry is zero in game grid of that specific, it means the entire row is not filled, updates the boolean flag
      {
        flag=false;
        break;
      }
    }
    score = row_deleter(row-1);   //recursive calling, checks for the above row 
    if(flag)    //entire row filled
    {
      for(; row>0; --row)
      {
        for(int i=0; i<10; ++i)
        {
        gameGrid[row][i] = gameGrid[row-1][i];    //replaces the current row, with the row above it 
        }      
      }
      if(score<=3)   //incase score is 3 or less
      {
        return score+1;  //adds 1 to score and returns it
      }
      else    //incase score is 4, returns as it is, since max score for simultaneous destruction is 4
      {
        return score;
      }
    }
  }
  return score;
}
void resetter(bool& reset, int point_1[][2], int next_block[][2], int shadow[][2], int& score, int& colorNum, int& new_block_color, int& choice, int alpha, int& row_limit)
{    //function to completely reset the game
  reset = false;  
  choice = 4;   //reset the number of shapes avaialble to the initial avaible of 4
  /*
  alpha is a temp 
  the reset function is utilized for both resetting the geame but also to clear the grid when the bomb explodes
  in order to differentiate between the two purposes, a temp value is sent as per the place where the reset function is being called
  */
  if(alpha==0)   //alpha is zero means to clean the entire game grid
  {
    for(int i=0; i<M; ++i)
    {
      for(int j=0; j<N; ++j)
      {
        gameGrid[i][j] = {0};
      }
    }
    row_limit = 0;
  }     //alpha not zero, only clear the specific area 
  else
  {
    for(int i=0; i<(M-row_limit); ++i)   //row_limit limits the playable grid, thus the game grid is reset accordingly
    {
      for(int j=0; j<N; ++j)
      {
        gameGrid[i][j] = {0};
      }
    }
  }  
  intializer(point_1, next_block, shadow, new_block_color, colorNum, choice, row_limit);  //initializer function called to create a new tetris block after the game grid is cleared
  /* 
  again if the purpose of reset it to restart the entire game, any value other than -1 is passed to clear the score as well
  if reset is used after bomb explosion, -1 is passed into the reset function to prevent the score from being cleared
  */
  if(score!=-1)
  {
    score = 0;
  }
  colorNum=rand()%7+1;   //colorNum for next block
}
void bomb_maker(int bomb_loc[][2])  //function for random bomb spawn location
{
  int x= rand()%7;    //spawns the bomb at randon position     
  bomb_loc[0][0]=x;
  bomb_loc[0][1]=0;
}
int bomb_mover(int bomb_p1[][2],bool& bomb_drop, int& bombColor, float& timer, int row_limit)  //function to move the bomb
{                                                                                              //similar in working to the fallingPiece function
  int bomb_p2[1][2]={};   //temp array
  bomb_p2[0][0]= bomb_p1[0][0];
  bomb_p2[0][1]= bomb_p1[0][1];
  bomb_p1[0][1]+=1;   //calculates the next supposed location of the bomb
  if(bomb_anomaly(bomb_p1, row_limit))    
  {
    bomb_drop= false;     
    bomb_maker(bomb_p1);   //function called to initliaze bomb coordinates for the next run
    if(bomb_destroyer(bomb_p2, bombColor, row_limit))  //function utlized to see how should the bomb expload
    {
      bombColor=rand()%7;   //bomb color for the next vomb
      return 1;          //if color match return 1, this will feed into the reset function as the playable game grid shall be cleared
    }
    else
    {
      bombColor=rand()%7;    
      return 2;          //if the color do not match
    }
  }
  timer=0;
  return 0;
}
bool bomb_anomaly(int bomb_p1[][2], int row_limit)  //function acts similar to the anomaly incldued in the skeleton code
{
  if(gameGrid[bomb_p1[0][1]][bomb_p1[0][0]] || bomb_p1[0][1]==(M-row_limit) ) //checks if the next position is already filled or crosses into the non-playable game grid
    return 1;   
  else
    return 0;
}
bool bomb_destroyer(int bomb_p2[][2], int bombColor, int row_limit)   //function to see how the bomb explosion occurs
{  
  if(bomb_p2[0][1]== ((M-1)-row_limit))    
  { /*centennial condition, function rolls back if the bomb is at the boundary of the playable game grid i.e.,     
    is at the extreme bottom or the rows beneath are frozen */
    return false;
  }  
  else
  {
    int color_value = gameGrid[bomb_p2[0][1]+1][bomb_p2[0][0]];  //finds the color of the block right beneath it
    if(color_value == (bombColor+1))    //if the color of the bomb and block match
    {
      return true;                            
    }
    else   //if color not match
    {
      bomb_clearer(bomb_p2[0][1], bomb_p2[0][0], 0, row_limit);   //function called to clear off the four blocks beneath when color do not match
      return false;
    }
  }
  return false;
}
void bomb_clearer(int row, int column, int n, int row_limit)   //function to clear off the four blocks when bomb and block color do not match
{
  if(row>=(19-row_limit) || n>=2)   //centennial condition, the function rolls back if the row is at the boundary of the playable game grid 
  {                                 //or if the function is being called for the third time, since only two rows need to cleaned off
    return;
  }
  else if(column>0)      
  {
    
    gameGrid[row+1][column-1]=0;     //clears the two blocks below the bomb
    gameGrid[row+1][column]=0;        
    
    for(int i=row+1; i>0; --i)
    {
      gameGrid[i][column]= gameGrid[i-1][column];    //fills the cleared off blocks with blocks over them
      gameGrid[i][column-1]= gameGrid[i-1][column-1];
    }
    bomb_clearer(row+1, column, n+1, row_limit);   //function recursive calling for the second row
  }
  else    //if the bomb is at extreme left of the game gird
  {       //works same as the above, only the explosion area differ to accomodate the position of the bomb correctly
    gameGrid[row+1][column]=0;
    gameGrid[row+1][column+1]=0;
    for(int i=row+1; i>0; --i)
    {
      gameGrid[i][column]= gameGrid[i-1][column];
      gameGrid[i][column+1]= gameGrid[i-1][column+1];
    }
    bomb_clearer(row+1, column, n+1, row_limit);   //function recursive calling for the second row
  }
}
void game_level(float& elapsed_time2, int& choice, int& level, float& level_delay)   //function to change game levels
{
  elapsed_time2 = -1;  //updates the elapsed_time2 so that the clock for it can be reset with help of conditional
  choice = 7;          //opnes up the possible number of chiices
  ++level;             //increase the level
  if(level%2==0 && level!=2)  //after every two levels, the block delay is reduced or the speed is increase
  {
    level_delay-=0.05;
  }
}
void grid_shrinker(int& row_limit, float& elapsed_time3)   //function to reduce the size of the playable game grid
{
  ++row_limit;        //increase the row_limit which allows to shrink the playable game grid
  elapsed_time3 = -1;   //updates the elapsed_time3 so that the clock for it can be reset with help of conditional
}
bool game_over()      //function to check if the top most row is filled or not
{
  for(int i=0; i<N; ++i)   
    if(gameGrid[0][i] != 0)    //returns 1 is 0th row or the top most row is filled at any point
    {
      return 1;
    } 
  return 0;
}
///*** FUNCTIONS END HERE ***///
/////////////////////////////////////
