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
#include <string>
#include <unordered_set>
#include <vector>

#include <mlio.h>

#include "column_statistics.h"

namespace pymlio {

class Column_analyzer {
public:
    Column_analyzer(std::vector<Column_analysis> &columns,
                    const std::vector<std::string> &null_like_values,
                    const std::unordered_set<std::size_t> &capture_columns,
                    std::size_t max_capture_count) noexcept;

public:
    void analyze(const mlio::Example &example) const;

private:
    std::vector<Column_analysis> *columns_;
    std::vector<std::string> const *null_like_values_;
    std::unordered_set<std::size_t> const *capture_columns_;
    std::size_t max_capture_count_;
};

}  // namespace pymlio
