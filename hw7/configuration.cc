#include "configuration.h"
/****************************************************************
 * Implementation for the 'Configuration' class.
 * 
 * Only has two functions. The first is the ReadConfiguration
 * function which main purpose is to take in a Scanner to 
 * parse a correctly formatted file into the appropriate 
 * variables. It then takes in the data in dataallsorted.txt
 * and stores it as well.
 * The second function is the simple ToString function
 * which builds a string of the data associated with this class.
 * 
 * Author/copyright:  Duncan Buell. All rights reserved.
 * Date: 6 October 2016
 * 
 * Modified by Michael Cantwell on 11/21/16
 * -Added correct spacing to code
 *
 * Michael Cantwell on 11/22/16
 * -Added comments
 *
**/

static const string kTag = "CONFIG: ";

/****************************************************************
 * Constructor.
**/
Configuration::Configuration() {
}

/****************************************************************
 * Destructor.
**/
Configuration::~Configuration() {
}

/****************************************************************
 * Accessors and mutators.
**/
/****************************************************************
**/
int Configuration::GetMaxServiceSubscript() const {
  
  return static_cast<int>(actual_service_times_.size()) - 1;

}

/****************************************************************
 * General functions.
**/
/****************************************************************
 * ReadConfiguration Function
 * 
 * Takes in a Scanner, then uses that to parse into its
 * appropriate values the file the Scanner is using.
 * Variables are filled in as the Scanner goes through a 
 * properly formatted file. Variables are declared in 
 * header file.
 * Then it opens up dataallsorted.txt and parses its
 * data into a vector.
 * 
**/
void Configuration::ReadConfiguration(Scanner& instream) {
/*
*/
  //parse data in through Scanner
  string line;
  ScanLine scanline;
  
  //break input down into lines
  line = instream.NextLine();
  scanline.OpenString(line);
  //breaks apart each line into the corresponding int values
  seed_ = scanline.NextInt();
  election_day_length_hours_ = scanline.NextInt();
  election_day_length_seconds_ = election_day_length_hours_ * 3600;
  time_to_vote_mean_seconds_ = scanline.NextInt();
  min_expected_to_simulate_ = scanline.NextInt();
  max_expected_to_simulate_ = scanline.NextInt();
  wait_time_minutes_that_is_too_long_ = scanline.NextInt();
  number_of_iterations_ = scanline.NextInt();
  
  line = instream.NextLine();
  scanline.OpenString(line);
  arrival_zero_ = scanline.NextDouble();
  
  for (int sub = 0; sub < election_day_length_hours_; ++sub) {
    //doubles are taken from the input and pushed into a vector
    double input = scanline.NextDouble();
    arrival_fractions_.push_back(input);
  }
  
  //open dataallsorted.txt next
  Scanner service_times_file;
  service_times_file.OpenFile("dataallsorted.txt");
  
  while (service_times_file.HasNext()) {
    //fill in a vector with this data 
    int thetime = service_times_file.NextInt();
    actual_service_times_.push_back(thetime);
  }
}

/****************************************************************
 * ToString Function
 * 
 * When called it builds a string consisting of all of the 
 * relevant data retrieved by the class. Pretty self-explanitory.
**/
string Configuration::ToString()
{
  string s = "\n";
  s += kTag;
  s += "RN seed:              ";
  s += Utils::Format(seed_, 8) + "\n";
  s += kTag;
  s += "Election Day length:  ";
  s += Utils::Format(election_day_length_seconds_, 8) + " =";
  s += Utils::Format(election_day_length_seconds_/3600.0, 8, 2) + " (";
  s += Utils::Format(election_day_length_hours_, 8, 2) + ") hours\n";
  s += kTag;
  s += "Time to vote mean:    ";
  s += Utils::Format(time_to_vote_mean_seconds_, 8) + " =";
  s += Utils::Format(time_to_vote_mean_seconds_/60.0, 8, 2) + " minutes\n";
  s += kTag;
  s += "Min and max expected voters for this simulation:     ";
  s += Utils::Format(min_expected_to_simulate_, 8);
  s += Utils::Format(max_expected_to_simulate_, 8) + "\n";
  s += "Wait time (minutes) that is 'too long': ";
  s += Utils::Format(wait_time_minutes_that_is_too_long_, 8) + "\n";
  s += "Number of iterations to perform: ";
  s += Utils::Format(number_of_iterations_, 4) + "\n";
  s += "Max service time subscript: ";
  s += Utils::Format(GetMaxServiceSubscript(), 6) + "\n";
  int offset = 6;
  s += kTag;
  s += Utils::Format(0, 2) + "-" + Utils::Format(0, 2);
  s += " : " + Utils::Format(arrival_zero_, 7, 2) + "\n";
  
  for (UINT sub = 0; sub < arrival_fractions_.size(); ++sub) {
    
    s += kTag;
    s += Utils::Format(offset+sub, 2) + "-" + Utils::Format(offset+sub+1, 2);
    s += " : " + Utils::Format(arrival_fractions_.at(sub), 7, 2) + "\n";
  }  
  
  s += "\n";
  
  return s;
}

