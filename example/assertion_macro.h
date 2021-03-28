#pragma once

/** 
    The only way in which a cooltests test can signal a test failure is by
    throwing an exception. This header wraps that interface into a couple
    assertion macros. These macros lack useful features like communicating
    where the error happened, or what the condition was.

    This header could be part of the cooltestslib library, but I like that
    the interface between test and test runner is so thin that the assertion
    functionality can be written by the user.

    These do not really have to be macros, they could just be regular functions.
*/

#define COOLTESTS_SIGNALFAILURE throw 0; // lol
#define ASSERT(condition) if (!(condition))	\
    COOLTESTS_SIGNALFAILURE
#define ASSERT_EQ(lhs, rhs) ASSERT(lhs == rhs)
