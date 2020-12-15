#ifndef TEST_CHAINING_HASH
#define TEST_CHAINING_HASH

#include "ChainingHash.h"


class TestChainingHash {
    private:
        ChainingHash<string, int>* table;

        void pretest(string, string, string);
        void posttest(int, int, bool, bool, bool);
        bool verify(int, int, bool);
        string statusStr(Status);

        enum Status {
            FAILED = 0,
            PASSED = 1,
            SEE_OUTPUT = 2
        };
        
    public:
        TestChainingHash();
        ~TestChainingHash();

        void testInsert();
        void testEmplace();
        void testAt();
        void testRehash();
        void testErase();
        
};

#endif
