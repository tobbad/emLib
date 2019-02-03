/*
 * mcal_reg_access_tpl.h
 *
 *  Created on: 04.06.2017
 *      Author: badi
 *
 *  Taken from
 *  Real-Time C++: Efficient Object-Oriented and Template Microcontroller Programming 2nd ed. 2015 Edition
 *  by Christopher Kormanyos
 *
 *  Copyright Christopher Kormanyos 2007 - 2013.
 *  Distributed under the Boost Software License,
 *  Version 1.0. (See accompanying file LICENSE_1_0.txt
 *  or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef INC_MCAL_REG_ACCESS_TPL_H_
#define INC_MCAL_REG_ACCESS_TPL_H_

namespace mcal
{
	namespace reg
	{
		template<
		   typename addr_type,
		   typename reg_type,
		   const addr_type address,
		   const reg_type value = static_cast<reg_type>(0)>
		struct access
		{
			static void     reg_set() { *reinterpret_cast<volatile reg_type*>(address)  = value; }
			static void     reg_and() { *reinterpret_cast<volatile reg_type*>(address) &= value; }
			static void     reg_or () { *reinterpret_cast<volatile reg_type*>(address) |= value; }
			static void     reg_not() { *reinterpret_cast<volatile reg_type*>(address) &= reg_type(~value); }
			static reg_type reg_get() { return *reinterpret_cast<volatile reg_type*>(address); }

			template<const reg_type mask_value>
			static void     reg_msk()
			{
				*reinterpret_cast<volatile reg_type*>(address) = reg_type(reg_type(reg_get() & reg_type(~mask_value)) | reg_type(value & mask_value));
			}

			static void     reg_set(const reg_type new_val) { *reinterpret_cast<volatile reg_type*>(address) = new_val; }

			static void     bit_set() { *reinterpret_cast<volatile reg_type*>(address) |= static_cast<reg_type>(1UL << value); }
			static void     bit_clr() { *reinterpret_cast<volatile reg_type*>(address) &= static_cast<reg_type>(~static_cast<reg_type>(1UL << value)); }
			static void     bit_not() { *reinterpret_cast<volatile reg_type*>(address) ^= static_cast<reg_type>(1UL << value); }
			static bool     bit_get() { return (static_cast<volatile reg_type>(reg_get() & static_cast<reg_type>(1UL << value)) != static_cast<reg_type>(0U)); }
		};
	}
}





#endif /* INC_MCAL_REG_ACCESS_TPL_H_ */
