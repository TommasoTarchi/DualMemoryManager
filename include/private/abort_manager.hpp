/**
 * @file abort_manager.hpp
 *
 * @brief Declaration of functions for aborting the memory manager.
 */

#pragma once

#include <string>

namespace MiMMO {

/**
 * @brief Aborts manager displaying an error message.
 *
 * @details
 * This function aborts the memory manager displaying an error
 * message passed by the user.
 *
 * @param message Error message to be displayed.
 */
void abort_manager(const std::string);

} // namespace MiMMO
