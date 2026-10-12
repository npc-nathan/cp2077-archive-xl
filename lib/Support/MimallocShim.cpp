// Build shim, not upstream code.
//
// TiltedCore.lib (pulled in by the `tiltedcore` xmake package) references the symbol
// `mi_malloc_size`, but the mimalloc build that the package links does not export it —
// in mimalloc 3.x the POSIX-compat alias is provided from `mi_usable_size`, which *is*
// exported. mimalloc's own definition of mi_malloc_size is exactly this forwarding call,
// so defining it here restores the link without changing behaviour.
//
// Added only to make the local test build of commit b933859 link; delete freely.

#include <cstddef>

extern "C" size_t mi_usable_size(const void* p) noexcept;

extern "C" size_t mi_malloc_size(const void* p) noexcept
{
    return mi_usable_size(p);
}
