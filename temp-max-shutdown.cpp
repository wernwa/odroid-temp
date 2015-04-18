#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <signal.h>
using namespace std;


// shutdown at critical temperature in degree
double max_temp = 95;
// sleep intervall in seconds between reading the temperature
double sleep_interval = 1;
// path to the temperature file
const char *temp_file_path = "/sys/devices/virtual/thermal/thermal_zone0/temp";


unsigned int microseconds = sleep_interval*1000000;
bool ALIVE=true;


void strl_c(int sig){
      ALIVE = false;
}


int main(){
    string line;
    ifstream temp_file (temp_file_path);
    signal(SIGINT, strl_c);

    if (temp_file.is_open())
    {

        while(ALIVE){
            temp_file.seekg (0, temp_file.beg);
            getline (temp_file,line);
            //cout << line << '\n';
            double curr_temp = std::stod (line)/1000;
            if (curr_temp >= max_temp){
                char logmsg[100];
                sprintf(logmsg,"/usr/bin/logger -t temp-max-shutdown '!!! critical temperature of %.3f degree reached, force the system to shut down. !!!'",curr_temp);
                system(logmsg);
                system("/sbin/shutdown -P now");
                //system("echo $PATH");
                ALIVE=false;
            }
            usleep(microseconds);
        }
        temp_file.close();

    }else cout << "Unable to open file" << endl; 


    return 0;
}
