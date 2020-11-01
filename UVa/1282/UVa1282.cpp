/*
 * UVa1282.cpp
 * Copyleft (ɔ) 2020 wildfootw <wildfootw@wildfoo.tw>
 *
 * Distributed under terms of the MIT license.
 */

// [ ] Completed

#include <iostream>
#include <ctime>
#include <vector>

#define INF 2147483647
#define EPS 1e-9
#define DEFAULT_FIXSTR 3

using namespace std;

#ifndef KNUTHMORRISPRATT_HPP
#define KNUTHMORRISPRATT_HPP
class KnuthMorrisPratt
{
private:
#ifndef NDEBUG
    inline string fix_alignment(string para) const;
#endif // NDEBUG

protected:
    string text, pattern;
    vector<int> answer_pos; //answer text[answer_pos] == pattern[0]
    int * failure; // second longest proper prefix-suffix length

    void calculate_failure(bool allow_overlap);
    void matching();

#ifndef NDEBUG
    void print_failure() const;
#endif // NDEBUG

public:
    KnuthMorrisPratt(string text, string pattern):
        text(text), pattern(pattern)
    {
        failure = new int[text.length() + pattern.length()];
    }

    ~KnuthMorrisPratt()
    {
        delete[] failure;
    }

    vector<int> answer(bool allow_overlap = true);
};

#ifndef NDEBUG
inline string KnuthMorrisPratt::fix_alignment(string para) const
{
    const int alignment_num = 2;
    para.resize(alignment_num, ' ');
    return para;
}
#endif // NDEBUG

void KnuthMorrisPratt::calculate_failure(bool allow_overlap)
{
    failure[0] = 0;
    string combine_str = pattern + text;

    for(int i = 1, j = 0;i < combine_str.length();++i)
    {
        if(failure[i - 1] == pattern.length()) // failure[i - 1] == pattern.length() is my own alternative for in case failure > pattern length (z.B. ABZABC ABZABCABZABC)
        {
            if(allow_overlap)
                j = failure[j - 1];
            else
                j = 0;
        }

        while(combine_str[i] != combine_str[j] && j > 0)
        {
            j = failure[j - 1];
        }
        if(combine_str[i] == combine_str[j])
        {
            failure[i] = ++j;
        }
        else
        {
            failure[i] = 0;
        }
    }
}

void KnuthMorrisPratt::matching()
{
    for(int i = 0;i < text.length();++i)
    {
        if(failure[pattern.length() + i] == pattern.length())
        {
            answer_pos.push_back(i - pattern.length() + 1);
        }
    }
    return;
}

#ifndef NDEBUG
void KnuthMorrisPratt::print_failure() const
{
    for(int i = 0;i < pattern.length();++i)
        clog << fix_alignment(string(1, pattern[i]));
    for(int i = 0;i < text.length();++i)
        clog << fix_alignment(string(1, text[i]));
    clog << endl;

    for(int i = 0;i < (pattern.length() + text.length());++i)
        clog << fix_alignment(to_string(failure[i]));
    clog << endl;
}
#endif // NDEBUG

vector<int> KnuthMorrisPratt::answer(bool allow_overlap)
{
    calculate_failure(allow_overlap);

#ifndef NDEBUG
    print_failure();
#endif // NDEBUG

    matching();

#ifndef NDEBUG
    if(answer_pos.size() == 0)
    {
        clog << "Nothing Matched." << endl;
    }
    else
    {
        clog << "Matched!" << endl;
        clog << text << endl;
        int idx = 0;
        for(int i = 0;i < text.length() && idx < answer_pos.size();++i)
        {
            if(i == answer_pos[idx])
            {
                clog << "⤴";
                ++idx;
            }
            else
                clog << " ";
        }
        clog << endl;
    }
#endif // NDEBUG

    return answer_pos;
}

#endif // KNUTHMORRISPRATT_HPP

static const int MAX_N = 100 // 0 <= N <= 100

class UVa1282
{
public:
    UVa1282(): fibonacci_word_sequence_length(MAX_N + 1, -1), occurrence_times(MAX_N + 1)
    {
        // prepare fibonacci word sequenece length
        fibonacci_word_sequence_length[0] = 1;
        fibonacci_word_sequence_length[1] = 1;
        fibonacci_word_sequence_length_calculate(MAX_N);

        fibonacci_word_sequence[0] = "0";
        fibonacci_word_sequence[1] = "1";
    }

    int count_occurrence_times(int n, string pattern)
    {
        for(int i = 0;i <= n;++i) occurrence_times[i] = -1;
        occurrence_pattern = pattern;
        return count_occurrence_times_recursive(n);
    }

private:
    vector<int> fibonacci_word_sequence_length;
    inline int fibonacci_word_sequence_length_calculate(int n)
    {
        if(fibonacci_word_sequence_length[n] != -1)
            return fibonacci_word_sequence_length[n];
        return fibonacci_word_sequence_length[n] = (fibonacci_word_sequence_length_calculate(n - 1) + fibonacci_word_sequence_length_calculate(n - 2));
    }

    vector<string> fibonacci_word_sequence;
    string fibonacci_word_sequence_get(int n)
    {
        // [TODO]
    }
    string fibonacci_word_sequence_get(int n, int length_max, bool right_side)
    {
        // [TODO]
    }

    // fibonacci word sequenece occurrence record array
    vector<int> occurrence_times;
    string occurrence_pattern;
    int count_occurrence_times_recursive(int n)
    {
        if(occurrence_times[n] != -1)
            return occurrence_times[n];
        if(fibonacci_word_sequence_length[n] < occurrence_pattern.length())
            return occurrence_times[n] = 0;
        int ret = count_occurrence_times_recursive(n - 1) + count_occurrence_times_recursive(n - 2);
        string combine_str = fibonacci_word_sequence_get(n - 1, occurrence_pattern - 1, true) + fibonacci_word_sequence_get(n - 2, occurrence_pattern - 1, false);
        KnuthMorrisPratt kmp(combine_str, occurrence_pattern);
        ret += kmp.answer().size();
        return occurrence_times[n] = ret;
    }
};

inline string _fixstr(string para, int alignment_num = DEFAULT_FIXSTR)
{
    para.resize(alignment_num, ' ');
    return para;
}
inline string _fixstr(char para, int alignment_num = DEFAULT_FIXSTR)
{
    string ret = string(1, para);
    return _fixstr(ret, alignment_num);
}
inline string _fixstr(int para, int alignment_num = DEFAULT_FIXSTR)
{
    string ret = to_string(para);
    if(para == INF)
        ret = "INF";
    return _fixstr(ret, alignment_num);
}

int main(int argc, char* argv[])
{
//    ios::sync_with_stdio(false);
//    cin.tie(0);

    istream* input = &cin;
    if(argc == 2)
    {
        input = new ifstream(argv[1]);
    }

    int n;
    UVa1282 uva_1282;

    while((*input) >> n)
    {
        string pattern;
        (*input).ignore(1, '\n');
        getline((*input), pattern);
        cout << "Case " << t << ": " << uva_1282.count_occurrence_times(n, pattern) << endl;
    }

    if(argc == 2)
    {
        delete input;
    }

    clog << "Time used = " << (double)clock() / CLOCKS_PER_SEC << endl;
    return 0;
}

