#include <stdexcept>
#include <iostream>
#include <ctime>
#include <utility>

#include "opcpp_ic.h"

/// @brief Starting the program simulates a start of the circuit which means this bool MUST be set as TRUE
const bool& system_is_powered_up{true};

int main(int argc, char const *argv[])
{
    // TASK:
    // upon program start, configure and set up sensor names,
    // TODO: rerun failed sensor starts
    // via cli

    // ./main.exe name1 name2 name3 name4

    const int sensor_count{4};

    std::string sensor_names[sensor_count];
    for (int i = 0; i < sensor_count; ++i) {
        sensor_names[i] = argv[i + 1];
    }

    try {
        std::cout << "Attempting to power up the sensors, named:" << std::endl;
        for (int i = 0; i < sensor_count; ++i) {
            std::cout << sensor_names[i] << std::endl;
        }
        
        power_up_sensor(Sensor::lidar,      sensor_names[0]);
        power_up_sensor(Sensor::radar,      sensor_names[1]);
        power_up_sensor(Sensor::ultrasonic, sensor_names[2]);
        power_up_sensor(Sensor::pressure,   sensor_names[3]);
        
        std::cout << "Successfully powered up the sensors" << std::endl;

    } catch (const std::runtime_error& e) {
        std::cout << "Powering up the sensors did not work and caught runtime exception: "
        << e.what() << std::endl;

    } catch (const std::exception& e) {
        std::cout << "Powering up the sensors did not work and caught exception: "
        << e.what() << std::endl;
    }

    

    return 0;
}
