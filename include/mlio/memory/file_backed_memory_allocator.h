/*
 * Copyright 2019-2020 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"). You
 * may not use this file except in compliance with the License. A copy of
 * the License is located at
 *
 *      http://aws.amazon.com/apache2.0/
 *
 * or in the "license" file accompanying this file. This file is
 * distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF
 * ANY KIND, either express or implied. See the License for the specific
 * language governing permissions and limitations under the License.
 */

#pragma once

#include <cstddef>

#include "mlio/config.h"
#include "mlio/fwd.h"
#include "mlio/intrusive_ptr.h"
#include "mlio/memory/memory_allocator.h"

namespace mlio {
inline namespace abi_v1 {

/// @addtogroup memory Memory
/// @{

/// Represents a memory allocator that returns File-mapped memory
/// blocks when the requested size is greater than a threshold.
class MLIO_API File_backed_memory_allocator final : public Memory_allocator {
public:
    /// @param oversize_threshold
    ///     Any allocation exceeding the threshold will be served from
    ///     a File-mapped memory region instead of the process heap.
    ///     If the threshold is zero, the actual threshold will be
    ///     determined dynamically based on the available physical
    ///     memory of the system.
    explicit File_backed_memory_allocator(std::size_t oversize_threshold = 0) noexcept;

    Intrusive_ptr<Mutable_memory_block> allocate(std::size_t size) final;

private:
    std::size_t oversize_threshold_{};
};

/// @}

}  // namespace abi_v1
}  // namespace mlio
