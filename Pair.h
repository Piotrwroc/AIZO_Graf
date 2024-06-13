#ifndef PAIR_H
#define PAIR_H

template <typename T1, typename T2>
class My_pair
{
public:
    T1 first;
    T2 second;
    My_pair* next;

    My_pair() : first(T1()), second(T2()), next(nullptr) {}
    My_pair(const T1& a, const T2& b) : first(a), second(b), next(nullptr) {}
};

template <typename T1, typename T2>
My_pair<T1, T2> my_make_pair(const T1& a, const T2& b) 
{
    return My_pair<T1, T2>(a, b);
}

#endif  PAIR_H