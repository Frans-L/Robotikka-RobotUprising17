
//Bluetooth Controller for Rotikka robot
//Controls the motors of the robot
//When the "Duck" -button of the controller is pressed
//	-> Starts the Rotikka_AI
//	-> Disconnects bluetooth connection
//	-> Starts QUAACKing


int Between(int value, int min, int max){
	if(value < min){
		return min;
	}else if (value > max){
		return max;
	}
	return value;
}

int GetDirection(int value){
	return value/abs(value);
}
 
void SendMotorRotation(int con, int port, int speed, int tacholimit = 0 , int turnpct = 0){
	
	speed = Between(speed,-100,100);
	RemoteSetOutputState(
		con,
		port,
		speed, 
		OUT_MODE_MOTORON, 
		OUT_REGMODE_IDLE, 
		turnpct,
		OUT_RUNSTATE_RUNNING,
		tacholimit);
	
}

void BrakeOn(int con, int port){
	
	RemoteSetOutputState(
		con,
		port,
		0,
		OUT_MODE_BRAKE,
		OUT_REGMODE_SYNC,
		0,
		OUT_RUNSTATE_HOLD,
		0);

}



task main(){
	
	RemotePlayTone(CONN_BT1, 1000,1000);
	
	Wait(30);
	
	PlayFile("Kvaque1.rso");
	
	float speedA = 0;
	float speedB = 0;
	float speedC = 0;
	bool clearScreenWait = true;
	
	SetSensorTouch(IN_1);
	
	while(true){
	
		//käsi
		if(abs(MotorTachoCount(OUT_A)) > 12){
			speedA = Between(MotorTachoCount(OUT_A) + 45 * GetDirection(MotorTachoCount(OUT_A)),-75,75);
		}else{
			speedA = 0;
		}
		
		
		//renkaat
		if(abs(MotorTachoCount(OUT_B)) > 12){
			speedB = (MotorTachoCount(OUT_B) + 50 * GetDirection(MotorTachoCount(OUT_B)));
			
		}else{
			speedB = 0;
		}
		if(abs(MotorTachoCount(OUT_C)) > 12){
			speedC = (MotorTachoCount(OUT_C) + 50 * GetDirection(MotorTachoCount(OUT_C)));
		}else{
			speedC = 0;
		}
		
		
		TextOut(10,30, "speed A: " + NumToStr(speedA));
		TextOut(10,20, "speed B: " + NumToStr(speedB));
		TextOut(10,10, "speed C: " + NumToStr(speedC));		 


		//Send motor controls
		SendMotorRotation(CONN_BT1, OUT_B, speedB);
		clearScreenWait = false;
		Wait(30);

		SendMotorRotation(CONN_BT1, OUT_C, speedC);
		clearScreenWait = false;
		Wait(30);

		SendMotorRotation(CONN_BT1, OUT_A, speedA);
		clearScreenWait = false;
		Wait(30);
		
		
		
		if (clearScreenWait){
			Wait(30);
		}
		
		//the "Duck button"
		if(Sensor(IN_1) == true){
			break ;
		}
		
		ClearScreen();
		clearScreenWait = true;
	}
	
	SendMotorRotation(CONN_BT1, OUT_B, 0);
	Wait(30);
	SendMotorRotation(CONN_BT1, OUT_C, 0);
	Wait(30);
	
	RemoteStartProgram(CONN_BT1, "kokoveto.rxe");
	Wait(1000);
	
	ClearScreen();
	
	//Quackenator
	while(true){
		TextOut(10,50, "Duck is Love");
		TextOut(10,40, "Duck is Life!");
		TextOut(10,20, "Quaaak!");
		TextOut(10,10, "RobotUpRising!");
		PlayFile("Kvaque1.rso");
		Wait(7500 + Random(5000));
	}
		
	

}