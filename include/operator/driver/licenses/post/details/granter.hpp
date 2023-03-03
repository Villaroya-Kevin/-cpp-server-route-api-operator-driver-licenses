#ifndef OPERATOR_DRIVER_LICENSES_POST_DETAILS_GRANTER_HPP_
#define OPERATOR_DRIVER_LICENSES_POST_DETAILS_GRANTER_HPP_

#include "service_security/model/user.hpp"
#include "service_security/access/granter.hpp"

namespace operator_::driver::licenses::post
{
    namespace details
    {
        struct granter
        {
            public:
                static inline bool has_access(service_security::model::user const& user)
                {
                    return service_security::access::granter::is_operator(
                        user,
                        service_security::model::operator_role::target::drivers,
                        service_security::model::operator_role::action::update,
                        service_security::model::operator_role::scope::full
                    );
                }
        };
    }
}


#endif