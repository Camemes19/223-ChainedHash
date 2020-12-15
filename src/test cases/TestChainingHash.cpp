#include "TestChainingHash.h"

/*
Name: Svetoslav Dimitrov
Description: Provides MA1-style unit tests for the following ChainingHash member functions:

    (1) void insert(const std::pair<K, V>& pair)
    (2) void emplace(K key, V value)
    (3) V& at(const K& key)
        -called on key that exists in the hash table (see testAt() below)
    (4) V& at(const K& key)
        -called on key that does not exist in the hash table (see testAtDNE() below)
    (5) void erase(const K& key)
    
    Note that tests will be performed on std::string keys and int values, and initial table sizes will be 11
    (this is what the default ChainingHash constructor provides). Each test will have the same structure:

        (1) pretest
            -Reset the ChainingHash table using the ChainingHash::reset() function
            -Modify the hash table as needed to meet preconditions
            -Print the test ID, preconditions, and expected result
        (2) test
            -Call the unit being tested, storing return values if needed
        (3) posttest
            -Show test result, which might include printing the contents of the hash table
            -Verify that size, bucket count, and empty return the correct values using the verify() helper function - display the FAILED status if incorrect
            -Show test status = PASSED, FAILED or SEE OUTPUT, which means the contents of the hash table need to be verified by the user (see posttest() function below for more)
            
*/

/*******************************
    - CONSTRUCTOR / DESTRUCTOR -
********************************/
TestChainingHash::TestChainingHash() {
    this->table = new ChainingHash<string, int>(); //create new ChainingHash table in memory
}

TestChainingHash::~TestChainingHash() {
    delete table; //deallocate ChainingHash table
}


/*******************************
    - UNIT TESTS -
********************************/

/*
    Test ID: Empty table insert check - ETIC
    Unit: ChainingHash::insert()
    Description: tests to determine if ChainingHash::insert() properly inserts a key value pair into a table bucket, while also returning 
    exepcted size, bucket count, and empty values 
    Test steps:
        1. Pretest
            a. Reset ChainingHash table 
            b. Show initial state of hash table using the ChainingHash::printTable() function
        2. Test
            a. Insert key/value pair "a" -> 97 into the hash table using the ChainingHash::insert() function 
        3. Posttest
            a. Print hash table using the ChainingHash::printTable() function to ensure key/value pair was properly inserted, 
            show FAILED if size, bucket count, or empty values are not as expected, otherwise show SEE_OUTPUT  
    Test data: key/value pair "a" -> 97, initial bucket count = 11
    Precondition: ChainingHash table has been reset with the ChainingHash::reset() function 
    Expected result: ChainingHash::printTable() shows key/value pair properly inserted into table bucket, size, bucket count, and empty
    return 1, 11, and false, respectively
    Actual result: some issues with output formatting, but otherwise expected result was observed
    Status: PASSED
*/
void TestChainingHash::testInsert() {
    string testid = "Empty table insert check - ETIC"; 
    string preconditions = "ChainingHash table has been reset with the ChainingHash::reset() function";
    string expectedResult = "ChainingHash::printTable() shows key/value pair properly inserted into table bucket, size, bucket count, and empty return 1, 11, and false, respectively";
    int exSize = 1;
    int exBucketCount = 11;
    bool exEmpty = false;
    bool initPassed = true;
    bool seeOutput = true; 

    this->table->reset();
    this->pretest(testid, preconditions, expectedResult);
    this->table->insert(make_pair("a", 97));
    this->posttest(exSize, exBucketCount, exEmpty, initPassed, seeOutput);
}

/*
    Test ID: Empty table emplace check - ETEC
    Unit: ChainingHash::emplace()
    Description: tests to determine if ChainingHash::emplace() properly emplaces a key value pair into a table bucket, while also returning 
    exepcted size, bucket count, and empty values 
    Test steps:
        1. Pretest
            a. Reset ChainingHash table 
            b. Show initial state of hash table using the ChainingHash::printTable() function
        2. Test
            a. Emplace key/value pair "a" -> 97 into the hash table using the ChainingHash::emplace() function 
        3. Posttest
            a. Print hash table using the ChainingHash::printTable() function to ensure key/value pair was properly emplaced, 
            show FAILED if size, bucket count, or empty values are not as expected, otherwise show SEE_OUTPUT  
    Test data: key/value pair "a" -> 97, initial bucket count = 11
    Precondition: ChainingHash table has been reset with the ChainingHash::reset() function 
    Expected result: ChainingHash::printTable() shows key/value pair properly emplaced into table bucket, size, bucket count, and empty
    return 1, 11, and false, respectively
    Actual result: see expected result above 
    Status: PASSED
*/
void TestChainingHash::testEmplace() {
    string testid = "Empty table emplace check - ETEC";
    string preconditions = "ChainingHash table has been reset with the ChainingHash::reset() function ";
    string expectedResult = "ChainingHash::printTable() shows key/value pair properly emplaced into table bucket, size, bucket count, and empty return 1, 11, and false, respectively";
    int exSize = 1;
    int exBucketCount = 11;
    bool exEmpty = false;
    bool initPassed = true;
    bool seeOutput = true; 

    this->table->reset();
    this->pretest(testid, preconditions, expectedResult);
    this->table->emplace("a", 97);
    this->posttest(exSize, exBucketCount, exEmpty, initPassed, seeOutput);
}

