#include <iostream>
#include <sstream>
#include <string>
#include <ctime>
#include <stdio.h>


/** returns local time **/
std::string localTimeFinder() {
// Declaring argument for time()
time_t tt;
// Declaring variable to store return value of
// localtime()
struct tm *ti;
// Applying time()
time (&tt);
// Using localtime()
ti = localtime(&tt);
std::string time_And_Date = asctime(ti); //returns human readable time
 return time_And_Date.substr(0, time_And_Date.size()-1); //returns human readable time with last new line character getting removed
}

/** logs the incoming buffer to log.txt **/
void logIncoming(char buffer[4096]) {
  FILE *log;
  std::string time_With_Buffer = localTimeFinder() +" "+ buffer;
  log = fopen("log.txt", "a");
  fprintf(log, time_With_Buffer.c_str());
  fclose(log);
}

/** sepeates string to different words if space sperated **/
std::string seperateWordBySpace(std::string str)
{
    // Used to split string around spaces.
    std::istringstream ss(str);
    std::string word; // for storing each word

    // Traverse through all words
    // while loop till we get
    // strings to store in string word
    ss >> word;
	  return word;
}
