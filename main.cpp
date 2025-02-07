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

    // Power up sensor
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
    
    // Read calibrations
    // es kann immer nur 1 mal pro Sensor die Konfiguration abgefragt werden
    try {
        
        // auto calib_1 = std::get<0>(get_calibration(Sensor::lidar,      sensor_names[0]));
        // auto calib_2 = std::get<0>(get_calibration(Sensor::radar,      sensor_names[1]));
        // auto calib_3 = std::get<0>(get_calibration(Sensor::ultrasonic, sensor_names[2]));
        // auto calib_4 = std::get<0>(get_calibration(Sensor::pressure,   sensor_names[3]));
        
        auto val_1 = std::get<1>(get_calibration(Sensor::lidar,      sensor_names[0]));
        auto val_2 = std::get<1>(get_calibration(Sensor::radar,      sensor_names[1]));
        auto val_3 = std::get<1>(get_calibration(Sensor::ultrasonic, sensor_names[2]));
        auto val_4 = std::get<1>(get_calibration(Sensor::pressure,   sensor_names[3]));
        
        std::cout << "Calibrations:\n"
            << /*calib_1 <<*/ "\t" << val_1 << "\n" 
            << /*calib_2 <<*/ "\t" << val_2 << "\n"
            << /*calib_3 <<*/ "\t" << val_3 << "\n"
            << /*calib_4 <<*/ "\t" << val_4 << "\n"
            << std::endl;
    
    } catch (const std::runtime_error& e) {
        std::cout << "Reading calibration did not work and caught runtime exception: "
        << e.what() << std::endl;

    } catch (const std::exception& e) {
        std::cout << "Reading calibration did not work and caught exception: "
        << e.what() << std::endl;
    }
    
    return 0;
}
