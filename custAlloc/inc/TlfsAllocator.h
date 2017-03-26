/*
 * TlfsAllocator.h
 *
 *  Created on: 14.01.2015
 *      Author: badi
 */

#ifndef TLFSALLOCATOR_H_
#define TLFSALLOCATOR_H_

#include <cstdint>
#include <cstddef>

namespace emLib
{

    template<typename T>
    class allocator
    {
    public:
        typedef std::size_t         size_type;
        typedef std::ptrdiff_t      difference_type;
        typedef T                   value_type;
        typedef value_type*         pointer;
        typedef const value_type*	const_pointer;
        typedef value_type&         reference;
        typedef const value_type&   const_reference;

        // Construcors
        allocator() noexcept;
        allocator(const allocator&) noexcept;

        template<class U>
        allocator(const allocator<U>&) noexcept;

        // Destructor
        ~allocator() noexcept;

        template<class U>
        struct rebind{ typedef allocator<U> other; };

        size_type max_size() const noexcept;

        pointer address(reference) const;
        const_pointer address(const_reference) const;

        pointer allocate(size_type count,
        		typename allocator<void>::const_pointer hint = 0) const;

        void construct(pointer p, const value_type);

        void deallocate(pointer, size_type);

    };
}

#endif /* TLFSALLOCATOR_H_ */
