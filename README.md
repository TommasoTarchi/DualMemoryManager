# MiMMO

**WARNING**: This library is still under development, and many of its features are still to be tested.

**WARNING**: Compilation for GPU is not available with CMake yet, it will be soon.

**WARNING**: This README is still to be completed

MiMMO (Minimal Memory Manager for Openacc) is a simple, safe, easy to use CPU/GPU memory manager to work
with OpenACC.

The pragma-based approach of OpenACC is extremely useful, however it only allows for a very high-level
management of host and device memory, and it is often confusing for those who like to understand what is
happening behind the curtain.

MiMMO aims to allow the users to have a finer control over memory allocations and movements, while keeping
it simple and safe.

Under the hood, MiMMO uses the OpenACC runtime API; however, it hides it completely, allowing the user to
write clean code for both host and device.

The manager also keeps track of all memory allocations on host and device, and reports can be requested at
any time.

## Table of Contents
- [Requirements](#requirements)
- [Building and Testing](#building-and-testing)
- [Usage](#usage)
- [API Reference](#api-reference)
- [Contributing](#contributing)
- [License](#license)

## Requirements

## Building and Testing

### Generate documentation

## Usage

The library's API is contained in a namespace called `MiMMO`.

The library works with so called "dual arrays", i.e. data structures containing host and device
pointers of the array, in addition to the number of elements, the size in bytes and the label
used by the memory manager to track the array.

### Sample code

## API Reference

The following is a list of all features available in the MiMMO API. For a more detailed description
of them, please see the Doxygen documentation (see #generate-documentation for how to generate it).

### Data structures

- `DualArray`: dual array data structure; it contains the following fields:
  - `host_ptr`: pointer to array memory on host;
  - `dev_ptr`: pointer to array memory on device;
  - `label`: label used to track dual array memory;
  - `num_elements`: number of elements in array;
  - `size`: size of array in bytes.

### Classes

- `DualMemoryManager`: memory manager that can be used to manage dual arrays; the following methods
  are made available:
  - `allocate()`: allocate requested memory on host and (optionally) on device;
  - `copy_host_to_device()`: copy array data from host to device;
  - `copy_device_to_host()`: copy array data from device to host;
  - `free()`: free both host and device memory;
  - `report_memory_usage()`: print report of memory usage for both host and device.

### Functions

- `select_ptr()`: function returning the host or device pointer of a dual array depending on
  whether OpenACC is enabled or not; it is thought to be used inside compute regions, to make
  code cleaner and avoid #ifdef's.

## Contributing

## License
