/**
    * Project: ICP 2022/23
    *
    * @brief Customized exception
    * @file exception.h
    * @author Daniel Zarsky <xzarsk04@stud.fit.vutbr.cz>
    * @date 22/4/2023
    */
#ifndef ICP_EXCEPTION_H
#define ICP_EXCEPTION_H

#include <stdexcept>

/**
 * Class for handling exceptions
 */
class Exception : public std::exception {
    public:
        char * err_message; ///error message to show

        Exception(char * str) : err_message(str) {}
        char * show () { ///propagating the error message
            return err_message;
        }
};
#endif //ICP_EXCEPTION_H
