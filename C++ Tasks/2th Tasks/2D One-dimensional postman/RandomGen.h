#pragma once

class RandomGen
{
public:
    RandomGen(unsigned a_val, unsigned b_val) : a{ a_val }, b{ b_val } {}

    unsigned NextRand24()
    {
        curr = curr * a + b;
        return curr >> 8;
    }

    unsigned NextRand32()
    {
        unsigned tmp1_val = NextRand24();
        unsigned tmp2_val = NextRand24();

        return (tmp1_val << 8) ^ tmp2_val;
    }

private:
    unsigned curr = 0;
    unsigned a = 0;
    unsigned b = 0;
};

std::vector<unsigned> generate_xi(int32_t n, unsigned a, unsigned b)
{
    std::vector<unsigned> res_xi(n);

    RandomGen generator(a, b);
    for (size_t i = 0; i < res_xi.size(); ++i)
        res_xi[i] = generator.NextRand32();

    return res_xi;
}