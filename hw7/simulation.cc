#include "simulation.h"
/****************************************************************
* Implementation for the 'Simulation' class.
*
* Author/copyright:  Duncan Buell
* Date last modified: 29 November 2016
*
* Modified by: CSCE240 Group9 Fall 2016
* (M.CANTWELL, R.CARFF, A.FRAZIER, C.KAYLOR, S.MARTIN)
*
* Objective: The first function 'ReadPrecints' utilizes a scanner
* to parse a file 'infile' of precint data. Utilizes the 'ReadData'
* function from 'onepct.cc' to parse the data from the file and =
* create a new instance of precint. 'RunSimulation' actually
* performs the simulation, and iterates over all of the precints
* and calls 'RunSimulationPct' for each precint. 'ToString' and
* 'ToStringPcts' work as expected, and return a formatted string
* 
* Modified by Michael Cantwell on 11/22/16
* -Added correct spacing
* 
* Michael Cantwell on 11/22/16
* -Added comments
* 
* Michael Cantwell on 11/26/16
* -Added more comments
*
* Updated 11/19/16 A. Frazier
*- Added Objective overview and comment changes
**/

static const string kTag = "SIM: ";

/****************************************************************
* Constructor.
**/
Simulation::Simulation()
{
}

/****************************************************************
* Destructor.
**/
Simulation::~Simulation()
{
}

/****************************************************************
* Accessors and mutators.
**/

/****************************************************************
* General functions.
**/
/****************************************************************
* ReadPrecincts Function
* 
* A simple function to detect data and pass it along to the
* onepct class. When there is data, the function creates a new
* instance of onepct. The function then calls the ReadData
* function of the new precinct to fill in its own data.
* Last the function adds the new instance of onepct to a map.
* 
**/
void Simulation::ReadPrecincts(Scanner& infile) {

  while (infile.HasNext()) {
    //when the Scanner has file to read, it creates a precinct
    //and calls that new precinct's ReadData function
    OnePct new_pct;
    new_pct.ReadData(infile);
    //adds new precinct to a map of precincts
    pcts_[new_pct.GetPctNumber()] = new_pct;
  } // while (infile.HasNext()) {

} // void Simulation::ReadPrecincts(Scanner& infile) {

/****************************************************************
 * RunSimulation Function 
 * 
 * This function basically goes through and calls the individual
 * simulation running functions of the different instances of
 * precincts. First it starts a for loop that iterates through 
 * the map of precincts. It then creates a precinct instance of
 * each precinct encountered in the map. Then if the expected 
 * voters number is outside of the expected to simulation 
 * numbers it continues the code. The precinct's toString is called
 * and then put into the output string. Then the precinct's
 * RunSimulationPct function is called. 
 * The for loop ends and the output string is sent to 
 * a function in the Utils that outputs the string.
**/
void Simulation::RunSimulation(const Configuration& config, 
                               MyRandom& random, ofstream& out_stream)
{
  
  string outstring = "XX";
  int pct_count_this_batch = 0;
  
  //for loop that iterates through the precincts
  for(auto iterPct = pcts_.begin(); iterPct != pcts_.end(); ++iterPct)
  {
  
    //create a precinct instance and move the iterator
    OnePct pct = iterPct->second;
    
    //fill in variables from precinct
    int expected_voters = pct.GetExpectedVoters();
    
    //if the expected voters is less than the minimum expected or greater
    //than the maximum expected then the code continues
    if ((expected_voters <=  config.min_expected_to_simulate_) || 
        (expected_voters >   config.max_expected_to_simulate_)) continue;
    
    //build the output string with data from the precinct's ToString
    outstring = kTag + "RunSimulation for pct " + "\n";
    outstring += kTag + pct.ToString() + "\n";
    Utils::Output(outstring, out_stream, Utils::log_stream);
    
    //increment the precinct count
    ++pct_count_this_batch;
    //call the precinct class's RunSimulationPct function
    pct.RunSimulationPct(config, random, out_stream);
    
    //    break; // we only run one pct right now
  } // for(auto iterPct = pcts_.begin(); iterPct != pcts_.end(); ++iterPct)
  
  //add Precinct count to output string
  //comments following code are what the called functions do
  outstring = kTag + "PRECINCT COUNT THIS BATCH "
  + Utils::Format(pct_count_this_batch, 4) + "\n";
  //  Utils::Output(outstring, out_stream);
  Utils::Output(outstring, out_stream, Utils::log_stream);
  //  out_stream << outstring << endl;
  //  out_stream.flush();
  //  Utils::log_stream << outstring << endl;
  //  Utils::log_stream.flush();
  
} // void Simulation::RunSimulation()

/****************************************************************
* Usual 'ToString'.
* 
* Use a for loop to go through the map of precincts and call
* each individual precinct's toString function and adds it to
* the output string.
**/
string Simulation::ToString()
{

  string s = "";
  
  //use for loop to iterate through the map
  for(auto iterPct = pcts_.begin(); iterPct != pcts_.end(); ++iterPct)
  {
    //add each precinct's toString to the output string
    s += kTag + (iterPct->second).ToString() + "\n";
  }
  
  return s;
} // string Simulation::ToString()

