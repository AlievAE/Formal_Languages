//
// Created by akhtyamovpavel on 5/1/20.
//


#pragma once

#include <gtest/gtest.h>
#include "Functions.h"

class TestAutomaton : public ::testing::Test {
    public: 
        void  SetUp() {
            A = new Automaton ({'a', 'b'}); // (w|a - w|b) % 3 == 0, 9 states, DFA
            for (int i = 0; i < 9; ++i) {
                int j = i + 1;
                if (i % 3 == 2) j = i - 2;
                A->add(i, j, 'a');
                j = i + 3;
                if (i >= 6) j = i - 6;
                A->add(i, j, 'b');
                if (i % 4 == 0) {
                    A->MakeTerminal(i);
                }
            }

            B = new Automaton({'B', 'c'}); // small DFA with different alphabet
            B->add(0, 1, 'B');
            B->add(1, 2, 'c');
            B->add(2, 1, 'c');
        } 

        void TearDown() {
            delete A;
            delete B;
        }
        Automaton* A;
        Automaton* B;
};