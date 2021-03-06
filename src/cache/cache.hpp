//--------------------------------------------------------------------------------------------------
// Copyright (c) 2019 Marcus Geelnard
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

#ifndef BUILDCACHE_CACHE_HPP_
#define BUILDCACHE_CACHE_HPP_

#include <base/string_list.hpp>
#include <cache/cache_entry.hpp>
#include <cache/expected_file.hpp>
#include <cache/local_cache.hpp>
#include <cache/remote_cache.hpp>

#include <map>
#include <string>

namespace bcache {
/// @brief An interface to the different caches.
class cache_t {
public:
  /// @brief Perform a direct mode cache lookup.
  /// @param direct_hash The hash of the direct mode cache entry.
  /// @param expected_files Paths to the actual files in the local file system (map from file ID to
  /// an expected file descriptor).
  /// @param allow_hard_links True if we are allowed to use hard links.
  /// @param create_target_dirs True if the target directory of the cached file must be created.
  /// @param[out] return_code The return code of the program.
  /// @returns true if we had a cache hit, otherwise false.
  bool lookup_direct(const std::string& direct_hash,
                     const std::map<std::string, expected_file_t>& expected_files,
                     const bool allow_hard_links,
                     const bool create_target_dirs,
                     int& return_code) noexcept;

  /// @brief Add a new direct mode entry to the cache.
  /// @param direct_hash The hash of the direct mode cache entry.
  /// @param hash The hash of the preprocessor mode cache entry.
  /// @param implicit_input_files A list of implicit input file paths.
  void add_direct(const std::string& direct_hash,
                  const std::string& hash,
                  const string_list_t& implicit_input_files);

  /// @brief Perform a cache lookup.
  /// @param hash The hash of the cache entry.
  /// @param expected_files Paths to the actual files in the local file system (map from file ID to
  /// an expected file descriptor).
  /// @param allow_hard_links True if we are allowed to use hard links.
  /// @param create_target_dirs True if the target directory of the cached file must be created.
  /// @param[out] return_code The return code of the program.
  /// @returns true if we had a cache hit, otherwise false.
  bool lookup(const std::string& hash,
              const std::map<std::string, expected_file_t>& expected_files,
              const bool allow_hard_links,
              const bool create_target_dirs,
              int& return_code) noexcept;

  /// @brief Add a new entry to the cache(s).
  /// @param hash The hash of the cache entry.
  /// @param entry The cache entry description.
  /// @param expected_files Paths to the actual files in the local file system (map from file ID to
  /// an expected file descriptor).
  /// @param allow_hard_links True if we are allowed to use hard links.
  void add(const std::string& hash,
           const cache_entry_t& entry,
           const std::map<std::string, expected_file_t>& expected_files,
           const bool allow_hard_links);

private:
  bool lookup_in_local_cache(const std::string& hash,
                             const std::map<std::string, expected_file_t>& expected_files,
                             const bool allow_hard_links,
                             const bool create_target_dirs,
                             int& return_code);

  bool lookup_in_remote_cache(const std::string& hash,
                              const std::map<std::string, expected_file_t>& expected_files,
                              const bool allow_hard_links,
                              const bool create_target_dirs,
                              int& return_code);

  local_cache_t m_local_cache;
  remote_cache_t m_remote_cache;
};
}  // namespace bcache

#endif  // BUILDCACHE_CACHE_HPP_
