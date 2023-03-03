#ifndef _OPERATOR_DRIVER_LICENSES_POST_DATABASE_USER_REGISTERER_HPP_
#define _OPERATOR_DRIVER_LICENSES_POST_DATABASE_USER_REGISTERER_HPP_

#include "api/obspher/operator/driver/licenses/post/inputs.hpp"
#include "operator/driver/licenses/post/context.hpp"

#include "boost/date_time/gregorian/gregorian.hpp"

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>

#include "database/mysql.hpp"

#include <string>
#include <optional>

namespace operator_::driver::licenses
{
    namespace database
    {
        struct license_driver_registerer final
        {

            public:
                explicit license_driver_registerer(context const& c) :
                    _context{std::cref(c)}
                {}

                void register_(
                    unsigned int driver_id,
                    std::vector<unsigned int> licenses_id
                ) const
                {
                    for(unsigned int license_id : licenses_id)
                    {
                        try
                        {
                            ::database::mysql::insert<has_license_t>{_context.get().has_license_table()}
                            .column<has_license_t::driver_id>(driver_id)
                            .column<has_license_t::license_id>(license_id)
                            .column<has_license_t::uuid>(boost::uuids::to_string(boost::uuids::random_generator{}()))
                            .column<has_license_t::obtain_date>(boost::gregorian::date(boost::gregorian::day_clock::universal_day()))
                            ();
                        }
                        catch(const std::exception& e)
                        {
                            throw api::obspher::operator_::driver::licenses::post::driver_has_already_license("Driver has already license"); 
                        }
                    }
                }

            private:
                std::reference_wrapper<context const> _context;

                using has_license_t = sql::model::obspher::has_license;
        };
    }
}

#endif