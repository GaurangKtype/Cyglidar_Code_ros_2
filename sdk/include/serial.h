#ifndef __SERIAL_H
#define __SERIAL_H

#include <boost/asio.hpp>
#include <cmath>
#include <thread>
#include <iostream>
#include <string>

#include "cygparser.h"
#include "d_series_constant.h"

#define SCAN_MAX_SIZE 20000
#define PULSE_AUTO    0
#define PULSE_MANUAL  1

enum eRunMode
{
    Mode2D,
    Mode3D,
    ModeDual
};

class cyglidar_serial
{
    public:
        /**
            * @brief Construct CygLiDAR attached to the given serial port
            * @param port_ The string for the serial port device to attempt to connect to, e.g. "/dev/ttyUSB0"
            * @param baud_rate_ The baud rate to open the serial port at
            * @param io_ Boost ASIO IO Service to use when creating the serial port object
            */
        cyglidar_serial(const std::string& port_, uint32_t baud_rate_, boost::asio::io_service& io_);

        /**
            * @brief Default destructor
            */
        ~cyglidar_serial()
        {
            serial.close();
        }

        /**
            * @brief Poll the laser to get a new scan. Block until a complete new scan is received or close is called.
            */
        uint16_t getPacketLength(uint8_t* output_buffer_, const int buffer_size_);

        /**
            * @brief Send a packet to run CygLiDAR
            */
        std::string requestRunMode(const eRunMode run_mode_);

        /**
            * @brief Send a packet to change a width of the pulse
            */
        void requestDurationControl(const eRunMode run_mode_, const int duration_mode_, const uint16_t duration_value_);

        /**
            * @brief Send a packet to assign a frequency level
            */
        void requestFrequencyChannel(const uint8_t channel_number_);

        /**
            * @brief Send a packet to get a device information
            */
        void requestDeviceInfo();

        /**
            * @brief Send a packet to change baud rate setting
            */
        void requestSerialBaudRate(const uint8_t _select_baud_rate);

        /**
            * @brief Close the driver down and prevent the polling loop from advancing
            */
        void close();

    private:
        std::string port;                ///< @brief The serial port which the driver belongs to
        uint32_t baud_rate;              ///< @brief The baud rate for the serial connection
        boost::asio::serial_port serial; ///< @brief Actual serial port object for reading/writing to the lidar Scanner
        uint8_t command_buffer[20];
        uint8_t payload_buffer[10];
        void makeCommand(uint8_t* command_buffer_, uint8_t* payload_, const uint16_t payload_size_);
};
#endif