/*
    Test ID: Key exists at check - KEAC
    Unit: ChainingHash::at()
    Description: tests to determine if ChainingHash::at() returns the correct value associated with the given key, while also returning 
    exepcted size, bucket count, and empty values 
    Test steps:
        1. Pretest
            a. Reset ChainingHash table 
            b. Insert key/value pair "a" -> 97 into table using the ChainingHash::insert() function 
            c. Show initial state of hash table using the ChainingHash::printTable() function
        2. Test
            a. Call ChainingHash::insert("a") and save return value 
        3. Posttest
            a. Check to see if ChainingHash::at("a") returns 97, the value associated with key "a"
            b. Print hash table using the ChainingHash::printTable() function, 
            show FAILED if size, bucket count, or empty values are not as expected OR if ChainingHash::at("a") does not return 97, 
            therwise show PASSED  
    Test data: key/value pair "a" -> 97, initial bucket count = 11
    Precondition: ChainingHash table has been reset with the ChainingHash::reset() function, table has key/value pair "a" -> 97 inserted
    Expected result: ChainingHash::at("a") returns 97, size, bucket count, and empty return 1, 11, and false, respectively
    Actual result: see expected result above 
    Status: PASSED
*/
void TestChainingHash::testAt() {
    string testid = "Key exists at check - KEAC";
    string preconditions = "ChainingHash table has been reset with the ChainingHash::reset() function, table has key/value pair \"a\" -> 97 inserted";
    string expectedResult = "ChainingHash::at(\"a\") returns 97, size, bucket count, and empty return 1, 11, and false, respectively";
    int exSize = 1;
    int exBucketCount = 11;
    bool exEmpty = false;
    bool initPassed = true;
    bool seeOutput = false; 
    int atReturn; 

    this->table->reset();
    this->pretest(testid, preconditions, expectedResult);
    this->table->insert(make_pair("a", 97));
    atReturn = this->table->at("a") == 97;
    initPassed = atReturn == 97;
    print("ChainingHash::at(\"a\") returns " + std::to_string(atReturn) + "\n");
    this->posttest(exSize, exBucketCount, exEmpty, initPassed, seeOutput);
}

/*
    Test ID: High load factor rehash check - HLFRC
    Unit: ChainingHash::rehash()
    Description: tests to determine if ChainingHash::rehash() both recognizes the need for a rehash given a high load factor and properly rehashes
    table by rehashing key/value pairs and expanding table to the nearest prime number greater than or equal to 2x the curren size, 
    while also returning exepcted size, bucket count, and empty values 
    Test steps:
        1. Pretest
            a. Reset ChainingHash table 
            b. Insert key/value pairs corresponding to the first 9 lowercase characters and their ASCII values into table using 
            the ChainingHash::insert() function 
            c. Show initial state of hash table using the ChainingHash::printTable() function
        2. Test
            a. No need to call ChainingHash::rehash() explitly - meant to be called by ChainingHash::insert() after recognizing high
            load factor
        3. Posttest
            a. Print hash table using the ChainingHash::printTable() function, 
            show FAILED if size, bucket count, or empty values are not as expected, otherwise show SEE OUTPUT   
    Test data: first 9 lowercase characters and their ASCII values, initial bucket count = 11
    Precondition: ChainingHash table has been reset with the ChainingHash::reset() function, table has 
    first 9 lowercase characters and their ASCII values inserted via the ChainingHash::insert() function 
    Expected result: after inserts, chaining hash properly rehashes all key/value pairs with correct table size, size, bucket count, 
    and empty return 9, 23, and false, respectively
    Actual result: see expected result above 
    Status: PASSED
*/
void TestChainingHash::testRehash() {
    string testid = "High load factor rehash check - HLFRC";
    string preconditions = "ChainingHash table has been reset with the ChainingHash::reset() function, table has first 9 lowercase characters and their ASCII values inserted via the ChainingHash::insert() function";
    string expectedResult = "after inserts, chaining hash properly rehashes all key/value pairs with correct table size, size, bucket count, and empty return 9, 23, and false, respectively";
    int exSize = 9;
    int exBucketCount = 23;
    bool exEmpty = false;
    bool initPassed = true;
    bool seeOutput = true; 
    std::string strKey = "\0";

    this->table->reset();
    this->pretest(testid, preconditions, expectedResult);
    for(int keyASCII = 97; keyASCII <= 105; ++keyASCII) {
        strKey[0] = (char) keyASCII;
        table.insert(make_pair(strKey, keyASCII));
    }
    this->posttest(exSize, exBucketCount, exEmpty, initPassed, seeOutput);
}

