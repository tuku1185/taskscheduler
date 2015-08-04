// quickstart.cpp : Defines the entry point for the console application.
//

#include "CTask.h"

int main(int /*argc*/, char* /*argv[]*/)
{
CTask task;									//konstruujemy obiekt klasy CTask;
CTime time(2004, 04, 01, 10, 10, 0);		//data utworzenia
LPCTSTR sTaskName("TaskName");				//nazwa zadania
BOOL bReplace = TRUE;						//zamien, jesli zadanie istnieje


	task.SetProgram     ( "" );				//Required
	task.SetParameters  ( "");				//Optional
	task.SetStartingDir ( "" );				//Optional
	task.SetAccountName ( "" );				//Required
	task.SetPassword    ( "" );				//Required
	task.SetComment     ( "" );				//Optional
	task.SetStartDateTime ( time );			//Required
	task.SetFrequency ( CTask::freqOnce );	//Required

	//dodajemy zadanie do harmonogramu
	if ( S_OK == task.SaveTask ( sTaskName, bReplace ))
	{
	MessageBox(GetActiveWindow(), "The task has been scheduled!", "", MB_OK);
	return 0;
	}
	else
	{
	MessageBox(GetActiveWindow(), "Unable to put the task on schedule!", "", MB_OK);
	return 1;
	}
}
