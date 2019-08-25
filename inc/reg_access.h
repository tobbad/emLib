/*
 * reg_access.h
 *
 *  Created on: 23.02.2018
 *      Author: badi
 */

#ifndef INC_REG_ACCESS_H_
#define INC_REG_ACCESS_H_

#include "config.h"

namespace common
{
    template<
       const mcal::addr_type address,
       uint8_t up_shift=0,
       mcal::reg_type mask=sizeof(mcal::reg_type)-1>
    class reg
    {
    public:
        mcal::reg_type operator=(mcal::reg_type value) { return *reinterpret_cast<volatile mcal::reg_type*>(address)  = value;}
        mcal::reg_type operator&(mcal::reg_type value) { return *reinterpret_cast<volatile mcal::reg_type*>(address) & value;}
        mcal::reg_type operator&=(mcal::reg_type value) { return *reinterpret_cast<volatile mcal::reg_type*>(address) &= value;}
        mcal::reg_type operator|(mcal::reg_type value) { return *reinterpret_cast<volatile mcal::reg_type*>(address) | value;}
        mcal::reg_type operator|=(mcal::reg_type value) { return *reinterpret_cast<volatile mcal::reg_type*>(address) |= value;}
        mcal::reg_type operator~() { return ~(*reinterpret_cast<volatile mcal::reg_type*>(address)); }
        mcal::reg_type value() {return (*reinterpret_cast<volatile mcal::reg_type*>(address));};
#if 0
        static reg_type get() { return *reinterpret_cast<volatile reg_type*>(address); }
        template<const reg_type mask_value>
        static void     reg_msk(reg_type value=0)
        {
            *reinterpret_cast<volatile reg_type*>(address) = reg_type(reg_type(get() & reg_type(~mask_value)) | reg_type(value & mask_value));
        }

        static void     bset(const reg_type value=0) { *reinterpret_cast<volatile reg_type*>(address) |= static_cast<reg_type>(1UL << value); }
        static void     bclr(const reg_type value=0) { *reinterpret_cast<volatile reg_type*>(address) &= static_cast<reg_type>(~static_cast<reg_type>(1UL << value)); }
        static void     bnot(const reg_type value=0) { *reinterpret_cast<volatile reg_type*>(address) ^= static_cast<reg_type>(1UL << value); }
        static bool     bget(const reg_type value=0) { return (static_cast<volatile reg_type>(get() & static_cast<reg_type>(1UL << value)) != static_cast<reg_type>(0U)); }
#endif
    };
}




#endif /* INC_REG_ACCESS_H_ */
