#ifndef TEST_CHAINING_HASH
#define TEST_CHAINING_HASH

#include "ChainingHash.h"


class TestChainingHash {
    private:
        ChainingHash<string, int>* table; //pointer to dynamically allocated hash table
        
        enum Status {
            FAILED = 0,
            PASSED = 1,
            SEE_OUTPUT = 2 //if the test conditions passed but the user still needs to verify the hash table contents to determine if the unit worked correctly, we show SEE_OUTPUT instead of PASSED
        }; //private enumerated type used to show unit test result - see TestChainingHash.cpp for more

        //private helper functions 
        void pretest(string, string, string);
        void posttest(int, int, bool, bool, bool);
        bool verify(int, int, bool);
        string statusStr(Status);
        
    public:
        //constructor and destructor
        TestChainingHash();
        ~TestChainingHash();

        //public unit tests
        void testInsert();
        void testEmplace();
        void testAt();
        void testRehash();
        void testErase();
        
};

#endif