//
// Created by akhtyamovpavel on 5/1/20.
//

#include "AddTestCase.h"
#include "Functions.h"


TEST_F(TestAutomaton, GetComplete_test1){
    Automaton aim = A->GetComplete();
    ASSERT_TRUE(*A == aim);
}

TEST_F(TestAutomaton, GetComplete_test2) {
    Automaton ans({'B', 'c'});
    ans.add(0, 1, 'B');
    ans.add(1, 2, 'c');
    ans.add(2, 1, 'c');
    ans.add(0, 3, 'c');
    ans.add(1, 3, 'B');
    ans.add(2, 3, 'B');
    ans.add(3, 3, 'B');
    ans.add(3, 3, 'c');
    Automaton CompleteB = B->GetComplete();
    ASSERT_TRUE(CompleteB == ans);
}

TEST_F(TestAutomaton, MinDFA_test1) {
    Automaton ans({'a', 'b'});
    ans.add(0, 0, 'a');
    ans.add(0, 0, 'b');
    A->ClearTerminal();
    ASSERT_TRUE(ans==A->MinDFA());
}

TEST_F(TestAutomaton, MinDFA_test2) 
{
	Automaton ans({'a', 'b'});
    ans.add(0, 1, 'a');
    ans.add(0, 2, 'b');
    ans.add(1, 2, 'a');
    ans.add(1, 0, 'b');
    ans.add(2, 0, 'a');
    ans.add(2, 1, 'b');
    ans.MakeTerminal(0);
    ASSERT_TRUE(ans==A->MinDFA());
}

TEST_F(TestAutomaton, GetComplement_test1) {
    Automaton C ({'a', 'b'}); // almost random large DFA
    for (int i = 0; i < 10; ++i) {
        C.add(i, (i * i + i + 17) % 10, 'a');
        C.add(i, ((1 << i) + 3 + i) % 10, 'b');
        if (i % 2 == 0) {
            C.MakeTerminal(i);
        }
    }
    Automaton ComplementC({'a', 'b'});
    for (int i = 0; i < 10; ++i) {
        ComplementC.add(i, (i * i + i + 17) % 10, 'a');
        ComplementC.add(i, ((1 << i) + 3 + i) % 10, 'b');
        if (i % 2 != 0) {
            ComplementC.MakeTerminal(i);
        }
    }
    ASSERT_TRUE(C.GetComplement() == ComplementC);
}

TEST_F(TestAutomaton, GetComplement_test2) {
    Automaton D({'a', 'b'}); // a(a+b)* + b
    D.add(0, 1, 'a');
    D.add(1, 1, 'a');
    D.add(1, 1, 'b');
    D.add(0, 2, 'b');
    D.MakeTerminal(1);
    D.MakeTerminal(2);

    Automaton ComplementD({'a', 'b'});
    ComplementD.add(0, 1, 'a');
    ComplementD.add(0, 2, 'b');
    ComplementD.add(1, 1, 'a');
    ComplementD.add(1, 1, 'b');
    ComplementD.add(2, 3, 'a');
    ComplementD.add(2, 3, 'b');
    ComplementD.add(3, 3, 'a');
    ComplementD.add(3, 3, 'b');
    ComplementD.MakeTerminal(0);
    ComplementD.MakeTerminal(3);

    ASSERT_TRUE(D.GetComplement() == ComplementD);
}

TEST_F(TestAutomaton, DeleteEmpty_test1) {
    Automaton E({'a', 'b'}); // small senseless NFA
    E.add(0, 0, '1');
    E.add(0, 1, 'a');
    E.add(1, 0, '1');
    E.add(1, 2, 'b');
    E.add(1, 2, '1');
    E.add(2, 2, 'a');
    E.MakeTerminal(2);

    Automaton NoEmptyE({'a', 'b'});
    NoEmptyE.add(0, 1, 'a');
    NoEmptyE.add(1, 2, 'b');
    NoEmptyE.add(1, 1, 'a');
    NoEmptyE.add(1, 2, 'a');
    NoEmptyE.add(2, 2, 'a');
    NoEmptyE.MakeTerminal(1);
    NoEmptyE.MakeTerminal(2);
    ASSERT_TRUE(E.DeleteEmpty() == NoEmptyE);
}

