#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN

#include <boost/test/unit_test.hpp>
#include "SavingsAccount.hpp"
#include "CheckingAccount.hpp"


BOOST_AUTO_TEST_SUITE(bank_account_suite)

BOOST_AUTO_TEST_CASE(deposit_test){
    SavingsAccount s("Eugene", "Krabs", 0.1);
    
    BOOST_CHECK_EQUAL(0, s.getBalance());

    s.deposit(100);

    BOOST_CHECK_EQUAL(100, s.getBalance());
}

BOOST_AUTO_TEST_CASE(withdrawal_test){
    SavingsAccount s("Eugene", "Krabs", 0.1);
    s.deposit(200);

    BOOST_CHECK_EQUAL(200, s.getBalance());

    s.withdrawal(50);

    BOOST_CHECK_EQUAL(150, s.getBalance());
    
    s.withdrawal(200);

    BOOST_CHECK_EQUAL(150, s.getBalance());
}

BOOST_AUTO_TEST_CASE(getfirstname_test){
    SavingsAccount s("Eugene", "Krabs", 0.1);

    BOOST_CHECK_EQUAL("Eugene", "Eugene");
}

BOOST_AUTO_TEST_CASE(getlastname_test){
    SavingsAccount s("Eugene", "Krabs", 0.1);

    BOOST_CHECK_EQUAL("Eugene", "Eugene");
}
BOOST_AUTO_TEST_CASE(setfirstname_test){
    SavingsAccount s("Eugene", "Krabs", 0.1);
    s.setFirstName("Bob");

    BOOST_CHECK_EQUAL("Bob", s.getFirstName()) ;
}

BOOST_AUTO_TEST_CASE(setlastame_test){
    SavingsAccount s("Eugene", "Krabs", 0.1);
    s.setLastName("Bob");

    BOOST_CHECK_EQUAL("Bob", s.getLastName()) ;
}

BOOST_AUTO_TEST_CASE(getBalance_test){
    SavingsAccount s("Eugene", "Krabs", 0.1);

    BOOST_CHECK_EQUAL(0, s.getBalance()) ;
}

BOOST_AUTO_TEST_SUITE_END()