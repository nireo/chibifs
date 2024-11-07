#include "entry.h"
#include <cstring>
#include <memory>

std::unique_ptr<uint8_t[]> Entry::encode() const {
  // del status, hash_len+size, vol_count
  size_t size = 1 + (4 + hash_.size()) + 4;
  for (const auto &vol : volumes_) {
    size += 4 + vol.size();
  }

  size_t curr = 0;
  std::unique_ptr<uint8_t[]> buffer(new std::uint8_t[size]);
  std::memcpy(&buffer.get()[curr], &del_status_, sizeof(uint8_t));
  curr += 1;

  uint32_t hash_len = static_cast<uint32_t>(hash_.size());
  std::memcpy(&buffer.get()[curr], &hash_len, sizeof(uint32_t));
  curr += 4;
  std::memcpy(&buffer.get()[curr], hash_.data(), hash_.size());
  curr += hash_.size();

  uint32_t vol_count = static_cast<uint32_t>(volumes_.size());
  std::memcpy(&buffer.get()[curr], &vol_count, sizeof(uint32_t));
  curr += 4;

  for (const auto &vol : volumes_) {
    uint32_t vol_len = static_cast<uint32_t>(vol.size());
    memcpy(&buffer.get()[curr], &vol_len, sizeof(uint32_t));
    curr += 4;

    std::memcpy(&buffer.get()[curr], vol.data(), vol.size());
    curr += vol.size();
  }

  return buffer;
}
