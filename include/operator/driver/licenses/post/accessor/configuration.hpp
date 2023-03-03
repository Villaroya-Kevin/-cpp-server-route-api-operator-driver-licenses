#ifndef _OPERATOR_DRIVER_LICENCES_POST_ACCESSOR_CONFIGURATION_HPP_
#define _OPERATOR_DRIVER_LICENCES_POST_ACCESSOR_CONFIGURATION_HPP_

#include "cppserver/configuration.hpp"
#include "cppserver/casters.hpp"
#include <string>

namespace operator_::driver::licenses::post
{
    namespace accessor
    {
        struct configuration final
        {
            inline static std::string mysql_uri(cppserver::configuration const& conf)
            {
                return conf.get_value<std::string, 3>({"databases", "mysql", "uri"});
            }
            inline static unsigned short mysql_port(cppserver::configuration const& conf)
            {
                return conf.get_value<unsigned short, 3>({"databases", "mysql", "port"});
            }
        };
    }
}

#endif