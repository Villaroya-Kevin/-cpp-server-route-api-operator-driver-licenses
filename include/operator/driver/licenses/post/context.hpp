#ifndef OPERATOR_DRIVER_LICENSES_CUSTOMER_CONTEXT_HPP_
#define OPERATOR_DRIVER_LICENSES_CUSTOMER_CONTEXT_HPP_

#include "database/mysql.hpp"
#include "sql/model/obspher.hpp"

#include "operator/driver/licenses/post/accessor/configuration.hpp"

namespace operator_::driver::licenses
{
    struct context final
    {
        public:
            explicit context(const database::mysql::context& mysql_context) :
            _licenses_table{database::mysql::table::create<sql::model::obspher::license>(mysql_context)},
            _has_license_table{database::mysql::table::create<sql::model::obspher::has_license>(mysql_context)}
            {}

            const database::mysql::table& licenses_table() const{return _licenses_table;}
            const database::mysql::table& has_license_table() const{return _has_license_table;}

        private:
            database::mysql::table _licenses_table;
            database::mysql::table _has_license_table;
    };
}


#endif