TEST_F(TestAutomaton, DeleteEmpty_test2) {
    ASSERT_TRUE(*A == A->DeleteEmpty());
}

TEST_F(TestAutomaton, Intersect_smokey_test1) {
    Automaton A({'a', 'b'});
    Automaton B({'a', 'b'});
    ASSERT_TRUE(A.Intersect(B) == A);
}

TEST_F(TestAutomaton, Intersect_smokey_test2) {
    Automaton empty({'a', 'b'});
    Automaton A({'a', 'b'});
    A.add(0, 1, 'a');
    A.MakeTerminal(1);
    Automaton B({'a', 'b'});
    B.add(0, 1, 'a');
    B.MakeTerminal(0);
    ASSERT_TRUE(A.Intersect(B).isEquivalent(empty));
}

TEST_F(TestAutomaton, Intersect_smokey_test3) {
    Automaton A({'a', 'b'});
    A.add(0, 1, 'a');
    A.MakeTerminal(1);
    ASSERT_TRUE(A.Intersect(A) == A);
}

TEST_F(TestAutomaton, Intersect_smokey_test4) {
    Automaton A({'a', 'b'});
    A.add(0, 1, 'a');
    A.MakeTerminal(1);
    Automaton B({'a', 'b'});
    B.add(0, 1, 'a');
    B.MakeTerminal(0);
    Automaton C({'a', 'b'});
    C.add(0, 1, 'a');
    ASSERT_TRUE(A.Intersect(B) == C);
}

TEST_F(TestAutomaton, Intersect_test1) {
    Automaton A({'a', 'b'});
    A.add(0, 1, 'a');
    A.add(0, 2, 'a');
    A.add(1, 3, 'a');
    A.add(2, 3, 'a');
    A.MakeTerminal(3);
    A = A.MinDFA();
    Automaton B({'a', 'b'});
    B.add(0, 1, 'a');
    B.add(1, 2, 'a');
    B.MakeTerminal(2);
    ASSERT_TRUE(A.Intersect(B) == B);
}

TEST_F(TestAutomaton, Intersect_test2) {
    Automaton A({'a', 'b'});
    A.add(0, 1, 'a');
    A.add(1, 0, '1');
    A.MakeTerminal(1);
    Automaton B({'a', 'b'});
    B.add(0, 1, 'a');
    B.add(1, 0, '1');
    B.MakeTerminal(0);
    ASSERT_TRUE(A.Intersect(B).isEquivalent(A));
}

TEST_F(TestAutomaton, Equality_test1) {
    Automaton A({'a', 'b'});
    A.add(0, 1, 'a');
    A.add(1, 2, 'a');
    A.MakeTerminal(1);
    Automaton B({'a', 'b'});
    B.add(0, 2, 'a');
    B.add(2, 1, 'a');
    B.MakeTerminal(2);
    ASSERT_TRUE(A.isEquivalent(B));
}

TEST_F(TestAutomaton, Equality_test2) {
    Automaton A({'a', 'b'});
    A.add(0, 1, 'b');
    A.add(1, 0, 'b');
    A.MakeTerminal(1);
    Automaton B({'a', 'b'});
    B.add(0, 1, 'a');
    B.add(1, 0, 'a');
    B.MakeTerminal(1);
    ASSERT_FALSE(A.isEquivalent(B));
}

TEST_F(TestAutomaton, Equality_test3) {
    Automaton A({'a', 'b'});
    A.add(0, 1, 'a');
    A.add(1, 0, 'a');
    A.MakeTerminal(2);
    Automaton B({'a', 'b'});
    B.add(0, 1, 'a');
    B.add(1, 0, 'a');
    B.MakeTerminal(3);
    ASSERT_TRUE(A.isEquivalent(B));
}

