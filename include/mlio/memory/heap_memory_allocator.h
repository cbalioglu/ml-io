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

/// Represents a memory allocator that allocates from the process heap.
class MLIO_API Heap_memory_allocator final : public Memory_allocator {
public:
    Intrusive_ptr<Mutable_memory_block> allocate(std::size_t size) final;
};

/// @}

}  // namespace abi_v1
}  // namespace mlio
