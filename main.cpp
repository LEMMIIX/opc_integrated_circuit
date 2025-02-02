#include <stdexcept>
#include <iostream>
#include <ctime>

#include "opcpp_ic.h"

/// @brief Starting the program simulates a start of the circuit which means this bool MUST be set as TRUE
const bool& system_is_powered_up{true};

int main(int argc, char const *argv[])
{
    try {
        std::cout << "Attempting to power up the sensor..." << std::endl;
        power_up_sensor(Sensor::radar, "pipi");
        std::cout << "Successfully powered up the sensor" << std::endl;

    } catch (const std::runtime_error& e) {
        std::cout << "Powering up the sensor did not work and caught runtime exception: "
        << e.what() << std::endl;

    } catch (const std::exception& e) {
        std::cout << "Powering up the sensor did not work and caught exception: "
        << e.what() << std::endl;
    }

    return 0;
}
