////////////////////////////////////////////////////////////////////////
////////////////  GESTIONE    MOVIMENTI  ///////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

bool T_Character::godown(byte sollim,byte dis)
{
	for(byte var1=0;var1<dis;var1++){
		for(byte i=0;i<ntopcp;i++){
			if(solid[coordy][coordx+topcp[i]]>sollim)
				return false;
		}
		coordy++;
	}
	return true;
}


bool T_Character::goleft(byte sollim,byte dis)
{
	for(byte var1=0;var1<dis;var1++){
		for(byte i=0;i<nleftcp;i++){
			if(solid[coordy-leftcp[i]-1][coordx-1]>sollim)
				return false;
		}
		coordx--;
	}
	return true;
}


bool T_Character::goright(byte sollim,byte dis)
{
	for(byte var1=0;var1<dis;var1++){
		for(byte i=0;i<nleftcp;i++){
			if(solid[coordy-leftcp[i]-1][coordx+chlargh]>sollim)
				return false;
		}
		coordx++;
	}
	return true;
}


bool T_Character::goup(byte sollim,byte dis)
{
	for(byte var1=0;var1<dis;var1++){
		for(byte i=0;i<ntopcp;i++){
			if(solid[coordy-chaltezz-1][coordx+topcp[i]]>sollim)
				return false;
		}
		coordy--;
	}
	return true;
}


void T_Character::gocrouch(void)
{

	nunity=crouchy;

	chaltezz=nunity*UNITY;

	nleftcp=nunity+1;

	return;
}

void T_Character::goraise(void)
{

	nunity=normaly;

	chaltezz=nunity*UNITY;

	nleftcp=nunity+1;

	return;
}




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

	if(coordx<X_OFFSET)
		return DIR_LEFT;

	if(coordy<Y_OFFSET-10)
		return DIR_UP;

	if(coordx>SCREEN_W-chlargh+X_OFFSET)
		return DIR_RIGHT;

	if(coordy>SCREEN_H+Y_OFFSET-1)
		return DIR_DOWN;

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