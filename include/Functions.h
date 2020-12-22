#pragma once 

#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <algorithm>

class Automaton { // one-letter edges only, 1 = empty symbol
public:
    Automaton(std::vector<char> alphabet) :
        alphabet_(alphabet),
        Graph_({{}}) {}

    void add(int, int, char);
    void MakeTerminal(int);
    void ClearTerminal() {
        terminal_.clear();
    }

    Automaton GetComplement() const; // works only with DFA

    Automaton DeleteEmpty() const;

    Automaton GetDFA() const {
        return DeleteEmpty().DFA();
    }

    bool IsComplete() const; // works only with DFA

    Automaton GetComplete() const; // works only with DFA

    int Go(int start, std::string word) const; // works only with DFA, returns vertex

    Automaton MinDFA() const;

    Automaton Intersect(const Automaton&) const;

    bool isEquivalent(const Automaton&) const;

    std::string Discriminator(const Automaton&) const; //returns any word discriminating automata

    std::vector<std::vector<std::pair<int, char>>> GetGraph() const {
        return Graph_;
    }

    bool isTerminal(int index) const {
        return std::find(terminal_.begin(), terminal_.end(), index) != terminal_.end();
    }

    int Size() const {
        return Graph_.size();
    }
    std::vector<int> GetTerminal() const {
        return terminal_;
    }
    std::vector<char> GetAlphabet() const {
        return alphabet_;
    }

    bool operator ==(const Automaton& aim) {
        return (alphabet_ == aim.alphabet_ && 
            Graph_ == aim.Graph_ &&
            terminal_ == aim.terminal_);
    }

    Automaton operator +(const Automaton&) const; // + as in regex
    Automaton operator *() const; //Kleene star
    Automaton operator ^(const Automaton&) const; //concatenation

    int Drain() const; //find drain, -1 if none, mincDFA only


private:
    std::vector<char> alphabet_;
    std::vector<std::vector<std::pair<int, char>>> Graph_;
    std::vector<int> terminal_;

    std::vector<int> GetSon(int ind) const; // find all reachable verteces from ind, using empty edges
    Automaton DFA() const;
    bool AnyWord(std::vector<int>&, std::string&, std::string&, int) const;

};

std::ostream& operator << (std::ostream&, const Automaton&);

Automaton parse_polish(const std::string& expression);

bool solve(const std::string& expression, const std::string& X, int k);