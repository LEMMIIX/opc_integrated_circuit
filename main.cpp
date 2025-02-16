/**
 * @file main.cpp
 * @author Lennart C. Moeller (lennartc.moeller@gmail.com)
 * @brief The `main` method handles multiple sensor actions to control the fantasy integrated circuit.  
 */

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
    // via cli

    // ./main.exe name1 name2 name3 name4

    std::cout << "Launching" << std::endl;

    Sensor sensor_types[]{
        Sensor::lidar,
        Sensor::radar,
        Sensor::ultrasonic,
        Sensor::pressure,
    };

    const int sensor_count{sizeof(sensor_types) / sizeof(sensor_types[0])};

    std::string sensor_names[sensor_count];
    for (int i = 0; i < sensor_count; ++i) {
        sensor_names[i] = argv[i + 1];
    }

    std::cout << "Names:" << std::endl;
    for (int i = 0; i < sensor_count; ++i) {
        std::cout << sensor_names[i] << std::endl;
    }

    // Power up sensor
    std::cout << "\nAttempting to power up the sensors..." << std::endl;
    try {
        bool is_powered_up{false};
        for(int i = 0; i < sensor_count; ++i) {
            is_powered_up = false;
            while(!is_powered_up) {
                is_powered_up = (power_up_sensor(sensor_types[i], sensor_names[i]) == Status::success);
            }
            
            std::cout << "Powered up sensor:\t" << sensor_names[i] << std::endl;
        }


        // power_up_sensor(Sensor::lidar,      sensor_names[0]);
        // power_up_sensor(Sensor::radar,      sensor_names[1]);
        // power_up_sensor(Sensor::ultrasonic, sensor_names[2]);
        // power_up_sensor(Sensor::pressure,   sensor_names[3]);
        
        std::cout << "Successfully powered up the sensors" << std::endl;
        
    } catch (const std::runtime_error& e) {
        std::cout << "Powering up the sensors did not work and caught runtime exception: "
        << e.what() << std::endl;
        
    } catch (const std::exception& e) {
        std::cout << "Powering up the sensors did not work and caught exception: "
        << e.what() << std::endl;
    }
    
    std::cout << "\nAttempting to apply sensor calibrations..." << std::endl;
    try {
        apply_sensor_calibration(Sensor::lidar,         sensor_names[0], "123");
        apply_sensor_calibration(Sensor::radar,         sensor_names[1], "123");
        apply_sensor_calibration(Sensor::ultrasonic,    sensor_names[2], "123");
        apply_sensor_calibration(Sensor::pressure,      sensor_names[3], "123");

    } catch (const std::runtime_error& e) {
        std::cout << "Applying calibration tp the sensors did not work and caught runtime exception: "
        << e.what() << std::endl;
        
    } catch (const std::exception& e) {
        std::cout << "Applying calibration to the sensors did not work and caught exception: "
        << e.what() << std::endl;
    }

    // Read calibrations
    // es kann immer nur 1 mal pro Sensor die Konfiguration abgefragt werden
    std::cout << "\nFetching calibrations:" << std::endl;
    try {
        
        auto calib_1 = std::get<0>(get_calibration(Sensor::lidar,      sensor_names[0]));
        auto calib_2 = std::get<0>(get_calibration(Sensor::radar,      sensor_names[1]));
        auto calib_3 = std::get<0>(get_calibration(Sensor::ultrasonic, sensor_names[2]));
        auto calib_4 = std::get<0>(get_calibration(Sensor::pressure,   sensor_names[3]));
        
        // auto val_1 = std::get<1>(get_calibration(Sensor::lidar,      sensor_names[0]));
        // auto val_2 = std::get<1>(get_calibration(Sensor::radar,      sensor_names[1]));
        // auto val_3 = std::get<1>(get_calibration(Sensor::ultrasonic, sensor_names[2]));
        // auto val_4 = std::get<1>(get_calibration(Sensor::pressure,   sensor_names[3]));
        
        std::cout   << calib_1 << "\t"  << /*val_1 << */"\n" 
                    << calib_2 << "\t"  << /*val_2 << */"\n"
                    << calib_3 << "\t"  << /*val_3 << */"\n"
                    << calib_4 << "\t"  /*<< val_4 << "\n"*/
        << std::endl;
        
    } catch (const std::runtime_error& e) {
        std::cout << "Reading calibration did not work and caught runtime exception: "
        << e.what() << std::endl;
        
    } catch (const std::exception& e) {
        std::cout << "Reading calibration did not work and caught exception: "
        << e.what() << std::endl;
    }
    
    std::cout << "\nReading register data" << std::endl;
    try {
        std::cout << read_reg(0x1) << std::endl
        << read_reg(0x2) << std::endl
        << read_reg(0x3) << std::endl;
        
    } catch (const std::runtime_error& e) {
        std::cout << "Reading registers did not work and caught runtime exception: "
        << e.what() << std::endl;
        
    } catch (const std::exception& e) {
        std::cout << "Reading registers did not work and caught exception: "
        << e.what() << std::endl;
    }
    
    std::cout << "\nWriting to register(s)..." << std::endl;
    try {
        const unsigned short data{11111};
        write_reg(0x3, data);
        std::cout << "Wrote to register: " << data << std::endl;
        
    } catch (const std::runtime_error& e) {
        std::cout << "Writing to registers did not work and caught runtime exception: "
        << e.what() << std::endl;
        
    } catch (const std::exception& e) {
        std::cout << "Writing to registers did not work and caught exception: "
        << e.what() << std::endl;
    } 
    
    std::cout << "\nAttempting to enter test mode..." << std::endl;
    bool was_success{false};
    try{
        int attempts{5};
        
        while(!was_success) {
            
            was_success = enter_test_mode() == Status::success;
            
            std::cout << "\tStatus: " << (was_success ? "success" : "failed") << std::endl;
            
        }
    } catch (const std::runtime_error& e) {
        std::cout << "Entering test mode failed and cuaght runtime exception: "
        << e.what() << std::endl;
        
    } catch (const std::exception& e) {
        std::cout << "Entering test mode failed and caught exception: "
        << e.what() << std::endl;
    }  
    
    // entering jtag mode if previous test mode entering was successful
    std::cout << "\nAttempting to jtag mode..." << std::endl;
    if (was_success) {
        try {
            was_success = false;
            
            while(!was_success) {
                
                was_success = enter_jtag() == Status::success;
                
                std::cout << "\tStatus:\t" << (was_success ? "success" : "failed") << std::endl;
                
            }
        } catch (const std::runtime_error& e) {
            std::cout << "Entering jtag mode failed and cuaght runtime exception: "
            << e.what() << std::endl;
            
        } catch (const std::exception& e) {
            std::cout << "Entering jtag mode failed and caught exception: "
            << e.what() << std::endl;
        }
    } else {
        std::cout << "Previous test mode entering was unsuccessfull - SKIPPING jtag entering." << std::endl;
    }
    
    // running scan tests if test mode entering was successful
    std::cout << "\nAttempting to run scan tests..." << std::endl;
    if (was_success) {
        was_success = false;
        
        while(!was_success) {
            
            was_success = run_scan_test() == Status::success;
            
            std::cout << "\tStatus: " << (was_success ? "success" : "failed") << std::endl;
            
        }
    } else {
        std::cout << "Previous test mode entering was unsuccessfull - SKIPPING to run tests." << std::endl;
    }
    
    std::cout << "\nAttempting to exit jtag mode..." << std::endl;
    try {
        exit_jtag();
    } catch (const std::runtime_error& e) {
        std::cout << "Could not exit jtag mode and caught runtime exception: "
        << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Could not exit jtag mode and caught exception: "
        << e.what() << std::endl;
    }
    
    std::cout << "\nAttempting to exit test mode..." << std::endl;
    try {
        exit_test_mode();
    } catch (const std::runtime_error& e) {
        std::cout << "Could not exit test mode and caught runtime exception: "
        << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Could not exit test mode and caught: "
        << e.what() << std::endl;
    }
    
    std::cout << "\nAttempting to power down sensors..." << std::endl;
    try {
        power_down_sensor(Sensor::lidar,      sensor_names[0]);
        power_down_sensor(Sensor::radar,      sensor_names[1]);
        power_down_sensor(Sensor::ultrasonic, sensor_names[2]);
        power_down_sensor(Sensor::pressure,   sensor_names[3]);
    } catch (const std::runtime_error& e) {
        std::cout << "Unable to power down sensor and caught runtime exception: "
            << e.what() << std::endl;
        } catch (const std::exception& e) {
        std::cout << "Unable to power down sensor and caught exception: "
            << e.what() << std::endl;
    }
    
    return 0;
}



/**
 * 
 *      ____    
 *     |".."  \  ,--~ .
 *      ` /`o- '--._  u `
 *     __ (_/'__>  >`\   `
 *    /cc     c '    /  u|
 *   | 	c  _c______ /   '
 *    \      >  >  /  \__\
 *     `\ .______/
 * 
 * 
*/