/**
 * @file logger.h
 * @section Logger
 * @name Logger
 * @date 26.4.2023
 */


#ifndef PACMAN_LOGGER_H
#define PACMAN_LOGGER_H

#include <fstream>
#include <QPoint>
#include <vector>
#include "resources.hpp"
#include "Sources.h"
#include "player.h"
#include "ghost.h"

/**
 * @name Logger
 * @brief Representation of logger class, which handle logging and reading from logger files
 * @author Samuel Šimún
 */
class Logger {
public:
    //! @brief Constructor of object
    explicit Logger();

    //! @brief Structure which represent information about one entity in one tik
    struct Log {
        int order{};
        char entity{};
        QPoint position{};
        Sources::Directions direction{};
    };

    /**
     * @brief Method for setting Logger into writing mode
     * @author Samuel Šimún
     * @date 27.4.2023
     */
    void open_file_output();


    /**
     * @brief Method for setting Logger into reading mode
     * @author Samuel Šimún
     * @date 27.4.2023
     */
    void open_file_input();


    /**
     * @brief Method which will in writing mode write map into logger file
     * @author Samuel Šimún
     * @date 27.4.2023
     */
    void add_map_to_file();


    /**
     * @brief Method to be called for add position of ghost into logger file
     * @param int Number which identify which ghost is logged
     * @param QPoint Position of ghost
     * @param Sources::Directions In which direction is ghost moving
     * @author Samuel Šimún
     * @date 2.5.2023
     */
    void add_position_ghost(int, QPoint, Sources::Directions);


    /**
     * @brief Method to be called for add position of player into logger file
     * @param QPoint Position of player
     * @param Sources::Directions In which direction is player moving
     * @author Samuel Šimún
     * @date 2.5.2023
     */
    void add_position_player(QPoint, Sources::Directions);


    /**
     * @brief Method to be called when key is taken from map by player
     * @param QPoint Position of key on map
     * @author Samuel Šimún
     * @date 28.4.2023
     */
    void remove_key(QPoint);


    /**
     * @brief Method which will end log file correctly and close file
     * @author Samuel Šimún
     * @date 27.4.2023
     */
    void end_log();


    /**
     * @brief Method for convert direction from integer
     * @param int Number to be extracted
     * @author Samuel Šimún
     * @date 2.5.2023
     * @return Sources::Directions Converted direction
     */
    static Sources::Directions extract_direction(int);


    /**
     * @brief Method for requesting log set on specific tik
     * @param int tik which will be returned
     * @author Samuel Šimún
     * @date 27.4.2023
     * @return vector<Logger::Log> Set of logs
     */
    std::vector<Logger::Log> get_instruction_by_index(int);

    //! Attribute which count number of log sets
    int order_counter{};

private:

    /**
     * @brief Function which read logs from file and parse it into vector
     * @author Samuel Šimún
     * @date 27.4.2023
     */
    void read_input();

    //! Vector representation of logger file
    std::vector<std::vector<Log>> log_vector;

    //! Pointer to input file
    std::ifstream file_input;

    //! Pointer to output file
    std::ofstream file_output;

};

#endif //PACMAN_LOGGER_H
