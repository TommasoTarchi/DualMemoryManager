#include "../include/private/abort_manager.hpp"
#include <iostream>

// TODO: maybe add MPI
// TODO: add description
void abort_manager(const std::string message) {

  /* return abort message */
  std::cerr << "DualMemoryManager error: " << message << std::endl;

  /* exit program */
  exit(1);

  return;
}