/*
    Test ID: Nonempty erase check - NEEC
    Unit: ChainingHash::erase()
    Description: tests to determine if ChainingHash::erases() properly removes inserted key/value from table 
    while also correctly updating size, bucket count, and empty values 
    Test steps:
        1. Pretest
            a. Reset ChainingHash table 
            b. Insert key/value pair "a" -> 97 into table using the ChainingHash::insert() function 
            c. Show initial state of hash table using the ChainingHash::printTable() function
        2. Test
            a. Call ChainingRehash::erase("a")
        3. Posttest
            a. Print hash table using the ChainingHash::printTable() function, 
            show FAILED if size, bucket count, or empty values are not as expected, otherwise show SEE OUTPUT   
    Test data: key/value pair "a" -> 97, initial bucket count = 11
    Precondition: ChainingHash table has been reset with the ChainingHash::reset() function, table has 
    key/value pair "a" -> 97 inserted via the ChainingHash::insert() function 
    Expected result: after erase, ChainingHash::erase() properly removes key/value pair "a" -> 97, size, bucket count, 
    and empty return 9, 11, and true, respectively
    Actual result: see expected result above 
    Status: PASSED
*/
void TestChainingHash::testErase() {
    string testid = "Nonempty erase check - NEEC";
    string preconditions = "ChainingHash table has been reset with the ChainingHash::reset() function, table has key/value pair \"a\" -> 97 inserted via the ChainingHash::insert() function";
    string expectedResult = "after erase, ChainingHash::erase() properly removes key/value pair \"a\" -> 97, size, bucket count, and empty return 9, 11, and true, respectively";
    int exSize = 0;
    int exBucketCount = 11;
    bool exEmpty = true;
    bool initPassed = true;
    bool seeOutput = true; 

    this->table->reset();
    this->table->insert(make_pair("a", 97));
    this->pretest(testid, preconditions, expectedResult);
    this->table->erase("a");
    this->posttest(exSize, exBucketCount, exEmpty, initPassed, seeOutput);   
}

/*******************************
    - PRIVATE HELPER FUNCTIONS -
********************************/

//display test id, preconditions, initial table state, and expected result
void TestChainingHash::pretest(string testid, string preconditions, string expectedResult) {
    print("Test ID: " + testid + "\n");
    print("Preconditions: " + preconditions + " and table has key/value pairs\n");
    this->table->printTable();
    print("Expected result: " + expectedResult + "\n");
    print("Result:\n");
}

//determine test status, show final table state, and display test result 
void TestChainingHash::posttest(int exSize, int exBucketCount, bool exEmpty, bool initPassed , bool seeOutput) {
    bool passed = initPassed && verify(table, exSize, exBucketCount, exEmpty);
    S/tatus testStatus;
    if(passed == false) //if the either the additional pass condition or verify() returns false, the test case was failed
        testStatus = FAILED;
    else { //otherwise
        if(seeOutput) //if the two conditions above passed but the user still needs to verify that the contents of the hash table are correct, the test wasn't necessarily passed - so, instead of saying PASSED, we show SEE OUTPUT to allow the user to verify the hash table
            testStatus = SEE_OUTPUT;
        else
            testStatus = PASSED; //if there contents of the hash table don't need to be verified, we've passed the test case
    }

    this->table->printTable(); //print the contents of the hash table

    print("Status: " + statusStr(testStatus) + "\n");   
}

//verify that size, bucket count, and empty return values are correct
bool TestChainingHash::verify(int exSize, int exBucketCount, bool exEmpty) {
    return (this->table->size() == exSize && this->table->bucket_count() == exBucketCount && this->table->empty() == exEmpty);
}

//convert Status enumerated type to std::string to allow for printing 
string TestChainingHash::statusStr(Status testStatus) {
    string str = "";

    if(testStatus == SEE_OUTPUT)
        str = "SEE OUTPUT";
    else if(testStatus == FAILED)
        str = "FAILED"; 
    else if(testStatus == PASSED)
        str = "PASSED";

    return str;
}

//used to print output to the godot console
void print(string consoleMessage) { 
    std::cout << message;
}