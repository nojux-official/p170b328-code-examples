import std.stdio;
import std.algorithm;
import std.range;
import std.typecons;

int[] getVector()
{
    return iota(0, 20).array;
}

void main()
{
    auto vector = getVector();
    auto sum = vector
        .filter!(x => x % 2 == 0)
        .map!(x => x * x)
        .reduce!((acc, x) => acc + x);
    writeln(sum);
}
