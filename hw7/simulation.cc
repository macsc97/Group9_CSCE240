#include "simulation.h"
/****************************************************************
* Implementation for the 'Simulation' class.
*
* Author/copyright:  Duncan Buell
* Date: 19 July 2016
* 
* Modified by Michael Cantwell on 11/22/16
* -Added correct spacing
* 
* Michael Cantwell on 11/22/16
* -Added comments
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
 * 
**/
void Simulation::RunSimulation(const Configuration& config, 
                               MyRandom& random, ofstream& out_stream)
{
  
  string outstring = "XX";
  int pct_count_this_batch = 0;
  
  for(auto iterPct = pcts_.begin(); iterPct != pcts_.end(); ++iterPct)
  {
  
    OnePct pct = iterPct->second;
    
    int expected_voters = pct.GetExpectedVoters();
    
    if ((expected_voters <=  config.min_expected_to_simulate_) || 
        (expected_voters >   config.max_expected_to_simulate_)) continue;
    
    outstring = kTag + "RunSimulation for pct " + "\n";
    outstring += kTag + pct.ToString() + "\n";
    Utils::Output(outstring, out_stream, Utils::log_stream);
    
    ++pct_count_this_batch;
    pct.RunSimulationPct(config, random, out_stream);
    
    //    break; // we only run one pct right now
  } // for(auto iterPct = pcts_.begin(); iterPct != pcts_.end(); ++iterPct)
  
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
**/
string Simulation::ToString()
{

  string s = "";
  
  for(auto iterPct = pcts_.begin(); iterPct != pcts_.end(); ++iterPct)
  {
  
    s += kTag + (iterPct->second).ToString() + "\n";
  }
  
  return s;
} // string Simulation::ToString()

