#include <boost/test/unit_test.hpp>
#include "CheckingAccount.hpp"
#include "SavingsAccount.hpp"

BOOST_AUTO_TEST_SUITE(checking_account_suite)

BOOST_AUTO_TEST_CASE(writeCheck_test) {
    CheckingAccount c("Eugene", "Krabs");
    SavingsAccount s("Bob", "Marley", 0.3);
    c.deposit(200);
    s.deposit(50);

    BOOST_CHECK_EQUAL(200, c.getBalance());
    BOOST_CHECK_EQUAL(50, s.getBalance());

    bool success = c.writeCheck(s, 100);

    BOOST_CHECK(success);
    BOOST_CHECK_EQUAL(100, c.getBalance());
    BOOST_CHECK_EQUAL(150, s.getBalance());

    success = c.writeCheck(s, -10);
    BOOST_CHECK(!success);
    BOOST_CHECK_EQUAL(100, c.getBalance());
    BOOST_CHECK_EQUAL(150, s.getBalance());
}

BOOST_AUTO_TEST_CASE(checkLog_test) {
    CheckingAccount c("Eugene", "Krabs");
    SavingsAccount s("Bob", "Marley", 0.3);

    c.deposit(200);
    c.writeCheck(s, 50);
    c.writeCheck(s, 75);

    std::list<double> log = c.getCheckLog();
    std::list<double> expectedLog = {50, 75};

    BOOST_CHECK_EQUAL_COLLECTIONS(log.begin(), log.end(), expectedLog.begin(), expectedLog.end());
}

BOOST_AUTO_TEST_CASE(to_string_test_checkingaccount) {
    CheckingAccount c("Bob", "Marley");
    c.deposit(100);

    std::string expected = "Checking Account Balance: $100.000000, wrote 0 checks\nLoan Balance: $0.000000, 0 Loans taken.";

    BOOST_CHECK_EQUAL(c.toString(), expected);
}

BOOST_AUTO_TEST_CASE(getLoanBalance_test) {
    CheckingAccount c("Bob", "Marley");

    BOOST_CHECK_EQUAL(0, c.getLoanBalance());
}

BOOST_AUTO_TEST_CASE(setLoanBalance_test) {
    CheckingAccount c("Bob", "Marley");
    c.setLoanBalance(100);

    BOOST_CHECK_EQUAL(100, c.getLoanBalance());
}

BOOST_AUTO_TEST_CASE(getLoanInterestRate_test) {
    CheckingAccount c("Bob", "Marley");

    double loanInterestRate = c.getLoanInterestRate();
    double expectedLoanInterestRate = 0.05;

    BOOST_CHECK_EQUAL(loanInterestRate, expectedLoanInterestRate);
}

BOOST_AUTO_TEST_CASE(accrueLoanInterest_test) {
    CheckingAccount c("Bob", "Marley");
    c.setLoanBalance(1000.0);

    double loanInterestRate = c.getLoanInterestRate();
    double expectedLoanBalance = 1000.0 + (1000.0 * loanInterestRate);

    c.accrueLoanInterest();

    BOOST_CHECK_CLOSE(c.getLoanBalance(), expectedLoanBalance, 0.01);
}

BOOST_AUTO_TEST_CASE(loanEligibility_test) {
    CheckingAccount c("Bob", "Marley");
    c.deposit(200); // Ensure balance is sufficient for loan eligibility

    LoanEligibility eligibility = c.loanEligibility();
    double expectedLoanEligibility = 200 * 0.5; // Max loan eligibility is 50% of balance

    BOOST_CHECK_EQUAL(eligibility.remainingEligibility, expectedLoanEligibility);
}

BOOST_AUTO_TEST_CASE(disburseLoan_test) {
    CheckingAccount c("Bob", "Marley");
    c.deposit(200);  // Ensure there is enough balance for loan eligibility

    BOOST_CHECK_EQUAL(c.getLoanBalance(), 0.0);

    bool success = c.disburseLoan(100.0);  // Check if loan can be disbursed
    BOOST_CHECK(success);
    BOOST_CHECK_EQUAL(c.getLoanBalance(), 100.0);

    success = c.disburseLoan(200.0);  // Check if loan exceeds eligibility
    BOOST_CHECK(!success);
    BOOST_CHECK_EQUAL(c.getLoanBalance(), 100.0);  // No change in loan balance
}

BOOST_AUTO_TEST_CASE(loanRepayment_test) {
    CheckingAccount c("Bob", "Marley");
    c.deposit(200); // Ensure balance is non-zero for loan eligibility
    c.disburseLoan(1000.0);  /

    BOOST_CHECK_EQUAL(c.getLoanBalance(), 1000.0);

    c.loanRepayment(300.0);  
    BOOST_CHECK_EQUAL(c.getLoanBalance(), 700.0);

    c.loanRepayment(800.0);  
    BOOST_CHECK_EQUAL(c.getLoanBalance(), 700.0); 
}

BOOST_AUTO_TEST_SUITE_END()
