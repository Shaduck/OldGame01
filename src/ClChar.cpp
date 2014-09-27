
T_Character::T_Character(void)
{

}

T_Character::~T_Character(void)
{

}

void T_Character::InitCharacter(byte x,byte y)
{

	status.move=0;
	status.run=0;
	status.crouch=0;
	status.graspcl=0;
	status.graspst=0;
	status.climb=0;
	status.stairs=0;
	status.jump=0;
	status.hitted=0;
	status.attack=0;
	status.fall=0;

	movecont=0;

	climbcont=0;

	//jumpcont=JUMP_DELAY;
	//movecont=MOVE_DELAY;
	//stairstemp=0;

	stairscont=0;
	stairsflag=0;
	stairsstx[0]=UNITX/NSTFRAME;
	stairssty[0]=UNITY/NSTFRAME;
	for(byte i=1;i<NSTFRAME;i++){
		stairsstx[i]=UNITX;
		stairssty[i]=UNITY;
		for(byte j=0;j<i;j++){
			stairsstx[i]-=stairsstx[j];
			stairssty[i]-=stairssty[j];
		}
	}

	dirx=0;
	diry=0;

	speedx=SPEXNORM;
	speedjump=0;
	speedfall=1;
	//speedup=SPEYUP;
	//speeddown=SPEYDOWN;



	InitScreenObj(x,y);

	return;

}

////////////////////////////////////////////////////////////////////////
////////////////  GESTIONE    MOVIMENTI  ///////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////


byte T_Character::setmove(byte dir)
{
  	if(status.crouch||status.climb||status.graspst||
  							status.stairs||status.hitted||status.attack)
  		return 0;
  	if(!status.jump&&!status.fall)
  		dirx=dir;
	status.move=true;
	return 1;
}

byte T_Character::resmove(void)
{
	status.move=false;
	//dirx=DIR_CENTRE;
	return 1;
}


/*byte T_Character::setrun(void)
{
	if(status.graspcl||status.graspst||status.climb||
		status.stairs||status.jump||status.hitted||status.fall)
		return 0;
	run=true;
	speedx=SPEXRUN;
	return 1;
}

byte T_Character::resrun(void)
{
	//if(status.graspcl||status.graspst||status.climb||
			status.stairs||status.jump||status.hitted||status.fall)
	//	return 0;

	run=false;
	speedx=SPEXNORM;
	return 1;
}  */

byte T_Character::setcrouch(void)
{
	if(status.move||status.crouch||status.graspcl||
		status.climb||status.stairs||status.jump||
		status.hitted||status.attack||status.fall)

		return 0;
	status.crouch=true;
	return 1;
}

byte T_Character::rescrouch(void)
{
	if(status.move||status.graspcl||status.graspst||
		status.climb||status.stairs||status.jump||
		status.hitted||status.attack||status.fall)
		return 0;
	status.crouch=false;
	return 1;
}

byte T_Character::setgraspcl(byte dir)
{
	byte temp;

	if(dir==DIR_UP){
		temp=testover(CLIMB_TERR);
	}else{
		if(dir==DIR_DOWN){
			temp=testtop(CLIMB_TERR);
		}
	}

	if(temp){
		if(temp==DIR_CENTRE){
			status.graspcl=true;
			status.fall=false;
			return 1;
		}

		dirx=temp;
		status.move=true;

		return 1;
	}

	return 0;
}

byte T_Character::resgraspcl(void)
{
	if(!status.graspcl)
		return 0;

	status.graspcl=false;
	return 1;
}

byte T_Character::setclimb(byte dir)
{

	if(status.crouch||status.stairs||status.attack)
		return 0;

	if(!setgraspcl(dir))
		return 0;

	if(status.graspcl){
		status.climb=true;
		diry=dir;
	}
	return 1;
}

byte T_Character::resclimb(void)
{
	if(!status.climb)
		return 0;

	status.climb=false;
	return 1;
}

byte T_Character::setgraspst(byte dir)
{
	byte temp;

	temp=testunder(STAIRS);
	if(temp){

		if(temp==DIR_CENTRE){
			status.graspst=true;
			return 1;
		}

		dirx=temp;
		status.move=true;
		return 1;
	}

	return 0;
}

