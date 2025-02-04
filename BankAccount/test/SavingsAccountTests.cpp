#include <boost/test/unit_test.hpp>
#include "CheckingAccount.hpp"
#include "SavingsAccount.hpp"

BOOST_AUTO_TEST_SUITE(saving_account_suite)

BOOST_AUTO_TEST_CASE(setGetInterestRate_test) {
    SavingsAccount s("Eugene", "Krabs", 0.1);  

    BOOST_CHECK_EQUAL(s.getInterestRate(), 0.1);  

    s.setInterestRate(0.05);  
    BOOST_CHECK_EQUAL(s.getInterestRate(), 0.05);  
}

BOOST_AUTO_TEST_CASE(accrueInterest_test) {
    SavingsAccount s("Bob", "Marley", 0.05);  
    s.deposit(100);  

    BOOST_CHECK_EQUAL(s.getBalance(), 100);  
    s.accrueInterest();  

    BOOST_CHECK_EQUAL(s.getBalance(), 105);  
    s.deposit(500);  

    BOOST_CHECK_EQUAL(s.getBalance(), 605);  
    s.setInterestRate(0.03);  

    s.accrueInterest();  
    BOOST_CHECK_EQUAL(s.getBalance(), 623.15);  
}

BOOST_AUTO_TEST_CASE(to_string_test_savingsaccount){
    SavingsAccount s("Eugene","Krabs", 0.1);
    s.deposit(100);

    std::string expected = "Savings Account Balance: $100.000000, Interest Rate: 0.100000";

    BOOST_CHECK_EQUAL(s.toString(), expected);

}

BOOST_AUTO_TEST_SUITE_END()