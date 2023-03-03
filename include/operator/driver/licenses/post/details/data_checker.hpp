#ifndef OPERATOR_DRIVER_LICENSES_POST_DETAILS_DATA_CHECKER_HPP_
#define OPERATOR_DRIVER_LICENSES_POST_DETAILS_DATA_CHECKER_HPP_

#include "operator/driver/licenses/post/context.hpp"
#include "api/obspher/operator/driver/licenses/post/errors.hpp"

#include "service_security/retreiver/user.hpp"

#include <vector>

namespace operator_::driver::licenses::post
{
    namespace details
    {
        struct data_checker final
        {
            public:
                explicit data_checker(const operator_::driver::licenses::context& context, ::database::mysql::context& mysql_context) : 
                _context{std::cref(context)},
                _user_retreiver{mysql_context}
                {}

                std::vector<unsigned int> licenses_exists(const std::vector<std::string>& licenses) const
                {
                    std::vector<unsigned int> ids{};
                    ids.reserve(licenses.size());

                    for(const std::string& license : licenses)
                    {
                        auto id = license_exists(license);
                        if(!id.has_value())
                        {
                            throw api::obspher::operator_::driver::licenses::post::contract_doesnt_exist("Contract " + license + " doesn't exist");
                        }

                        ids.emplace_back(id.value());
                    }

                    return ids;
                }

                unsigned int driver_exist(const std::string& id_driver) const
                {
                   auto driver = _user_retreiver.retreive(
                        ::database::mysql::clause<std::pair<sql::model::obspher::professional_users, sql::model::obspher::professional_users::driver_id>>{}.not_null() and
                        ::database::mysql::clause<std::pair<sql::model::obspher::users, sql::model::obspher::users::uuid>>{} == id_driver
                    );

                    if(!driver.has_value())
                    {
                        throw api::obspher::operator_::driver::licenses::post::driver_not_found("Driver not found");
                    }

                    return driver.value().registered().value().professional_().value().driver_().value().sql_id();
                }

            private:
                std::optional<unsigned int> license_exists(const std::string& license) const
                {
                    auto query = ::database::mysql::query
                    <std::pair<licenses_t, licenses_t::id>>{}
                    .from<licenses_t>(_context.get().licenses_table())
                    .where(database::mysql::clause<std::pair<licenses_t, licenses_t::name_>>{} == license);

                    try
                    {
                        return std::get<0>(query.single()).value();
                    }
                    catch(const std::exception& e)
                    {
                        return {};
                    }
                }

            private:
                std::reference_wrapper<operator_::driver::licenses::context const> _context;
                service_security::retreiver::user _user_retreiver;

                using licenses_t = sql::model::obspher::license;
        };
    }
}

#endif