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

#include "mlio/init.h"

#include <memory>

#include "mlio/logger.h"
#include "mlio/memory/file_backed_memory_allocator.h"
#include "mlio/memory/memory_allocator.h"

namespace mlio {
inline namespace abi_v1 {

void initialize()
{
    static bool initialized{};
    if (initialized) {
        logger::warn("MLIO is already initialized.");

        return;
    }

    set_memory_allocator(std::make_unique<File_backed_memory_allocator>());

    initialized = true;
}

}  // namespace abi_v1
}  // namespace mlio
