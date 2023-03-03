#ifndef OPERATOR_DRIVER_LICENSES_POST_HPP_
#define OPERATOR_DRIVER_LICENSES_POST_HPP_

#include "api/obspher/server.hpp"
#include "api/obspher/operator/driver/licenses/post/inputs.hpp"
#include "api/obspher/operator/driver/licenses/post/outputs.hpp"
#include "api/obspher/operator/driver/licenses/post/route.hpp"
#include "api/obspher/operator/driver/licenses/post/method.hpp"
#include "api/obspher/operator/driver/licenses/post/writer.hpp"
#include "api/obspher/operator/driver/licenses/post/errors.hpp"

#include "api/obspher/operator/driver/licenses/post/reader.hpp"

#include "operator/driver/licenses/post/details/granter.hpp"
#include "operator/driver/licenses/post/details/data_checker.hpp"
#include "operator/driver/licenses/post/database/license_driver_registerer.hpp"

#include "cppserver/middleware/authorization_bearer.hpp"

#include "accessor/configuration.hpp"

#include "cppserver/endpoint.hpp"

namespace operator_::driver::licenses::post
{
     struct endpoint final : public cppserver::endpoint<endpoint, cppserver::middleware::authorization_bearer<details::granter>>
     {
        public:
            using server_t = api::obspher::server;

            using inputs_t = api::obspher::operator_::driver::licenses::post::inputs;
            using outputs_t = api::obspher::operator_::driver::licenses::post::outputs;

            using route_t = api::obspher::operator_::driver::licenses::post::route;
            using method_t = api::obspher::operator_::driver::licenses::post::method;

            template<class ContentType>
            using writer_t = api::obspher::operator_::driver::licenses::post::writer<ContentType>;

            template<class ContentType>
            using reader_t = api::obspher::operator_::driver::licenses::post::reader<ContentType>;


            endpoint(
                cppserver::configuration const &c,
                std::vector <std::shared_ptr<virtual_endpoint>> const &e
            );

            outputs_t process(auto &&middlewares_results, inputs_t const &) const;

        private:
            ::database::mysql::context _mysql_context;
            context _context;
            database::license_driver_registerer _license_driver_registerer;
            details::data_checker _data_checker;
    };
}

#endif