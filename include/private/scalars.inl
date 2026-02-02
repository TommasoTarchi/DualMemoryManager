/**
 * @file allocate.inl
 *
 * @brief Definition of method for managing dual scalars.
 */

#pragma once

namespace MiMMO {

/**
 * @brief Creates a dual scalar.
 *
 * @details
 * This function creates a scalar variable on host and optionally on
 * device (allocating a one-element array), and assigns the requested
 * value. It returns an object of type DualScalar that contains the host
 * value and the device pointer.
 *
 * @param dual_scalar Dual scalar to be created.
 * @param label       Label that should be used to track the scalar in
 *                    memory.
 * @param value       Value to which the scalar should be initialized.
 * @param on_device   Whether the scalar should be created on device as
 *                    well (ignored if main code compiled without OpenACC
 *                    support).
 */
template <typename T>
void DualMemoryManager::create_scalar(DualScalar<T> &dual_scalar,
                                      const std::string label, const T value,
                                      const bool on_device) {

  /* define value on host */
  dual_scalar.host_value = value;

  /* if required, allocate memory on device */
#ifdef _OPENACC
  if (on_device) {
    dual_scalar.dev_ptr = (T *)acc_malloc(sizeof(T));

    if (!(dual_scalar.dev_ptr)) {
      abort_mimmo("Failed to allocate device memory.");
    }

  } else {
    dual_scalar.dev_ptr = nullptr;
  }
#else
  dual_scalar.dev_ptr = nullptr;
#endif // _OPENACC

  /* copy data from host to device */
#ifdef _OPENACC
  if (on_device)
    acc_memcpy_to_device(dual_scalar.dev_ptr, &(dual_scalar.host_value),
                         sizeof(T));
#endif // _OPENACC

  /* update memory tracker */
#ifdef _OPENACC
  const bool ret =
      add_to_memory_tracker(memory_tracker, total_memory, (void *)&dual_scalar,
                            label, sizeof(T), on_device);
#else
  const bool ret =
      add_to_memory_tracker(memory_tracker, total_memory, (void *)&dual_scalar,
                            label, sizeof(T), false);
#endif // _OPENACC

  if (ret)
    abort_mimmo("Failed to track memory for dual scalar '" + label + "'.");

  return;
}

/**
 * @brief Updates the value of a dual scalar from host to device.
 *
 * @details
 * This function updates the value of a dual scalar from host to device.
 *
 * If the scalar is not present on device, the program aborts.
 *
 * **Warning**: the scalar must have been previously created using the
 * create_scalar() method.
 *
 * @param dual_scalar Dual scalar to synchronize.
 */
template <typename T>
void DualMemoryManager::update_scalar_host_to_device(
    DualScalar<T> &dual_scalar) {

#ifdef _OPENACC
  /* check that device pointer is initialized */
  if (dual_scalar.dev_ptr == nullptr)
    abort_mimmo("Device pointer of dual scalar is a null pointer.");

  /* copy data from host to device */
  acc_memcpy_to_device(dual_scalar.dev_ptr, (void *)&dual_scalar, sizeof(T));
#endif // _OPENACC

  return;
}

/**
 * @brief Updates the value of a dual scalar from device to host.
 *
 * @details
 * This function updates the value of a dual scalar from device to host.
 *
 * If the scalar is not present on device, the program aborts.
 *
 * If OpenACC is not enabled, this function does nothing.
 *
 * **Warning**: the scalar must have been previously created using the
 * create_scalar() method.
 *
 * @param dual_scalar Dual scalar to synchronize.
 */
template <typename T>
void DualMemoryManager::update_scalar_device_to_host(
    DualScalar<T> &dual_scalar) {

#ifdef _OPENACC
  /* check that device pointer is initialized */
  if (dual_scalar.dev_ptr == nullptr)
    abort_mimmo("Device pointer of dual scalar is a null pointer.");

  /* copy data from host to device */
  acc_memcpy_from_device(&dual_scalar.host_value, dual_scalar.dev_ptr,
                         sizeof(T));
#endif // _OPENACC

  return;
}

/**
 * @brief Frees memory allocated on device for a given scalar.
 *
 * @details
 * This function frees memory allocated on device for a given dual
 * scalar.
 *
 * If the scalar is not tracked (i.e. was not allocated using this
 * memory manager, or it was already freed), the program aborts.
 *
 * If OpenACC is not enabled, this function does nothing.
 *
 * @param dual_scalar Dual scalar to be destroyed.
 */
template <typename T>
void DualMemoryManager::destroy_scalar(DualScalar<T> &dual_scalar) {

  /* check that scalar was actually recorded and update memory
   * tracker
   * */
  const bool ret = remove_from_memory_tracker(memory_tracker, total_memory,
                                              (void *)&dual_scalar);
  if (ret) {
    abort_mimmo("Dual scalar was not found by memory manager.");
  }

  /* free memory on device */
#ifdef _OPENACC
  if (dual_scalar.dev_ptr != nullptr) {
    acc_free(dual_scalar.dev_ptr);
    dual_scalar.dev_ptr = nullptr;
  }
#endif // _OPENACC

  return;
}

} // namespace MiMMO
