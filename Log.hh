/*
 * Project: Boost Logging System
 * File: Log.hh
 * Author: Majid Lashgarian <Majid@Lashgarian.com>
 * Date: March.2015
 * Copuright 2015 Majid Lashgarian
 * under MIT Open source License
 */

#ifndef __LOG_H__
#define __LOG_H__

#include <cassert>
#include <iostream>
#include <fstream>
#include <boost/smart_ptr/shared_ptr.hpp>
#include "null_deleter.hh"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/log/common.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/utility/manipulators/add_value.hpp>
#include <boost/log/attributes/scoped_attribute.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <string.h>

namespace logging = boost::log;
namespace expr = boost::log::expressions;
namespace sinks = boost::log::sinks;
namespace attrs = boost::log::attributes;
namespace src = boost::log::sources;
namespace keywords = boost::log::keywords;



namespace ADRO_LOG 
{
    enum LogLevel
    {
        info  , 
        debug , 
        warning,
        error , 
        critical 
    };
    inline std::ostream& operator<< (std::ostream& strm, LogLevel level)
    {
        static const char* strings[] =
        {
            "   Info   ",
            "   Debug  ",
            "  Warning ",
            "   Error  ",
            " Critical ",
        };

        if (static_cast< std::size_t >(level) < sizeof(strings) / sizeof(*strings))
            strm << strings[level];
        else
            strm << static_cast< int >(level);

        return strm;
    }

}





BOOST_LOG_INLINE_GLOBAL_LOGGER_DEFAULT(g_logger, src::logger_mt); 
BOOST_LOG_ATTRIBUTE_KEYWORD(severity, "Severity", ADRO_LOG::LogLevel);
BOOST_LOG_ATTRIBUTE_KEYWORD(tag_attr, "Tag", std::string);
BOOST_LOG_ATTRIBUTE_KEYWORD(timestamp, "TimeStamp", boost::posix_time::ptime)



namespace LOGGING{
    //Author: Lashgarian 
    //Date: 23.Feb.2015 
    /*!
     * This class print info severity log 
     * with help of boost Log library V2.
     *
     */
    class Info {
        public :
			src::severity_logger< ADRO_LOG::LogLevel > slg;
			std::ostringstream buf; 

			Info(){
                slg.add_attribute("Tag", attrs::constant< std::string >("ADRO RTB"));
			}
	
			~Info(){
                BOOST_LOG_SEV(slg , ADRO_LOG::info) << buf.str(); 
			}
			
            template<typename T>
            Info &operator<<(const T &t)
            {
				buf << t; 
                return * this ; 
            }


    };

    //Author: Lashgarian 
    //Date: 23.Feb.2015 
    /*!
     * This class print Debug severity log 
     * with help of boost Log library V2.
     *
     */
    class Debug {
        public :
			src::severity_logger< ADRO_LOG::LogLevel > slg;
			std::ostringstream buf; 
			Debug(){
                slg.add_attribute("Tag", attrs::constant< std::string >("ADRO RTB"));
			}
			~Debug(){
                BOOST_LOG_SEV(slg , ADRO_LOG::debug) << buf.str() ; 
			}
            template<typename T>
            Debug &operator<<(const T &t)
            {
				buf << t ;
                return * this ; 
            }

    };

    //Author: Lashgarian 
    //Date: 23.Feb.2015 
    /*!
     * This class print warn severity log 
     * with help of boost Log library V2.
     *
     */
    class Warn {
        public :
			src::severity_logger< ADRO_LOG::LogLevel > slg;
			std::ostringstream buf; 
			Warn(){
                slg.add_attribute("Tag", attrs::constant< std::string >("ADRO RTB"));
			}
			~Warn(){
                BOOST_LOG_SEV(slg , ADRO_LOG::warning) << buf.str() ; 
			}
            template<typename T>
            Warn &operator<<(const T &t)
            {
				buf << t;
                return * this ; 
            }

    };
     //Author: Lashgarian 
    //Date: 23.Feb.2015 
    /*!
     * This class print Error severity log 
     * with help of boost Log library V2.
     *
     */
    class Error {
        public :
			src::severity_logger< ADRO_LOG::LogLevel > slg;
			std::ostringstream buf; 
			Error(){
                slg.add_attribute("Tag", attrs::constant< std::string >("ADRO RTB"));
			}
			~Error(){
                BOOST_LOG_SEV(slg , ADRO_LOG::error) << buf.str() ; 
			}
            template<typename T>
            Error &operator<<(const T &t)
            {
				buf << t ; 
                return * this ; 
            }

    };

    //Author: Lashgarian 
    //Date: 23.Feb.2015 
    /*!
     * This class print info severity log 
     * with help of boost Log library V2.
     *
     */
    class Crit {
        public :
			src::severity_logger< ADRO_LOG::LogLevel > slg;
			std::ostringstream buf; 
			Crit(){
                slg.add_attribute("Tag", attrs::constant< std::string >("ADRO RTB"));
			}
			~Crit(){
                BOOST_LOG_SEV(slg , ADRO_LOG::critical) << buf.str() ; 
			}
            template<typename T>
            Crit &operator<<(const T &t)
            {
				buf << t ; 
                return * this ; 
            }

    };

    //Author: Lashgarian 
    //Date: 23.Feb.2015
    /*
     * Log class which wrap Boost Log library for logging
     * in ostream and fstream.
     */
    class Log{
        public :

            //init logging tools such as create sink , 
            //define streams and add them to sink, etc.
            static inline void init();
    
    };


    //Author: Lashgarian
    //Date: 23.Feb.2015
    /*!
     * 
     * set log option and setting such as define 
     * log stream, log foramt, file size and name, etc. and
     * add them to sink 
     *
     */
    inline void Log::init()
    {
        using boost::shared_ptr;
        //defines text_ostream_backend for sink and declater an instance 
        typedef sinks::synchronous_sink< sinks::text_ostream_backend > text_sink;
        shared_ptr< text_sink > pSink(new text_sink); 

        //define sink backend and add o/ofstream to that 
        {
            text_sink::locked_backend_ptr pBackend = pSink->locked_backend();
            shared_ptr< std::ostream > pStream(&std::cout, boost::null_deleter());
            pBackend->add_stream(pStream);

            //TODO : ezafe kardan mahdodyate size 
            //declare file name and size and rotation 
            shared_ptr< std::ofstream > pStream2(new std::ofstream("sampleMajid.log"));
            assert(pStream2->is_open());
//            pBackend->add_stream(pStream2);
        }


        pSink->set_formatter(
                    expr::stream 
                    << "[" << severity << "] " 
                    << "From " << tag_attr <<" @"
                    << expr::format_date_time(timestamp , "%Y-%m-%d, %H:%M:%S.%f" )
                    <<" -- "
                    << expr::smessage   
                );

        //add modified sink to core logging 
        logging::core::get()->set_filter
		(
			severity >= ADRO_LOG::info
		);
        logging::core::get()->add_sink(pSink);
        logging::add_common_attributes();
    }

    
}
#endif
