/////////////////////////
void LTimer::start_timer()
/////////////////////////
{
    //get the current clock time
	start = SDL_GetTicks();
	
	//set the paused ticks to 0
	pTicks = 0;
	
	//unpause the timer
	timerPaused = false;
}

///////////////////////
int LTimer::get_ticks()
///////////////////////
{
    //if the timer is paused
    if( timerPaused == true )
    {
        //return the paused ticks
        return pTicks;   
    }

    //return the current time minus the start time
	return SDL_GetTicks() - start;
}

//////////////////////////
void LTimer::pause_timer()
//////////////////////////
{
    //calculate the paused ticks
    pTicks = SDL_GetTicks() - start;
    
    //pause the timer
    timerPaused = true;
}

///////////////////////////
void LTimer::resume_timer()
///////////////////////////
{
    //if the timer is paused
    if( timerPaused == true )
    {
        //restart the start point
        start = SDL_GetTicks() - pTicks;
        
        //reset the paused ticks
        pTicks = 0;
        
        //unpause the timer
        timerPaused = false;   
    }
}

/////////////////////
bool LTimer::paused()
/////////////////////
{
    return timerPaused;
}
