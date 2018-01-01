#include "factorio/mod-info.hpp"
namespace factorio
{
namespace mod
{
  bool operator == (const info& lhs, const info& rhs)
  {
    return lhs.id() == rhs.id();
  }
} // namespace mod
} // namespace factorio
