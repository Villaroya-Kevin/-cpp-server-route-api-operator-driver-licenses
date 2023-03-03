#include "operator/driver/licenses/post/handler.hpp"
#include "operator/driver/licenses/post/accessor/configuration.hpp"

namespace operator_::driver::licenses::post
{
    endpoint::endpoint(
        cppserver::configuration const &c,
        std::vector <std::shared_ptr<virtual_endpoint>> const &e
    ) :
    cppserver::endpoint<endpoint,cppserver::middleware::authorization_bearer<details::granter>>{c, e},
    _mysql_context{
        accessor::configuration::mysql_uri(c), 
        accessor::configuration::mysql_port(c),
        "operator::driver::licenses::post",
        std::string{credentials::mysql_user()},
        std::string{credentials::mysql_pwd()}
    },
    _context{_mysql_context},
    _license_driver_registerer(_context),
    _data_checker{_context, _mysql_context}
    {}

    endpoint::outputs_t endpoint::process(auto &&, inputs_t const &params) const // cppcheck-suppress  unusedFunction
    {
        auto license_ids = _data_checker.licenses_exists(params.licenses);
        auto driver_id = _data_checker.driver_exist(params.driver_id);

        _license_driver_registerer.register_(driver_id, license_ids);

        outputs_t response;
        return response;
    }
}