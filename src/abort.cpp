/**
 * @file abort.cpp
 *
 * @brief Implementation of functions for aborting the memory manager.
 */

#include "../include/private/abort.hpp"
#include <iostream>

namespace MiMMO {

// TODO: give more info in error if possible
/**
 * @brief Aborts manager displaying an error message.
 *
 * @details
 * This function aborts the memory manager displaying an error
 * message passed by the user.
 *
 * @param message Error message to be displayed.
 */
void abort_mimmo(const std::string message) {

  /* make sure standard output is flushed */
  std::cout.flush();

  /* return abort message */
  std::cerr << "DualMemoryManager error: " << message << std::endl;

  /* exit program */
  exit(1);

  return;
}

} // namespace MiMMO
