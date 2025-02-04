#include <boost/test/unit_test.hpp>
#include "CheckingAccount.hpp"
#include "SavingsAccount.hpp"
#include "AccountManager.hpp"

BOOST_AUTO_TEST_SUITE(AccountManagerTests)

BOOST_AUTO_TEST_CASE(TestAddAccount) {
    AccountManager manager;
    manager.addAccount("Eugene Krabs");

    BOOST_CHECK(manager.getNumAccounts() == 1);
    BOOST_CHECK_NO_THROW(manager.displayAccount("Eugene Krabs"));
}

BOOST_AUTO_TEST_CASE(TestDeleteAccount) {
    AccountManager manager;
    manager.addAccount("Eugene Krabs");
    manager.deleteAccount("Eugene Krabs");

    BOOST_CHECK(manager.getNumAccounts() == 0);
    BOOST_CHECK_THROW(manager.displayAccount("Eugene Krabs"), std::exception);
}

BOOST_AUTO_TEST_CASE(TestWriteCheck) {
    AccountManager manager;
    manager.addAccount("Eugene Krabs");
    manager.addAccount("Bob");

    manager.makeDeposit("Eugene Krabs", 1000.0);
    BOOST_CHECK_NO_THROW(manager.writeCheck("Eugene Krabs", "Bob", 500.0));

    // After writing check, both accounts should be accessible
    BOOST_CHECK_NO_THROW(manager.displayAccount("Eugene Krabs"));
    BOOST_CHECK_NO_THROW(manager.displayAccount("Bob"));
}

BOOST_AUTO_TEST_CASE(TestLoanDisbursement) {
    AccountManager manager;
    manager.addAccount("Eugene Krabs");
    manager.makeDeposit("Eugene Krabs", 1000.0);

    BOOST_CHECK_NO_THROW(manager.disburseLoan("Eugene Krabs", 500.0));
    BOOST_CHECK_THROW(manager.disburseLoan("Bob", 500.0), std::exception);
}

BOOST_AUTO_TEST_CASE(TestLoanEligibility) {
    AccountManager manager;
    manager.addAccount("Eugene Krabs");

    BOOST_CHECK_NO_THROW(manager.loanEligibility("Eugene Krabs", 100.0));
    BOOST_CHECK_THROW(manager.loanEligibility("Bob", 100.0), std::exception);
}

BOOST_AUTO_TEST_CASE(TestRepayLoan) {
    AccountManager manager;
    manager.addAccount("Eugene Krabs");

    manager.makeDeposit("Eugene Krabs", 1000.0);
    manager.disburseLoan("Eugene Krabs", 500.0);
    BOOST_CHECK_NO_THROW(manager.repayLoan("Eugene Krabs", 100.0));
}

BOOST_AUTO_TEST_SUITE_END()
