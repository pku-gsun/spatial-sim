#ifndef __SPATIAL_SIM_CONFIG_H__
#define __SPATIAL_SIM_CONFIG_H__

#include "config_utils.hpp"

class SpatialSimConfig : public Configuration {
public:
    SpatialSimConfig() {
        AddStrField("log_file", "log.txt");

        _int_map["array_size"] = 16;    // The size of core array
        _int_map["network_size"] = 16;  // The size of network ( equal to core array by default )

        AddStrField("core_array_spec", "cas");  // relative path of the core specification file
        AddStrField("noc_spec", "ns");          // relative path of the noc specification file
    }
};


#endif