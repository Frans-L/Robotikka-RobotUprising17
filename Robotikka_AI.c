
//Solves the challanges automatically
//	- Iron Forest
//	- the Maze
	
	
//Program starts from the "task main()"

//SolveForrest()
//	- Finds a good starting position
//	- Tries to find a wall where to hit
//	- Calibrates the position and the angle of the robot by using a wall
//	- Goes throguh the forest to a ramp
	
//FindLine()
//	- Tries to find the  ceiling of the maze
// 	- Tries to find a line

//LineFollow()
//	- Follows the blue line 
//	- When the robot is alinged correctly, increases the speed of the robot
//	- Sets a mine in the middle of the maze


int gray = 55; //line threshold
int CurveOffset = 300; //corner finding offset
bool curve, LineEnd = false;
int initB, initC, CurrentB, CurrentC, CurrentRawB, CurrentRawC;


//Finds the start position for the Iron Forrest
void forrestFindStartPosition(){
	
	OnFwd(OUT_A,15);
	
	OnFwd(OUT_BC, 50);
	Wait(500);
	
	
	//Detecting when the robot is in the starting position
	while(true){
	
		if(Sensor(IN_3) == true){
			Off(OUT_BC);
			Wait(100);
			break ;
		}
	
	}
	
	RotateMotorEx(OUT_BC,50,-40,0,true,true);
	Wait(100);
	
	RotateMotorEx(OUT_BC,50,390,100,true,true);//oikea90
	Wait(100);
	RotateMotor(OUT_BC,50,630);
	Wait(100);
	
	RotateMotorEx(OUT_BC,50,-310,-100,true,true); //oikea90
	Wait(200);

}


//Finds a wall 
void forrestFindWall(){
	OnFwd(OUT_BC,60);
	
	while(true){
		
		if(Sensor(IN_3) == true){
			Wait(1250);
			break ;
		}
		
	}
}


//Calibrate Angle and Position
void forrestCalibratePosition(){
	Off(OUT_BC);
	Wait(100);
	RotateMotorEx(OUT_BC,50,-200,0,true,true);
	Wait(100);
	RotateMotorEx(OUT_BC,50,-330,100,true,true);
	OnFwd(OUT_BC,-60);
	
	Wait(2000); //toisessa seinässä
	Off(OUT_BC);
}


//Exit to the ramp
void forrestExit(){
	Wait(100);
	RotateMotorEx(OUT_BC,50,1000,0,true,true);
	Wait(100);
	RotateMotorEx(OUT_BC,50,100,-100,true,true);
	Wait(100);
	RotateMotor(OUT_BC,50,420);
	Wait(100);
	RotateMotorEx(OUT_BC,50,230,100,true,true);
	Wait(100);
	RotateMotor(OUT_BC,50,2050);
	Wait(100);
	RotateMotorEx(OUT_BC,75,-110,-100,true,true);
	//RotateMotor(OUT_C,40,220);
	Wait(100);
	RotateMotor(OUT_BC,50,1000);
}


//SolveForrest()
//	- Finds a good starting position
//	- Tries to find a wall where to hit
//	- Calibrates the position and the angle of the robot by using a wall
//	- Goes throguh the forest to a ramp
void SolveForrest()
{
	
	forrestFindStartPosition();  //finds the start position
	forrestFindWall(); //finds a wall
	forrestCalibratePosition(); //calibrate positiona and angle with wall
	forrestExit(); //exit to the ramp
	
}


//FindLine()
//	- Tries to find the  ceiling of the maze
// 	- Tries to find a line
void FindLine()
{
	OnFwd(OUT_A,20);
	
	//initialize sensors
	SetSensorLight(IN_1);
	SetSensorLight(IN_4);
	SetSensorUltrasonic(S2);
	
	//finds the roof of the maze
	OnFwd(OUT_B,40);
	OnFwd(OUT_C,60);
	until(SensorUS(IN_2) < 30);
	
	//finds the line
	OnFwd(OUT_BC,30);
	until(Sensor(IN_1) < gray); //kunnes ollaan viivalla
	Off(OUT_BC);
	
	//finds the the right direction
	OnFwd(OUT_C,70);
	OnFwd(OUT_B,-40);
	until(Sensor(IN_4) < gray);
	Wait(10);
	 
}

//nothing anymore
/*task turn()
{
    curve=false;
    initB = MotorRotationCount(OUT_B);
    initC = MotorRotationCount(OUT_C);
    while(true)
    {
             CurrentRawB = MotorRotationCount(OUT_B);
             CurrentRawC = MotorRotationCount(OUT_C);
             CurrentB = abs(CurrentRawB - initB);
             CurrentC = abs(CurrentRawC - initC);
          if(abs(CurrentB - CurrentC) > CurveOffset)
          {
          curve=true;
          PlayTone(1000,100);
          until(curve==false);
          }
     }
}*/

