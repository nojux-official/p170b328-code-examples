using System;

namespace ElementariPrograma
{
    public class Executor
    {
        private string _name;
        public Executor(string name)
        {
            _name = name;
        }

        public void Execute()
        {
            Console.WriteLine(_name + ": one");
            Console.WriteLine(_name + ": two");
            Console.WriteLine(_name + ": three");
        }
    }
}