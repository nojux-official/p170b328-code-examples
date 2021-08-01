using System;

namespace SimpleProgramCS
{
    public class Executor
    {
        private readonly string _name;
        public Executor(string name) => _name = name;

        public void Execute()
        {
            Console.WriteLine($"{_name}: one");
            Console.WriteLine($"{_name}: two");
            Console.WriteLine($"{_name}: three");
        }
    }
}