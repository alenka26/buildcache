//--------------------------------------------------------------------------------------------------
// Copyright (c) 2020 Marcus Geelnard
//
// This software is provided 'as-is', without any express or implied warranty. In no event will the
// authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose, including commercial
// applications, and to alter it and redistribute it freely, subject to the following restrictions:
//
//  1. The origin of this software must not be misrepresented; you must not claim that you wrote
//     the original software. If you use this software in a product, an acknowledgment in the
//     product documentation would be appreciated but is not required.
//
//  2. Altered source versions must be plainly marked as such, and must not be misrepresented as
//     being the original software.
//
//  3. This notice may not be removed or altered from any source distribution.
//--------------------------------------------------------------------------------------------------

#include <wrappers/ti_arm_cgt_wrapper.hpp>

#include <base/file_utils.hpp>
#include <base/unicode_utils.hpp>

#include <regex>

namespace bcache {
ti_arm_cgt_wrapper_t::ti_arm_cgt_wrapper_t(const file::exe_path_t& exe_path,
                                           const string_list_t& args)
    : ti_common_wrapper_t(exe_path, args) {
}

bool ti_arm_cgt_wrapper_t::can_handle_command() {
  // Is this the right compiler?
  const auto cmd = lower_case(file::get_file_part(m_exe_path.real_path(), true));
  const std::regex re("armcl.*");
  return std::regex_match(cmd, re);
}

}  // namespace bcache
