/**
 * @file opcpp_ic.h
 * @author Pedro Novo (pedro.novo@w-hs.de)
 * @brief The `opcpp_ic` header offers a series of fantasy functionalities intended for training classes.
        It simulates an integrated circuit (IC) which requires an external boolean `system_is_powered_up`.
        THIS API WAS GIVEN AS A STARTING POINT
 * @version 0.1
 * 
 * @copyright Pedro Novo Copyright (c) 2025
 * 
 */

#ifndef OPCPP_IC_H
#define OPCPP_IC_H

#include <string>
#include <string_view>
#include <tuple>

enum class Sensor
{
    lidar,
    radar,
    ultrasonic,
    pressure,
};

enum class Status
{
    success,
    failure,
    enabled,
    disabled,
};

/**
    @brief
        Fetch a single calibration entry for a given fantasy `sensor_name`.
        Each calibration is a pair of csv key and value sets.
        Can be obtained whether `system_is_powered_up` is `true` or not.

    @details
        Calibration examples:
        {Sensor::lidar, {"yaw,pitch,roll", "0.3,1,0.45"}}
        {Sensor::radar, {"yaw,pitch,roll,sensitivity", "0.3,1,0.45,3"}}
        {Sensor::ultrasonic, {"range,sensitivity", "5,2"}}
        {Sensor::pressure, {"sensitivity", "5"}}

    @throws runtime_error
        If multiple calibrations are requested for a given sensor name and type pair fantasy.

    @param [in] sensor_name
        A sensor name fantasy, eg "XY37".

    @param [in] sensor
        A sensor type fantasy.

    Example:
    @code
    auto cal = get_calibration(Sensor::lidar, "#1");
    // `cal` could look something like:
    // <0>: "yaw,pitch,roll"
    // <1>: "0.3,1,0.45"
    @endcode
 */
std::tuple<std::string, std::string> get_calibration(Sensor sensor, std::string_view sensor_name);

/**
    @brief
        Setup a given sensor. There is a magic chance it will work or not. If you get a
        `Status::failure`, try again.

    @throws runtime_error
        If `system_is_powered_up` is not `true`.

    @param [in] sensor_name
        A sensor name fantasy, eg "XY37".

    @param [in] sensor
        A sensor type fantasy.

    @return
        Either `Status::success` or `Status::failure`.
 */
Status power_up_sensor(Sensor sensor, std::string_view sensor_name);

/**
    @brief
        Before a sensor can be used or shutdown, you need to apply a calibration to it.
        After running this function, the respective sensor will be in `Status::enabled`.

     @param [in] calibration
        An appropriate calibration for the given sensor.

    @param [in] sensor_name
        A sensor name fantasy, eg "XY37".

    @param [in] sensor
        A sensor type fantasy.

    @throws runtime_error
        If the sensor is not powered up.

    @throws runtime_error
        If the calibration is not appropriate.

    @return
        There is no return. If all the requirements were met, the application of the calibration
        is always successful.
 */
void apply_sensor_calibration(Sensor sensor, std::string_view sensor_name, std::string_view calibration);

/**
    @brief
        Set down a given sensor.

    @throws runtime_error
        If the given sensor was not previously in `Status::enabled`.

    @param [in] sensor_name
        A sensor name fantasy, eg "XY37".

    @param [in] sensor
        A sensor type fantasy.

    @return
        There is no return. If all the requirements were met, powering down a sensor
        is always successful.
 */
void power_down_sensor(Sensor sensor, std::string_view sensor_name);

/**
    @brief
        Get a single sensor read.

    @throws runtime_error
        If the given sensor was not previously in `Status::enabled`.

    @param [in] sensor_name
        A sensor name fantasy, eg "XY37".

    @param [in] sensor
        A sensor type fantasy.
 */
const float get_sensor_read(Sensor sensor, std::string_view sensor_name);

/**
    @brief
        Enter test mode debugging mode fantasy. There is a magic chance it will work or not. If you get a
        `Status::failure`, try again. Whenever it fails, even if previously there has been a success entry,
        test mode is reset to `false`. It is up to you to track the test mode status.

    @throws runtime_error
        If `system_is_powered_up` is not `true`.

    @return
        Either `Status::success` or `Status::failure`.
 */
Status enter_test_mode();

/**
    @brief
        Exit test mode debugging mode fantasy.

    @throws runtime_error
        If not previously in test mode.

     @return
        There is no return. If all the requirements were met, exiting test mode
        is always successful.
 */
void exit_test_mode();

/**
    @brief
        Enter JTAG debugging mode fantasy. There is a magic chance it will work or not. If you get a
        `Status::failure`, try again. It is up to you to track the jtag mode status.

    @throws runtime_error
        If `system_is_powered_up` is not `true` or not in test mode.

    @return
        Either `Status::success` or `Status::failure`.
 */
Status enter_jtag();

/**
    @brief
        Exit JTAG debugging mode fantasy.

    @throws runtime_error
        If jtag was not previously in `Status::enabled`.

    @return
        There is no return. If all the requirements were met, exiting jtag mode
        is always successful.
 */
void exit_jtag();

/**
    @brief
        Run a scan test <a href="https://en.wikipedia.org/wiki/Scan_chain">[wiki]</a>.
        If you do not know what it means in real world, worry not, you just need to know that in this
        fantasy you need to be in `jtag` mode to properly run this test. No exception occurs if that is
        not the case, but the result in that case will always be `Status::failure`. Else the result can be
        `Status::success` or `Status::failure` for no particular reason. But a tip: There is a magic chance
        it will work if the configuration is appropriate: just repeat it enough and you should obtain a
        `Status::success`.

    @return
        Either `Status::success` or `Status::failure`.
 */
Status run_scan_test();

/**
    @brief 
        Perform an IC register read.

    @throws runtime_error
        When trying to read from an invalid address or the system is not powered up.

    @param addr 
        The address of the register.

    @returns
        The current register status.
 */
unsigned short read_reg(unsigned short addr);

/**
    @brief 
        Perform an IC register write.

    @throws runtime_error
        When trying to write to a read-only address.

    @param addr 
        The address of the register.

    @param data 
        The data to write to the address. If some fields are read only, those won't be overwritten.
 */
void write_reg(const unsigned short addr, const unsigned short data);

#endif // OPCPP_IC_H