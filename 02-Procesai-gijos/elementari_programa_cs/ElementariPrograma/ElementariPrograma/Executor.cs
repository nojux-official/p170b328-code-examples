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
            Console.Write(_name + ": ");
            Console.Write("vienas ");
            Console.Write("du ");
            Console.WriteLine("trys");
        }
    }
}