byte T_Character::resgraspst(void)
{
	if(!status.graspst)
		return 0;

	status.graspst=false;
	return 1;
}

byte T_Character::setstairs(byte dir)
{

	if(status.jump||status.fall||status.crouch||
		status.climb||status.attack)
		return 0;

	if(!status.graspst){
		if(!setgraspst(dir)){
  			status.stairs=false;
			stairsflag=0;

			return 0;
		}
	}

	diry=dir;

	if(!stairstest)
		stairstest=2;

	status.stairs=true;

	return 1;
}

byte T_Character::resstairs(void)
{
	if(!status.stairs||stairstest)
		return 0;

	status.stairs=false;
	return 1;
}


byte T_Character::setjump(void)
{
	if(status.crouch||status.graspcl||status.graspst||
		status.climb||status.stairs||status.jump||
		status.hitted||status.attack||status.fall)
		return 0;

	jumpdelay=JUMP_DELAY;
	speedjump=SPEJUMP;
	status.jump=true;

	return 1;
}

/////////////////////////////////////////////////////////////////////////

byte T_Character::moveplatform(void)
{
	byte temp=0;

	temp=TestBorder();

	if(temp)
		return temp;

	temp=0;

	if(status.jump){

		temp=goup(SEMISOLID,speedjump);

		if(!jumpdelay){
			if(speedjump==0||!temp){
				status.jump=false;
				status.fall=true;
				speedfall=0;
			}
			speedjump--;
			jumpdelay=JUMP_DELAY;
		}

		if(status.move){
			if(dirx==DIR_LEFT)
				goleft(SEMISOLID,speedx);
			if(dirx==DIR_RIGHT)
				goright(SEMISOLID,speedx);
		}

		jumpdelay--;
		return 0;
	}

	if(!status.graspcl&&!status.graspst){
		if(godown(NOSOLID,speedfall)){
			status.fall=true;

			if(speedfall<SPEFALL)
				speedfall++;

		}else{
			status.fall=false;
			speedfall=1;
		}
	}

	if(status.crouch){
		gocrouch();
		return 0;
	}else{		//if(!crouch){
		goraise();
	}

	if(status.move){

		if(!movecont){
			if(dirx==DIR_LEFT)
				goleft(SEMISOLID,speedx);
			if(dirx==DIR_RIGHT)
				goright(SEMISOLID,speedx);

			if(status.graspcl&&!testtop(CLIMB_TERR))
				status.graspcl=false;

			//stairstest--;

			movecont=MOVE_DELAY;
		}
		movecont--;
		return 0;
	}

	if(status.climb){
		if(!climbcont){
			if(diry==DIR_UP){
				goup(SEMISOLID,speedx);
			}
			if(diry==DIR_DOWN){
				godown(SEMISOLID,speedx);
			}
			climbcont=CLIMB_DELAY;
		}
		climbcont--;
		return 0;
	}

	if(status.stairs){

		if(diry==DIR_UP)
			temp=testbottom(STAIRS);

		if(diry==DIR_DOWN)
			temp=testunder(STAIRS,UNITY);

		if(!temp){
			status.graspst=false;
			status.stairs=false;
			return 0;
		}

		if(!stairscont){
			if(temp==DIR_RIGHT){
				goright(ALLSOLID,stairsstx[stairsflag]);

			}
			if(temp==DIR_LEFT){
				goleft(ALLSOLID,stairsstx[stairsflag]);
			}

			if(diry==DIR_UP){
				goup(ALLSOLID,stairssty[stairsflag]);

				if(!stairsflag){
					stairsflag=NSTFRAME-1;
				}
				stairsflag--;
			}

			if(diry==DIR_DOWN){
				godown(ALLSOLID,stairssty[stairsflag]);

				stairsflag++;
				if(stairsflag>(NSTFRAME-1))
					stairsflag=0;

			}
			stairstest--;

			stairscont=STAIRS_DELAY;
		}
		stairscont--;

		if(diry==DIR_UP&&temp!=testbottom(STAIRS)){
			status.graspst=false;
			status.stairs=false;
		}
		if(diry==DIR_DOWN&&temp!=testunder(STAIRS,UNITY)){
			status.graspst=false;
			status.stairs=false;
		}

		return 0;
	}

	return 0;
}


////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////