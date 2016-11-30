#include "onevoter.h"
/****************************************************************
* Implementation for the 'OneVoter' class.
*
* Author/copyright:  Duncan Buell. All rights reserved.
* Date last modified: 29 November 2016
*
* Modified by: CSCE240 Group9 Fall 2016
* (M.CANTWELL, R.CARFF, A.FRAZIER, C.KAYLOR, S.MARTIN)
*
* Objective: This class has multiple functions. There are many
* accessor type functions for multipe variables, including:
* GetTOD, GetStationNumber, GetTimeArrival, GetTimeDoneVoting, 
* GetTimeInQ, and GetTimeWaiting. The constructor sets up 'sequence', 
* 'time_arrival_seconds', 'time_start_voting_seconds', 
* 'time_vote_duration_seconds', and the initial station
* 'which_station'. 'AssignStation' assigns a voter to a station.
* 'ConvertTime' returns a formatted string of time in an
* 'hour:minutes:seconds' format. 'ToString' returns a formatted
* string, as per usual. 'ToStringHeader' returns a formatted string
* for the variables in the header file.
*
* November 29, 2016 A. Frazier
* -Added objective overview, commenting and formatting changes.
*
* edit nov 27-Sebastian Martin
* - added comments
**/

static const string kTag = "ONEVOTER: ";

/****************************************************************
* Constructor.
**/
OneVoter::OneVoter() {
}
/****************************************************************
*sets up original variables for a specific voter
 * Parameters:
 *   sequence- the spot of the voter in the sequence
     arrival_seconds-the arrival time of the voter
     duration_seconds- how long the voter was there
 *
 
**/
OneVoter::OneVoter(int sequence, int arrival_seconds, int duration_seconds) {

  sequence_ = sequence;
  time_arrival_seconds_ = arrival_seconds;
  time_start_voting_seconds_ = 0;
  time_vote_duration_seconds_ = duration_seconds;
  // magic number -1   
  which_station_ = -1;
}

/****************************************************************
**/
OneVoter::~OneVoter() {
}

/****************************************************************
* Accessors and mutators.
**/
/****************************************************************
**/
int OneVoter::GetTimeArrival() const {

  return time_arrival_seconds_;
}

/****************************************************************
**/
int OneVoter::GetTimeWaiting() const {

  return time_waiting_seconds_;
}

/****************************************************************
**/
int OneVoter::GetStationNumber() const {

  return which_station_;
}

/****************************************************************
* General functions.
**/

/****************************************************************
This class assigns a certain station to a voter, it is based 
off the station numbers, and the start time
**/
void OneVoter::AssignStation(int station_number, int start_time_seconds) {

  which_station_ = station_number;
  time_start_voting_seconds_ = start_time_seconds;
  time_done_voting_seconds_ = time_start_voting_seconds_ + time_vote_duration_seconds_;
  time_waiting_seconds_ = time_start_voting_seconds_ - time_arrival_seconds_;
}

/****************************************************************
accessors
**/
int OneVoter::GetTimeDoneVoting() const {

  return time_start_voting_seconds_ + time_vote_duration_seconds_;
}

/****************************************************************
**/
int OneVoter::GetTimeInQ() const {

  return time_start_voting_seconds_ - time_arrival_seconds_;
}

/****************************************************************
this will return the time in a format with hours/minutes/seconds
for the current time_in_seconds and offset_hours*3600
**/
string OneVoter::GetTOD(int time_in_seconds) const {

  //  int offset_hours = 6;
  int offset_hours = 0;
  string s = "";
  return this->ConvertTime(time_in_seconds + offset_hours*3600);
}

/****************************************************************
this method will take in the time that it has taken for a voter in 
seconds. It will then convery this into an hour/minute/second format
and return it as a string
**/
string OneVoter::ConvertTime(int time_in_seconds) const {
  //initilizing variables
  int hours = 0;
  int minutes = 0;
  int seconds = 0;
  string s = "";
  
  hours = time_in_seconds / 3600;
  minutes = (time_in_seconds - 3600*hours) / 60;
  seconds = (time_in_seconds - 3600*hours - 60*minutes);
  
  s += Utils::Format(time_in_seconds, 6);
  
  if(hours < 0)
  s += " 00";
  else if(hours < 10)
  s += " 0" + Utils::Format(hours, 1);
  else
  s += " " + Utils::Format(hours, 2);
  
  if(minutes < 0)
  s += ":00";
  else if(minutes < 10)
  s += ":0" + Utils::Format(minutes, 1);
  else
  s += ":" + Utils::Format(minutes, 2);
  
  if(seconds < 0)
  s += ":00";
  else if(seconds < 10)
  s += ":0" + Utils::Format(seconds, 1);
  else
  s += ":" + Utils::Format(seconds, 2);
  
  return s;
} // string OneVoter::ConvertTime(int time_in_seconds) const

/****************************************************************
*this method will format the data for the specific voter in order
for it to be printed out, and it will be returned as a string
**/
string OneVoter::ToString() {

  string s = kTag;
  
  s += Utils::Format(sequence_, 7);
  s += ": ";
  s += Utils::Format(this->GetTOD(time_arrival_seconds_));
  s += " ";
  s += Utils::Format(this->GetTOD(time_start_voting_seconds_));
  s += " ";
  s += Utils::Format(this->ConvertTime(time_vote_duration_seconds_));
  s += " ";
  s += Utils::Format(this->GetTOD(time_start_voting_seconds_ + time_vote_duration_seconds_));
  s += " ";
  s += Utils::Format(this->ConvertTime(GetTimeInQ()));
  s += ": ";
  s += Utils::Format(which_station_, 4);
  
  return s;
} // string OneVoter::toString()

/****************************************************************
* This method will print out a formatted header for the files
**/
string OneVoter::ToStringHeader() {

  string s = kTag;
  s += "    Seq        Arr           Start             Dur             End            Wait         Stn";
  return s;
}

