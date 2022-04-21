
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <string>
#include <string.h>
#include "noc.hpp"

// Booksim:main.cpp dependency
#include "booksim.hpp"
#include "routefunc.hpp"
#include "traffic.hpp"
#include "booksim_config.hpp"
#include "trafficmanager.hpp"
#include "random_utils.hpp"
#include "network.hpp"
#include "injection.hpp"
#include "power_module.hpp"
#include "globals.hpp"

/* printing activity factor*/
bool gPrintActivity;
int gK; //radix
int gN; //dimension
int gC; //concentration
int gNodes;
//generate nocviewer trace
bool gTrace;
ostream * gWatchOut;

// Well ... old troublesomes from booksim2
TrafficManager* trafficManager = NULL;


spatial::NoC::NoC(BookSimConfig config, PCNInterfaceSet send_queues_, PCNInterfaceSet receive_queues_) {
    /*initialize routing, traffic, injection functions
   */

    _config = config;
    InitializeRoutingMap(config);

    gPrintActivity = (config.GetInt("print_activity") > 0);
    gTrace = (config.GetInt("viewer_trace") > 0);
    
    string watch_out_file = config.GetStr( "watch_out" );
    if(watch_out_file == "") {
        gWatchOut = NULL;
    } else if(watch_out_file == "-") {
        gWatchOut = &cout;
    } else {
        gWatchOut = new ofstream(watch_out_file.c_str());
    }

    // Setup Nets
    vector<Network *> net;
    int subnets = config.GetInt("subnets");
    if (subnets != 1) {
        throw "The number of subnets is not 1 !!";
    }

    /*To include a new network, must register the network here
    *add an else if statement with the name of the network
    */
    net.resize(subnets);
    for (int i = 0; i < subnets; ++i) {
        ostringstream name;
        name << "network_" << i;
        net[i] = Network::New( config, name.str() );
    }

    _traffic_manager = TrafficManager::New(config, net);
    _traffic_manager->SetupSim(send_queues_, receive_queues_);
    trafficManager = _traffic_manager;
}


void spatial::NoC::step(clock_t clock) {
    _traffic_manager->_Step();
}


void spatial::NoC::DisplayStats(std::ostream & os) {
    _traffic_manager->_DisplayRemaining(os);
}