//LineFollow()
//	- Follows the blue line 
//	- When the robot is alinged correctly, increases the speed of the robot
//	- Sets a mine in the middle of the maze
void LineFollow()
{
	long timer;
	long cubeTimer = CurrentTick();
	bool timerOn;
	bool dropStep1 = false;
	bool dropStep2 = false;
	bool spurtOnStep1 = false;
	
	bool spurtOn = true;
	
	OnFwd(OUT_A,10);
	
	//As long as there is line ahead
	while(LineEnd == false)
	{
	
		//Detects when the roof of the maze ends)
		if(SensorUS(IN_2) > 35 && timer == false)
		{
			timer = CurrentTick();
			timerOn = true;
		}
		
		//After maze and some seconds, stop following a line
		if(CurrentTick()-timer > 2000&& timerOn)
		{
			LineEnd=true;
		}
		
		NumOut(10,10,Sensor(IN_1));
		NumOut(10,40,MotorRotationCount(OUT_B));
		NumOut(10,50,MotorRotationCount(OUT_C));

		
		//Set MazeMine -> (1.) after dropping, lift the gripper
		if(dropStep1 == true && CurrentTick() - cubeTimer > 1500 && dropStep2 == false){
			OnFwd(OUT_A,75);
			dropStep2 = true;
			cubeTimer = CurrentTick();
		///Set MazeMine -> (2.) after dropping, release the gripper
		}else if(dropStep2 == true && CurrentTick() - cubeTimer > 1500 && spurtOnStep1 == false){
			OnFwd(OUT_A,30);
			spurtOnStep1 = true;
			cubeTimer = CurrentTick();
		
		/*//3. vapauta spurtti käyttöön
		}else if(spurtOnStep1 && CurrentTick() - cubeTimer > 10 * 1000){
			spurtOn = true;
		*/
		}
		
		
		//Detects if the robot is alinged -> Launch Warkspeed
		//Set MazeMine -> finds a good position to drop the cube
		if (Sensor(IN_4) < gray ) // && spurtOn)
		{
		
			//Set MazeMine -> if it's a time
			if(CurrentTick() - cubeTimer > 15*1000 && dropStep1 == false){
				OnFwd(OUT_A,-75);
				
				dropStep1 = true;
				cubeTimer = CurrentTick();
				
				spurtOn = false;
				
			}
			
			Wait(5);
			OnFwd(OUT_BC,60);
			
			//*if(spurtOn){
			
			//Warkspeed until not alinged
			until(Sensor(IN_4)>gray);	
			//}
			
			
		}
		//Otherwise follows a line slowly
		else
		{
			//If touching a line
			if(Sensor(IN_1) < gray)
			{
				OnFwd(OUT_B,70);
				OnFwd(OUT_C,-60);
				if(curve)
				{
					until(Sensor(IN_4) < gray);
					Wait(10);
					initB = MotorRotationCount(OUT_B);
					initC = MotorRotationCount(OUT_C);
					curve = false;
				}
			}
			
			//If not touching a line
			else
			{
				OnFwd(OUT_C,70);
				OnFwd(OUT_B,-40);
				if(curve)
				{
					until(Sensor(IN_4) < gray);
					Wait(10);
					initB = MotorRotationCount(OUT_B);
					initC = MotorRotationCount(OUT_C);
					curve=false;
				}
			}
		}
		
	}
}

//Automated hyper celebrations
//Duck is Love! Duck is Life!
void Celebrations()
{
	RotateMotorEx(OUT_BC,100,1000,0,true,true);
	OnFwd(OUT_B,100);
	OnRev(OUT_C,100);
	Wait(2500*3);
	
	Off(OUT_BC);
	ClearScreen();
	
	
	while(true){
		TextOut(10,50, "Duck is Love");
		TextOut(10,40, "Duck is Life!");
		TextOut(10,20, "Quaaak!");
		TextOut(10,10, "RobotUpRising!");
		
		Wait(1000);
		ClearScreen();
	}
	
}

//Solves the Iron Forrest Challenge
//and Maze automatically
task main()
{
	Wait(1000);
	SetSensorTouch(IN_3); //Set touch sensor On
	
	SolveForrest(); //Solves the Iron Forrest
	FindLine(); //Finds the maze and a line
	LineFollow(); //Follows the line
	Celebrations(); //Celebrates
}