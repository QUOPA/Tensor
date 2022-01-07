#pragma once
#include <exception>
#include <iostream>
#include <string>

#define REGISTERTESTCASE(FN) std::cout << std::endl  << "< TEST CASE : " << #FN << " >" << std::endl; \
try { FN(); } \
catch (std::exception & e) { std::cout << "Exception : " << e.what() <<std::endl; } \
catch (...) { std::cout << "Exception : Unexpected" << std::endl; }


#define REGISTERTESTSUITE(FN) std::cout << std::endl << "======== TEST SUITE : " << #FN << " ========" << std::endl; FN();


#define REGISTERTESTCASE_STRIN(FN, StrIN) std::cout << std::endl  << "< TEST CASE : " << #FN << " >" << std::endl; \
try { FN(StrIN); } \
catch (std::exception & e) { std::cout << "Exception : " << e.what() <<std::endl; } \
catch (...) { std::cout << "Exception : Unexpected" << std::endl; }


#define REGISTERTESTSUITE_STRIN(FN, StrIN) std::cout << std::endl << "======== TEST SUITE : " << #FN << " ========" << std::endl; \
std::cout << "Parameter: " << StrIN << std::endl; FN(StrIN);


#define SHOW_LITERAL_AND_COUT(varin)  std::cout << #varin << " = " << varin;

