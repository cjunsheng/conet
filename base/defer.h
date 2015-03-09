/*
 * =====================================================================================
 *
 *       Filename:  defer.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年03月09日 15时54分04秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  piboye
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef __CONET_DEFER_H__
#define __CONET_DEFER_H__

//  gcc 必须定义这个， 不然会定义为 0, 导致 BOOST_PP_VARIADIC_TO_SEQ 用不了
#define BOOST_PP_VARIADICS 1

#include "boost/preprocessor.hpp"


#define CONET_DEFER_DECL_TYPEOF(r, data,  a) typedef typeof(a) BOOST_PP_CAT(typeof_, a) ;
#define CONET_DEFER_IMPL_REF_TYPE(r, data, a) BOOST_PP_CAT(typeof_,a) &a;

#define CONET_DEFER_PARAM_DEF(r1, data, i, a) BOOST_PP_COMMA_IF(i) BOOST_PP_CAT(typeof_,a) & BOOST_PP_CAT(a,r)
#define CONET_DEFER_PARAM_INIT(r1, data, i, a) BOOST_PP_COMMA_IF(i) a(BOOST_PP_CAT(a,r))


#define CONET_DEFER(param, op)  \
BOOST_PP_SEQ_FOR_EACH(CONET_DEFER_DECL_TYPEOF, data, BOOST_PP_VARIADIC_TO_SEQ param) \
struct __conet_defer_t_##__LINE__ \
{ \
    BOOST_PP_SEQ_FOR_EACH(CONET_DEFER_IMPL_REF_TYPE, data, BOOST_PP_VARIADIC_TO_SEQ param) \
    explicit \
    __conet_defer_t_##__LINE__ \
    (\
        BOOST_PP_SEQ_FOR_EACH_I(CONET_DEFER_PARAM_DEF, data, BOOST_PP_VARIADIC_TO_SEQ param) \
    ) :\
        BOOST_PP_SEQ_FOR_EACH_I(CONET_DEFER_PARAM_INIT, data, BOOST_PP_VARIADIC_TO_SEQ param) \
	{}\
    \
    ~__conet_defer_t_##__LINE__()\
    op  \
}  \
__conet_defer_var_##__LINE__ param \


#endif /* end of include guard */