TEST_F(TestAutomaton, Discriminator_test1) {
    Automaton A({'a', 'b'});
    A.add(0, 1, 'a');
    A.MakeTerminal(1);
    Automaton B({'b', 'a'});
    B.add(0, 1, 'b');
    B.MakeTerminal(1);
    ASSERT_TRUE("a" == A.Discriminator(B));
}

TEST_F(TestAutomaton, Discriminator_test2) {
    Automaton A({'a', 'b'});
    A.add(0, 1, 'a');
    A.add(1, 0, '1');
    A.MakeTerminal(1);
    Automaton B({'b', 'a'});
    B.add(0, 1, 'a');
    B.add(1, 0, '1');
    B.MakeTerminal(0);
    EXPECT_TRUE("" == A.Discriminator(B));
}

TEST_F(TestAutomaton, Solver_test1) {
    std::string exp;
    std::string x;
    int k;
    exp = "ab+c.aba.*.bac.+.+*";
    x = "a";
    k = 4;
    bool ans = solve(exp, x, k);
    EXPECT_TRUE(ans == false);
}

TEST_F(TestAutomaton, Solver_test2) {
    std::string exp;
    std::string x;
    int k;
    exp = "acb..bab.c.*.ab.ba.+.+*a.";
    x = "c";
    k = 0;
    bool ans = solve(exp, x, k);
    EXPECT_TRUE(ans == true);
}

TEST_F(TestAutomaton, Discriminator_test3) {
    Automaton A({'a', 'b', 'c', 'd', 'k', 'i', 'n', 'g', 's'}); // almost random big automaton
    for (size_t i = 0; i < 100; ++i) {
        A.add((i*i + 13) % 100, (i^i + 23) % 100, (i*i*i % 4) + 'a'); 
        if (i % 13 == 0) {
            A.MakeTerminal(i);
        }
    }
    Automaton B({'a', 'b', 'c', 'd', 'k', 'i', 'n', 'g', 's'});
    B.add(0, 1, 'k');
    B.add(1, 2, 'i');
    B.add(2, 3, 'n');
    B.add(3, 4, 'g');
    B.add(4, 5, 'i');
    B.add(5, 6, 's');
    B.add(6, 7, 'b');
    B.add(7, 8, 'a');
    B.add(8, 9, 'c');
    B.add(9, 10, 'k');
    B.MakeTerminal(10);
    B = A + B;
    EXPECT_TRUE("kingisback" == A.Discriminator(B));
}

TEST_F(TestAutomaton, Discriminator_test4) {
    Automaton A({'a', 'b', 'c', 'd', 'k', 'i', 'n', 'g', 's'}); // almost random big automaton
    for (size_t i = 0; i < 100; ++i) {
        A.add((i*i + 13) % 100, (i^i + 23) % 100, (i*i*i % 4) + 'a'); 
        if (i % 13 == 0) {
            A.MakeTerminal(i);
        }
    }
    Automaton B = A;
    EXPECT_EQ("$$$DISCRIMINATOR FAIL!!!!!", A.Discriminator(B));
}

TEST_F(TestAutomaton, Solver_test3) {
    std::string exp;
    std::string x;
    int k;
    exp = "1abc.*.*."; // regex = 1(a(bc)*)*
    x = "aaaaaaaaa";
    k = 1000000000;
    bool ans = solve(exp, x, k);
    EXPECT_TRUE(ans == true);
}

TEST_F(TestAutomaton, Polish_test1) {
    std::string exp = "acb..bab.c.*.ab.ba.+.+*a.+";
    EXPECT_THROW(parse_polish(exp), std::runtime_error);
}

TEST_F(TestAutomaton, Polish_test2) {
    std::string exp = "privet!!!";
    EXPECT_THROW(solve(exp, "aaaaa", 100), std::runtime_error); //since its incorrect expression
}