/*
 * Project: Boost Logging System 
 * File: main.cpp
 * Author: Majid Lashgarian <Majid@Lashgarian.com>
 * Date: March.2015
 * Copuright 2015 Majid Lashgarian 
 * under MIT Open source License
 */

#include "Log.hh"
#define INFO LOGGING::Info() 
#define WARN LOGGING::Warn() 
#define DEB LOGGING::Debug() 
#define ERR LOGGING::Error() 
#define CRIT LOGGING::Crit() 

int main(int argc, char** argv)
{
   
    LOGGING::Log::init();
    INFO <<" Information" ; 
    WARN <<" Warning" ; 
    DEB <<" Debug" ; 
    ERR <<" Error" ; 
    CRIT <<" Critical" ; 
    return 0 ; 
}
