/*  Copyright (C) 2013-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_CORE_PERMUTE_BYTES16_H
#define LIBSIMDPP_SIMDPP_CORE_PERMUTE_BYTES16_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/insn/permute_bytes16.h>

namespace simdpp {
namespace SIMDPP_ARCH_NAMESPACE {

/// @{
/** Selects bytes from a vector according to a mask. Each byte within the
    mask defines which element to select:
     * Bits 7-4 must be zero or the behavior is undefined
     * Bits 3-0 define the element within the given vector.

    @par 128-bit version:
    @unimp{SSE2-SSE3}
    @icost{NEON, 2}

    @par 256-bit version:
    The vectors will be shuffled as if the 128-bit version was applied to the
    lower and higher halves of the vectors separately.

    @unimp{SSE2-SSE3}
    @icost{SSSE3-AVX, ALTIVEC, 2}
    @icost{NEON, 4}
*/
template<unsigned N> SIMDPP_INL
uint8<N> permute_bytes16(const uint8<N>& a, const uint8<N>& mask)
{
    return detail::insn::i_permute_bytes16(a, mask);
}
template<unsigned N> SIMDPP_INL
uint16<N> permute_bytes16(const uint16<N>& a, const uint16<N>& mask)
{
    return detail::insn::i_permute_bytes16(a, mask);
}
template<unsigned N> SIMDPP_INL
uint32<N> permute_bytes16(const uint32<N>& a, const uint32<N>& mask)
{
    return detail::insn::i_permute_bytes16(a, mask);
}
template<unsigned N> SIMDPP_INL
uint64<N> permute_bytes16(const uint64<N>& a, const uint64<N>& mask)
{
    return detail::insn::i_permute_bytes16(a, mask);
}
template<unsigned N> SIMDPP_INL
float32<N> permute_bytes16(const float32<N>& a, const uint32<N>& mask)
{
    return detail::insn::i_permute_bytes16(a, mask);
}
template<unsigned N> SIMDPP_INL
float64<N> permute_bytes16(const float64<N>& a, const uint64<N>& mask)
{
    return detail::insn::i_permute_bytes16(a, mask);
}
/// @}

} // namespace SIMDPP_ARCH_NAMESPACE
} // namespace simdpp

#endif

