#pragma once

#include <cstdint>
#include <span>
#include <vector>

enum class EntryDeletionStatus : uint8_t { Not, Soft, Hard };

class Entry {
  [[nodiscard]] std::unique_ptr<uint8_t[]> encode() const;
  explicit Entry(std::span<uint8_t> &data); // construct entry from encoded data

private:
  EntryDeletionStatus del_status_;
  std::string hash_;
  std::vector<std::string> volumes_;
};
